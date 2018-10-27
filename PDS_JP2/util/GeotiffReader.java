/**

This programs looks through the first Megabyte of a file to find a TIFF header.
The containing file format need not be TIFF. If it finds the TIFF header it then
searches for Geotiff entries and displays them on the standard output. 
*/
package HiRISE.PDS_JP2.util;

import java.io.*;
import java.nio.*;
import java.nio.channels.*;
import java.nio.charset.*;
import java.util.*;
import java.util.logging.*;
import static java.nio.channels.FileChannel.MapMode.READ_ONLY;
import static java.nio.channels.FileChannel.MapMode.READ_WRITE;
import static java.nio.ByteOrder.LITTLE_ENDIAN;
import static java.nio.ByteOrder.BIG_ENDIAN;

public class GeotiffReader extends Geotiff
{
   /** CVS ID */ 
   public static final String ID = "GeotiffReader 1.7 2016/01/19 18:30:55";
    
   /** how many bytes to read into memory from the header */ 
   static final long HEADER_LIMIT_BYTES  = 1024000l; // one megabyte
   
   /** magic byte sequence indicating a TIFF little-endian header */
   static final int TIFF_HEADER_LITTLE_ENDIAN = 0x49492A00; // II

   /** magic byte sequence indicating a TIFF big-endian header */
   static final int TIFF_HEADER_BIG_ENDIAN = 0x4D4D002A; // MM

   /** TIFF identifier for a two-byte unsigned short (store as an int in java)*/
   static final int TIFF_TYPE_SHORT      = 3;
   
   /** TIFF identifier for a IEEE double (same as in java) */
   static final int TIFF_TYPE_DOUBLE     = 12;
   
   /** TIFF identifer for an ASCII character string */
   static final int TIFF_TYPE_STRING     = 2;

   /** Logger for debugging purposes */
   static final Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);
   
   /** Used for opening a RandomAccessFile read-only */
   static final String UNWRITABLE = "r";
   
   /** Used for opening a RandomAccessFile read-write (if permissions allow) */
   static final String WRITABLE = "rwd";
   
   /** Used to change geokey IDs */
   private int oldKeyID = Undefined, newKeyID = Undefined, fixKeyID;
   
   /** Used to change values (number or String) */
   private String fixValue = null;
   
   /**
   Structure representing a TIFF "directory" entry. 12 bytes in memory.
   */
   static class TiffDirEntry
   {
      int          tag;       /* 2-byte unsigned short tag number */
      int          type;      /* 2-byte unsigned short data type */
      long         count;     /* 4-byte unsigned int number of items; length in spec */
      long         offset;    /* 4-byte unsigned int byte offset to field data */

      @Override
      public String toString()
      {
         return String.format("TIFF tag %d [%d] #%d @%d", tag, type, count, offset);
      }
   };

   /**
   Structure representing a Geotiff key entry, an array of these could be under
   TIFF directory entry with tag ID Geotiff.GEO_KEY_DIRECTORY. A geotiff key entry
   is in the same 12-byte format as a TIFF directory entry but re-purposed.
   */
   static class GeoKeyEntry
   {
      int KeyID;           /* identifies a key in the Geotiff spec */
      int TIFFTagLocation; /* if 0, value contained in offset */
      int Count;           /* number of items, ignore if TIFFTagLocation is zero */
      int Value_Offset;    /* actual value or pointer to item number in a TIFF tag */

      @Override
      public String toString()
      {
        switch (TIFFTagLocation)
        {
           case 0:
              return String.format("%d = %d", KeyID, Value_Offset);
           default:
              return String.format("%d @%d+%d #%d", KeyID, TIFFTagLocation, Value_Offset, Count);
        }     
      }
   };

   /**
   Handle command-line arguments, open files and print Geotiff headers 
   */
   public static void main(String... args) throws Exception
   {
      System.out.println(ID);
      
      GeotiffReader geotiffreader = new GeotiffReader();
            
      String file = null, mode = UNWRITABLE;
      
      for (int i = 0 ; i < args.length ; i++)
      {         
         if (args[i].matches("-+changekey") && args.length > ++i)
         {
             String[] keys = args[i].split(",");
             if (keys.length == 2)
             {
                 geotiffreader.changeGeoKeyID(keys[0], keys[1]);
                 mode = WRITABLE;
             }
             continue;
         }
         if (args[i].matches("-+changeval") && args.length > ++i)
         {
             String[] vals = args[i].split(",");
             if (vals.length == 2)
             {
                 geotiffreader.changeGeoValue(vals[0], vals[1]);
                 mode = WRITABLE;
             }
             continue;
         }
         
         file = args[i];
      }         
      
      if (file == null)
      {
          System.out.println("Args: [--changekey old,new] [--changeval key,val] file");
          System.exit(1);
      }
      
      RandomAccessFile open = new RandomAccessFile(file, mode); 
      FileChannel channel = open.getChannel();
      ByteBuffer buffer = channel.map(mode.equals(WRITABLE) ? READ_WRITE : READ_ONLY, 0L, HEADER_LIMIT_BYTES);

      geotiffreader.getGeotiffProperties(buffer).store(System.out, "Geotiff Properties of " + file);

      channel.close();
      open.close();

   }

   /**
    Locates the TIFF header. 
    @param buffer The buffer
    @return starting byte of TIFF header or -1 if not found
   */
   final int findTiffHeader(final ByteBuffer buffer)
   {
       buffer.order(BIG_ENDIAN);
       /*
       The TIFF marker is not guaranteeed to be in the file, or be at an
       integral offset, so we iterate through the bytes one at a time starting
       with the zeroeth, reading four bytes ahead, then seeking to the first byte, etc.
       */
         for (int var, loc, pos = 0; buffer.hasRemaining() ; pos++)
         {
            buffer.position(pos);
            var = buffer.getInt();
            if (TIFF_HEADER_LITTLE_ENDIAN == var)
            {
               loc = buffer.position() - 4; 
               logger.fine("Found a little endian TIFF Header at byte " + loc);

	            buffer.order(LITTLE_ENDIAN);
               return loc; // bytes
            }
            else if (TIFF_HEADER_BIG_ENDIAN == var)
            {
               loc = buffer.position() - 4;
               logger.fine("Found a big endian TIFF Header at byte " + loc);
               return loc;
            }
         }
      
      logger.warning("Did not find a TIFF header");
      
      return -1;
   }

   /**
    Locates the TIFF directory
    @param buffer The buffer
    @return starting byte of the TIFF directory or -1 if not found
   */
   final int findTiffDirectory(final ByteBuffer buffer)
   {
      int pos = findTiffHeader(buffer);
      
      if (pos < 0) 
      {
            return -1;
      }
      
      // TODO this seems to be required on our files, should it be??
      //buffer.order(ByteOrder.LITTLE_ENDIAN);
      buffer.position(pos);
      buffer.getInt(); // TIFF_HEADER_MARKER
      
      /*
       the 4-byte integer after the TIFF identifer is a pointer to the byte
       location of the TIFF directory
      */
      pos += buffer.getInt();
      logger.fine("Found TIFF directory at byte " + pos);
      return pos;
   }

   /**
    Read the TIFF directory entries, if any. Returns an empty list if none found. 
    @param buffer The buffer
    @return A list of found TiffDirEntries
   */ 
   final List <TiffDirEntry> readTiffDirEntries(final ByteBuffer buffer)
   {
      int count = 0, pos = findTiffDirectory(buffer);
      
      if (pos >= 0) 
      {
          buffer.position(pos);

          if (buffer.hasRemaining())
          {
              count = buffer.getChar();
          }
      }
      
      logger.fine("TIFF dir count is " + count);
      
      if (count < 1) return new ArrayList <TiffDirEntry> ();

      List <TiffDirEntry> list = new ArrayList <TiffDirEntry> (count);

      for (int i = 0 ; i < count ; i++)
      {
         TiffDirEntry entry = new TiffDirEntry();

         entry.tag = buffer.getChar();
         entry.type = buffer.getChar();
         entry.count = buffer.getInt();
         entry.offset = pos + 2 - 12 + buffer.getInt(); // TODO understand this offset: 10 bytes before the dir start plus the value??
         logger.finest(entry.toString());
         list.add(entry);
      }

      return list;
   }

   /**
    Read the Geotiff keys, which are pointed to by TIFF directory entry tagged
    34735.
    @param buffer The buffer
    @param entry The TIFF directory entry pointing to the geokeys
    @return A list of any found GeoKeyEntries
   */
   final List <GeoKeyEntry> readGeoKeys(final ByteBuffer buffer, TiffDirEntry entry) throws IOException
   {
      if (entry == null)
      {
         throw new IOException("Invalid null GeoKeyDirectoryTag");
      }
       
      if (entry.tag != Tag.GEO_KEY_DIRECTORY && entry.type != TIFF_TYPE_SHORT)
      {
         throw new IOException(String.format("Invalid GeoKeyDirectoryTag (tag = %d, type = %d)", entry.tag, entry.type));
      }

      List <GeoKeyEntry> list = new ArrayList <GeoKeyEntry> ();

      buffer.position((int) entry.offset);

      for (int i = 0 ; i < entry.count / 4 ; i++)
      {
         GeoKeyEntry geokey = new GeoKeyEntry();
         geokey.KeyID = buffer.getChar();
         
         if (oldKeyID > 0 && geokey.KeyID == oldKeyID)
         {
             buffer.position(buffer.position() - 2);
             logger.info(String.format("Changing %d [%s] to %d [%s] at byte %d",
                (int) oldKeyID,
                GeotiffReader.getKeyName(oldKeyID),
                (int) newKeyID,
                GeotiffReader.getKeyName(newKeyID),
                buffer.position()
             ));
             buffer.putChar((char)newKeyID);
             geokey.KeyID = newKeyID;
         }
         
         geokey.TIFFTagLocation = buffer.getChar();
         geokey.Count = buffer.getChar();
         geokey.Value_Offset = buffer.getChar();
         logger.finer(geokey.toString());
         list.add(geokey);
      }

      return list;
   }

   /**
    Read the doubles, which are pointed to by TIFF directory entry tagged 34736.
   */
   final double[] readDoubles(final ByteBuffer buffer, final TiffDirEntry entry, final List <GeoKeyEntry> geokeys) 
   throws IOException
   {
      if (entry.type != TIFF_TYPE_DOUBLE)
      {
         throw new IOException(String.format("Invalid GeoKeyDoubleTag (tag = %d, type = %d)", entry.tag, entry.type));
      }

      buffer.position((int) entry.offset);

      double[] doubles = new double[(int)entry.count];

      double fixNum = Undefined;
      GeoKeyEntry fixEntry = null;
      
      if (fixKeyID != Undefined && geokeys != null)
      {
          try
          {
              if (fixValue != null) fixNum = Double.parseDouble(fixValue);
          }
          catch (NumberFormatException ex)
          {
            logger.log(Level.SEVERE, "Could not parse numeric value from " + fixValue, ex);
            throw ex;
          }
          
          for (GeoKeyEntry e : geokeys)
          {
              if (e.KeyID == fixKeyID)
              {
                  fixEntry = e;
              }
          }
      }
      
      for (int i = 0 ; i < doubles.length ; i++)
      {
         doubles[i] = buffer.getDouble();

         if (fixValue != null && fixEntry != null && i == fixEntry.Value_Offset)
         {
             buffer.position(buffer.position() - 8);
             logger.info(String.format("Changing %s to %s at byte %d",
                doubles[i],
                fixValue,
                buffer.position()
             ));
             buffer.putDouble(fixNum);
             doubles[i] = fixNum;
         }
      }

      logger.fine(Arrays.toString(doubles));
      
      return doubles;
   }

   /**
    Read the strings, which are pointed to by TIFF directory entry tagged 34737.
    The strings are separated by the pipe (|) character, each may contain null
    terminators. There should be a terminating pipe character as well.
   */
   final String readStrings(final ByteBuffer buffer, final TiffDirEntry entry, final List <GeoKeyEntry> geokeys) 
   throws IOException
   {
      if (entry.type != TIFF_TYPE_STRING)
      {
          throw new IOException(String.format("Invalid GeoKeyASCIITag (tag = %d, type = %d)", entry.tag, entry.type));
      }

      buffer.position((int) entry.offset);

      byte[] ascii = new byte[(int)entry.count];

      buffer.get(ascii);

      String str = new String(ascii, Charset.forName("US-ASCII"));

      logger.fine(str);
      
      return str;
   }

   /**
    * To change a geoKey from one ID to another
    * @param oldKeyID the old key ID
    * @param newKeyID the new key ID
    */
   final public void changeGeoKeyID(String oldKeyID, String newKeyID)
   {
       if (oldKeyID.equalsIgnoreCase(newKeyID)) return;
       
       this.oldKeyID = getKeyCode(oldKeyID);
       this.newKeyID = getKeyCode(newKeyID);
   }
   
   /**
    * To change the value corresponding to a geoKey
    * @param fixKeyID the keyID to fix
    * @param fixValue the new value 
    */
   final public void changeGeoValue(String fixKeyID, String fixValue)
   {
       if (fixKeyID == null || "".equals(fixKeyID)) return;
       if (fixValue == null || "".equals(fixValue)) return;

       this.fixKeyID = getKeyCode(fixKeyID);
       this.fixValue = fixValue;
   }   
   /**
    Read the Geotiff values and fill in definitions
   */ 
   final public Properties getGeotiffProperties(ByteBuffer buffer) throws IOException
   {
      Properties props = new Properties();

      List <TiffDirEntry> entries = readTiffDirEntries(buffer);
      List <GeoKeyEntry> geokeys = null;
      String strings = null;
      double[] doubles = null;

      if (entries == null) return props;
      
      for (TiffDirEntry entry: entries)
      {
         switch (entry.tag)
         {
            case Tag.GEO_KEY_DIRECTORY:
               geokeys = readGeoKeys(buffer, entry);
               break;
            case Tag.MODEL_PIXELSCALE:
            case Tag.MODEL_TIEPOINT:
                String name = GeotiffReader.getKeyName(entry.tag);
                double[] values = readDoubles(buffer, entry, null);
                props.setProperty(name, Arrays.toString(values));
                break;
         }
      }

      if (geokeys == null) return props;
      
      for (TiffDirEntry entry: entries)
      {
         switch (entry.tag)
         {
            case Tag.GEO_ASCII_PARAMS:
               strings = readStrings(buffer, entry, geokeys);
               break;
            case Tag.GEO_DOUBLE_PARAMS:
               doubles = readDoubles(buffer, entry, geokeys);
               break;
         }
      }

      for (GeoKeyEntry key : geokeys)
      {
         String name = GeotiffReader.getKeyName(key.KeyID);

         switch (key.TIFFTagLocation)
         {
            case 0:
               switch (key.KeyID)
               {
                  case GeoKey.ModelType:
                     props.setProperty(name, GeotiffReader.getModelTypeKeyName(key.Value_Offset));
                     break;
                  case GeoKey.RasterType:
                     props.setProperty(name, GeotiffReader.getRasterTypeKeyName(key.Value_Offset));
                     break;
                  default:
                     props.setProperty(name, GeotiffReader.getKeyName(key.Value_Offset));
                     break;
               }
               break;
               
            case Tag.GEO_ASCII_PARAMS:
                if (strings != null && key.Count > 0 && key.Value_Offset < strings.length())
                {
                    props.put(name, strings.substring(key.Value_Offset, key.Count -1 + key.Value_Offset));
                }
                else
                {
                    // TODO warn on invalid key?
                    System.out.format("%s = string(%d) @%d%n", name, key.Count, key.Value_Offset);
                }
                break;
                
            case Tag.GEO_DOUBLE_PARAMS:
                if (doubles != null && key.Count == 1 && key.Value_Offset < doubles.length)
                {
                    props.setProperty(name, Double.toString(doubles[key.Value_Offset]));
                }
                else
                {
                    // TODO handle double arrays or warn on invalid key
                    System.out.format("%s = number(%d) @%d%n", name, key.Count, key.Value_Offset);
                }
                break;
                
         }

      }

      return props;
   }
}

