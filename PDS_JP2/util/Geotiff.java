/*
 * Copyright (C) 2011 United States Government as represented by the Administrator of the
 * National Aeronautics and Space Administration.
 * All Rights Reserved.
 */
package HiRISE.PDS_JP2.util;

/**
 * Contains constants defined by the Geotiff Specification version 1.8.2
 * http://www.remotesensing.org/geotiff/spec/geotiffhome.html
 */
public abstract class Geotiff
{
    public static final int Undefined   = 0;
    public static final int UserDefined = 32767;
    
    // Geotiff extension tags
    public interface Tag
    {
        public static final int MODEL_PIXELSCALE        = 33550;
        public static final int MODEL_TIEPOINT          = 33922;
        public static final int MODEL_TRANSFORMATION    = 34264;
        public static final int GEO_KEY_DIRECTORY       = 34735;
        public static final int GEO_DOUBLE_PARAMS       = 34736;
        public static final int GEO_ASCII_PARAMS        = 34737;

        public static final int GDAL_NODATA             = 42113;
    }


    public interface GeoKeyHeader
    {
        public static final int KeyDirectoryVersion = 1;
        public static final int KeyRevision = 1;
        public static final int MinorRevision = 0;
        
    }

    public interface GeoKey
    {
        public static final int ModelType           = 1024; // see GeoTiff.ModelType values
        public static final int RasterType          = 1025; // see GeoTiff.RasterType values

        public static final int GeographicType      = 2048; // see GeoTiff.GCS for values or Section 6.3.2.1 Codes
        // GeoKey Requirements for User-Defined geographic CS:
        public static final int GeogCitation            = 2049; // ASCII
        public static final int GeogGeodeticDatum       = 2050; // SHORT, See section 6.3.2.2 Geodetic Datum Codes
        public static final int GeogPrimeMeridian       = 2051; // SHORT, Section 6.3.2.4 Codes
        public static final int GeogLinearUnits         = 2052; // Double, See GeoTiff.Unit.Liner or Section 6.3.1.3 Codes
        public static final int GeogLinearUnitSize      = 2053; // Double, meters
        public static final int GeogAngularUnits        = 2054; // Short, See GeoTiff.Units.Angular or Section 6.3.1.4 Codes
        public static final int GeogAngularUnitSize     = 2055; // Double, radians
        public static final int GeogEllipsoid           = 2056; // Short, See Section 6.3.2.3 Codes 
        public static final int GeogAzimuthUnits        = 2060; // Short, Section 6.3.1.4 Codes
        public static final int GeogPrimeMeridianLong   = 2061; // DOUBLE, See GeoTiff.Units.Angular

        // 6.2.3 Projected CS Parameter Keys
        public static final int ProjectedCSType             = 3072; /*  Section 6.3.3.1 codes */
        public static final int PCSCitation                 = 3073; /*  documentation */
        public static final int Projection                  = 3074; /*  Section 6.3.3.2 codes */
        public static final int ProjCoordTrans              = 3075; /*  Section 6.3.3.3 codes */
        public static final int ProjLinearUnits             = 3076; /*  Section 6.3.1.3 codes */
        public static final int ProjLinearUnitSize          = 3077; /*  meters */
        public static final int ProjStdParallel1            = 3078; /*  GeogAngularUnit */
        public static final int ProjStdParallel2            = 3079; /*  GeogAngularUnit */
        public static final int ProjNatOriginLong           = 3080; /*  GeogAngularUnit */
        public static final int ProjNatOriginLat            = 3081; /*  GeogAngularUnit */
        public static final int ProjFalseEasting            = 3082; /*  ProjLinearUnits */
        public static final int ProjFalseNorthing           = 3083; /*  ProjLinearUnits */
        public static final int ProjFalseOriginLong         = 3084; /*  GeogAngularUnit */
        public static final int ProjFalseOriginLat          = 3085; /*  GeogAngularUnit */
        public static final int ProjFalseOriginEasting      = 3086; /*  ProjLinearUnits */
        public static final int ProjFalseOriginNorthing     = 3087; /*  ProjLinearUnits */
        public static final int ProjCenterLong              = 3088; /*  GeogAngularUnit */
        public static final int ProjCenterLat               = 3089; /*  GeogAngularUnit */
        public static final int ProjCenterEasting           = 3090; /*  ProjLinearUnits */
        public static final int ProjCenterNorthing          = 3091; /*  ProjLinearUnits */
        public static final int ProjScaleAtNatOrigin        = 3092; /*  ratio */
        public static final int ProjScaleAtCenter           = 3093; /*  ratio */
        public static final int ProjAzimuthAngle            = 3094; /*  GeogAzimuthUnit */
        public static final int ProjStraightVertPoleLong    = 3095; /*  GeogAngularUnit */
        // Aliases:
        public static final int ProjStdParallel = ProjStdParallel1;
        public static final int ProjOriginLong = ProjNatOriginLong;
        public static final int ProjOriginLat = ProjNatOriginLat;
        public static final int ProjScaleAtOrigin = ProjScaleAtNatOrigin;

        // 6.2.4 Vertical CS Keys
        public static final int VerticalCSType    = 4096; /* Section 6.3.4.1 codes */
        public static final int VerticalCitation  = 4097; /* ASCII */
        public static final int VerticalDatum     = 4098; /* Section 6.3.4.2 codes */
        public static final int VerticalUnits     = 4099; /* Section 6.3.1.3 codes */
    }

    public interface ModelType
    {
        public static final int Undefined   =     0;
        public static final int Projected   =     1;
        public static final int Geographic  =     2;
        public static final int Geocentric  =     3;
        public static final int UserDefined = 32767;

        public static final int DEFAULT = Geographic;
    }

    public interface RasterType
    {
        public static final int Undefined           =     0; // highly not recomended to use
        public static final int RasterPixelIsArea   =     1;
        public static final int RasterPixelIsPoint  =     2;
        public static final int UserDefined         = 32767; // highly not recomended to use
    }


    public interface Unit
    {
        public static final int Undefined   =     0;
        public static final int UserDefined = 32767;

        //6.3.1.3 Linear Units Codes
        public interface Linear
        {
            public static final int Meter                       = 9001;
            public static final int Foot                        = 9002;
            public static final int Foot_US_Survey              = 9003;
            public static final int Foot_Modified_American      = 9004;
            public static final int Foot_Clarke                 = 9005;
            public static final int Foot_Indian                 = 9006;
            public static final int Link                        = 9007;
            public static final int Link_Benoit                 = 9008;
            public static final int Link_Sears                  = 9009;
            public static final int Chain_Benoit                = 9010;
            public static final int Chain_Sears                 = 9011;
            public static final int Yard_Sears                  = 9012;
            public static final int Yard_Indian                 = 9013;
            public static final int Fathom                      = 9014;
            public static final int Mile_International_Nautical = 9015;
        }

        // 6.3.1.4 Angular Units Codes
        // These codes shall be used for any key that requires specification of an angular unit of measurement.
        public interface Angular
        {
            public static final int Angular_Radian              = 9101;
            public static final int Angular_Degree              = 9102;
            public static final int Angular_Arc_Minute          = 9103;
            public static final int Angular_Arc_Second          = 9104;
            public static final int Angular_Grad                = 9105;
            public static final int Angular_Gon                 = 9106;
            public static final int Angular_DMS                 = 9107;
            public static final int Angular_DMS_Hemisphere      = 9108;
        }
    }

    // Geogrphic Coordinate System (GCS)
    public interface GCS
    {
        public static final int Undefined   = 0;
        public static final int UserDefined = 32767;

        public static final int NAD_83      = 4269;
        public static final int WGS_72      = 4322;
        public static final int WGS_72BE    = 4324;
        public static final int WGS_84      = 4326;

        public static final int DEFAULT = WGS_84;
    }

    // Geogrphic Coordinate System Ellipsoid (GCSE)
    public interface GCSE
    {
        public static final int WGS_84 = 4030;
    }

    // Projected Coordinate System (PCS)
    public interface PCS
    {
        public static final int Undefined   =     0;
        public static final int UserDefined = 32767;
    }

    // Vertical Coordinate System (VCS) 
    public interface VCS
    {
        // [ 1, 4999] = Reserved
        // [ 5000, 5099] = EPSG Ellipsoid Vertical CS Codes
        // [ 5100, 5199] = EPSG Orthometric Vertical CS Codes
        // [ 5200, 5999] = Reserved EPSG
        // [ 6000, 32766] = Reserved
        // [32768, 65535] = Private User Implementations
        
        public static final int Undefined   =     0;
        public static final int UserDefined = 32767;

        public static final int Airy_1830_ellipsoid = 5001;
        public static final int Airy_Modified_1849_ellipsoid = 5002;
        public static final int ANS_ellipsoid = 5003;
        public static final int Bessel_1841_ellipsoid = 5004;
        public static final int Bessel_Modified_ellipsoid = 5005;
        public static final int Bessel_Namibia_ellipsoid = 5006;
        public static final int Clarke_1858_ellipsoid = 5007;
        public static final int Clarke_1866_ellipsoid = 5008;
        public static final int Clarke_1880_Benoit_ellipsoid = 5010;
        public static final int Clarke_1880_IGN_ellipsoid = 5011;
        public static final int Clarke_1880_RGS_ellipsoid = 5012;
        public static final int Clarke_1880_Arc_ellipsoid = 5013;
        public static final int Clarke_1880_SGA_1922_ellipsoid = 5014;
        public static final int Everest_1830_1937_Adjustment_ellipsoid = 5015;
        public static final int Everest_1830_1967_Definition_ellipsoid = 5016;
        public static final int Everest_1830_1975_Definition_ellipsoid = 5017;
        public static final int Everest_1830_Modified_ellipsoid = 5018;
        public static final int GRS_1980_ellipsoid = 5019;
        public static final int Helmert_1906_ellipsoid = 5020;
        public static final int INS_ellipsoid = 5021;
        public static final int International_1924_ellipsoid = 5022;
        public static final int International_1967_ellipsoid = 5023;
        public static final int Krassowsky_1940_ellipsoid = 5024;
        public static final int NWL_9D_ellipsoid = 5025;
        public static final int NWL_10D_ellipsoid = 5026;
        public static final int Plessis_1817_ellipsoid = 5027;
        public static final int Struve_1860_ellipsoid = 5028;
        public static final int War_Office_ellipsoid = 5029;
        public static final int WGS_84_ellipsoid = 5030;
        public static final int GEM_10C_ellipsoid = 5031;
        public static final int OSU86F_ellipsoid = 5032;
        public static final int OSU91A_ellipsoid = 5033;
        // Orthometric Vertical CS;
        public static final int Newlyn = 5101;
        public static final int North_American_Vertical_Datum_1929 = 5102;
        public static final int North_American_Vertical_Datum_1988 = 5103;
        public static final int Yellow_Sea_1956 = 5104;
        public static final int Baltic_Sea = 5105;
        public static final int Caspian_Sea = 5106;
            
        public static final int DEFAULT = Undefined;
    }

public static final String getGeoKeyHeaderName(final int code)
{
   switch (code)
   {
case (0): return "MinorRevision";
case (1): return "KeyDirectoryVersion";
//case (1): return "KeyRevision";
   }
   return Integer.toString(code);
}

public static final String getModelTypeKeyName(final int code)
{
   switch (code)
   {
case (0): return "Undefined";
case (1): return "Projected";
case (2): return "Geographic";
case (3): return "Geocentric";
   }
   return Integer.toString(code);
}

public static final String getRasterTypeKeyName(final int code)
{
   switch (code)
   {
case (0): return "Undefined";
case (1): return "RasterPixelIsArea";
case (2): return "RasterPixelIsPoint";
   }
   return Integer.toString(code);
}

public static final String getKeyName(final int code)
{
   switch (code)
   {
case (0): return "Undefined";

case (1024): return "ModelType";
case (1025): return "RasterType";
case (1026): return "GTCitationGeoKey";
case (2048): return "GeographicType";
case (2049): return "GeogCitation";
case (2050): return "GeogGeodeticDatum";
case (2051): return "GeogPrimeMeridian";
case (2052): return "GeogLinearUnits";
case (2053): return "GeogLinearUnitSize";
case (2054): return "GeogAngularUnits";
case (2055): return "GeogAngularUnitSize";
case (2056): return "GeogEllipsoid";
case (2057): return "GeogSemiMajorAxisGeoKey";
case (2058): return "GeogSemiMinorAxisGeoKey";
case (2059): return "GeogInvFlatteningGeoKey";
case (2060): return "GeogAzimuthUnits";
case (2061): return "GeogPrimeMeridianLong";
case (3072): return "ProjectedCSType";
case (3073): return "PCSCitation";
case (3074): return "Projection";
case (3075): return "ProjCoordTrans";
case (3076): return "ProjLinearUnits";
case (3077): return "ProjLinearUnitSize";
case (3078): return "ProjStdParallel1";
case (3079): return "ProjStdParallel2";
case (3080): return "ProjNatOriginLong";
case (3081): return "ProjNatOriginLat";
case (3082): return "ProjFalseEasting";
case (3083): return "ProjFalseNorthing";
case (3084): return "ProjFalseOriginLong";
case (3085): return "ProjFalseOriginLat";
case (3086): return "ProjFalseOriginEasting";
case (3087): return "ProjFalseOriginNorthing";
case (3088): return "ProjCenterLong";
case (3089): return "ProjCenterLat";
case (3090): return "ProjCenterEasting";
case (3091): return "ProjCenterNorthing";
case (3092): return "ProjScaleAtNatOrigin";
case (3093): return "ProjScaleAtCenter";
case (3094): return "ProjAzimuthAngle";
case (3095): return "ProjStraightVertPoleLong";
case (4030): return "WGS_84";
case (4096): return "VerticalCSType";
case (4097): return "VerticalCitation";
case (4098): return "VerticalDatum";
case (4099): return "VerticalUnits";
case (4269): return "NAD_83";
case (4322): return "WGS_72";
case (4324): return "WGS_72BE";
case (4326): return "WGS_84";
case (5001): return "Airy_1830_ellipsoid";
case (5002): return "Airy_Modified_1849_ellipsoid";
case (5003): return "ANS_ellipsoid";
case (5004): return "Bessel_1841_ellipsoid";
case (5005): return "Bessel_Modified_ellipsoid";
case (5006): return "Bessel_Namibia_ellipsoid";
case (5007): return "Clarke_1858_ellipsoid";
case (5008): return "Clarke_1866_ellipsoid";
case (5010): return "Clarke_1880_Benoit_ellipsoid";
case (5011): return "Clarke_1880_IGN_ellipsoid";
case (5012): return "Clarke_1880_RGS_ellipsoid";
case (5013): return "Clarke_1880_Arc_ellipsoid";
case (5014): return "Clarke_1880_SGA_1922_ellipsoid";
case (5015): return "Everest_1830_1937_Adjustment_ellipsoid";
case (5016): return "Everest_1830_1967_Definition_ellipsoid";
case (5017): return "Everest_1830_1975_Definition_ellipsoid";
case (5018): return "Everest_1830_Modified_ellipsoid";
case (5019): return "GRS_1980_ellipsoid";
case (5020): return "Helmert_1906_ellipsoid";
case (5021): return "INS_ellipsoid";
case (5022): return "International_1924_ellipsoid";
case (5023): return "International_1967_ellipsoid";
case (5024): return "Krassowsky_1940_ellipsoid";
case (5025): return "NWL_9D_ellipsoid";
case (5026): return "NWL_10D_ellipsoid";
case (5027): return "Plessis_1817_ellipsoid";
case (5028): return "Struve_1860_ellipsoid";
case (5029): return "War_Office_ellipsoid";
case (5030): return "WGS_84_ellipsoid";
case (5031): return "GEM_10C_ellipsoid";
case (5032): return "OSU86F_ellipsoid";
case (5033): return "OSU91A_ellipsoid";
case (5101): return "Newlyn";
case (5102): return "North_American_Vertical_Datum_1929";
case (5103): return "North_American_Vertical_Datum_1988";
case (5104): return "Yellow_Sea_1956";
case (5105): return "Baltic_Sea";
case (5106): return "Caspian_Sea";
case (9001): return "Meter";
case (9002): return "Foot";
case (9003): return "Foot_US_Survey";
case (9004): return "Foot_Modified_American";
case (9005): return "Foot_Clarke";
case (9006): return "Foot_Indian";
case (9007): return "Link";
case (9008): return "Link_Benoit";
case (9009): return "Link_Sears";
case (9010): return "Chain_Benoit";
case (9011): return "Chain_Sears";
case (9012): return "Yard_Sears";
case (9013): return "Yard_Indian";
case (9014): return "Fathom";
case (9015): return "Mile_International_Nautical";
case (9101): return "Angular_Radian";
case (9102): return "Angular_Degree";
case (9103): return "Angular_Arc_Minute";
case (9104): return "Angular_Arc_Second";
case (9105): return "Angular_Grad";
case (9106): return "Angular_Gon";
case (9107): return "Angular_DMS";
case (9108): return "Angular_DMS_Hemisphere";
case (32767): return "UserDefined";
case (33550): return "MODEL_PIXELSCALE";
case (33922): return "MODEL_TIEPOINT";
case (34264): return "MODEL_TRANSFORMATION";
case (34735): return "GEO_KEY_DIRECTORY";
case (34736): return "GEO_DOUBLE_PARAMS";
case (34737): return "GEO_ASCII_PARAMS";
case (42113): return "GDAL_NODATA";
   }

   return Integer.toString(code);
}

    public static int getKeyCode(String name)
    {
        if (name == null) return Undefined;
        
if (name.equalsIgnoreCase("ModelType")) { return 1024; }
if (name.equalsIgnoreCase("RasterType")) { return 1025; }
if (name.equalsIgnoreCase("GTCitationGeoKey")) { return 1026; }
if (name.equalsIgnoreCase("GeographicType")) { return 2048; }
if (name.equalsIgnoreCase("GeogCitation")) { return 2049; }
if (name.equalsIgnoreCase("GeogGeodeticDatum")) { return 2050; }
if (name.equalsIgnoreCase("GeogPrimeMeridian")) { return 2051; }
if (name.equalsIgnoreCase("GeogLinearUnits")) { return 2052; }
if (name.equalsIgnoreCase("GeogLinearUnitSize")) { return 2053; }
if (name.equalsIgnoreCase("GeogAngularUnits")) { return 2054; }
if (name.equalsIgnoreCase("GeogAngularUnitSize")) { return 2055; }
if (name.equalsIgnoreCase("GeogEllipsoid")) { return 2056; }
if (name.equalsIgnoreCase("GeogSemiMajorAxisGeoKey")) { return 2057; }
if (name.equalsIgnoreCase("GeogSemiMinorAxisGeoKey")) { return 2058; }
if (name.equalsIgnoreCase("GeogInvFlatteningGeoKey")) { return 2059; }
if (name.equalsIgnoreCase("GeogAzimuthUnits")) { return 2060; }
if (name.equalsIgnoreCase("GeogPrimeMeridianLong")) { return 2061; }
if (name.equalsIgnoreCase("ProjectedCSType")) { return 3072; }
if (name.equalsIgnoreCase("PCSCitation")) { return 3073; }
if (name.equalsIgnoreCase("Projection")) { return 3074; }
if (name.equalsIgnoreCase("ProjCoordTrans")) { return 3075; }
if (name.equalsIgnoreCase("ProjLinearUnits")) { return 3076; }
if (name.equalsIgnoreCase("ProjLinearUnitSize")) { return 3077; }
if (name.equalsIgnoreCase("ProjStdParallel1")) { return 3078; }
if (name.equalsIgnoreCase("ProjStdParallel2")) { return 3079; }
if (name.equalsIgnoreCase("ProjNatOriginLong")) { return 3080; }
if (name.equalsIgnoreCase("ProjNatOriginLat")) { return 3081; }
if (name.equalsIgnoreCase("ProjFalseEasting")) { return 3082; }
if (name.equalsIgnoreCase("ProjFalseNorthing")) { return 3083; }
if (name.equalsIgnoreCase("ProjFalseOriginLong")) { return 3084; }
if (name.equalsIgnoreCase("ProjFalseOriginLat")) { return 3085; }
if (name.equalsIgnoreCase("ProjFalseOriginEasting")) { return 3086; }
if (name.equalsIgnoreCase("ProjFalseOriginNorthing")) { return 3087; }
if (name.equalsIgnoreCase("ProjCenterLong")) { return 3088; }
if (name.equalsIgnoreCase("ProjCenterLat")) { return 3089; }
if (name.equalsIgnoreCase("ProjCenterEasting")) { return 3090; }
if (name.equalsIgnoreCase("ProjCenterNorthing")) { return 3091; }
if (name.equalsIgnoreCase("ProjScaleAtNatOrigin")) { return 3092; }
if (name.equalsIgnoreCase("ProjScaleAtCenter")) { return 3093; }
if (name.equalsIgnoreCase("ProjAzimuthAngle")) { return 3094; }
if (name.equalsIgnoreCase("ProjStraightVertPoleLong")) { return 3095; }
if (name.equalsIgnoreCase("WGS_84")) { return 4030; }
if (name.equalsIgnoreCase("VerticalCSType")) { return 4096; }
if (name.equalsIgnoreCase("VerticalCitation")) { return 4097; }
if (name.equalsIgnoreCase("VerticalDatum")) { return 4098; }
if (name.equalsIgnoreCase("VerticalUnits")) { return 4099; }
if (name.equalsIgnoreCase("NAD_83")) { return 4269; }
if (name.equalsIgnoreCase("WGS_72")) { return 4322; }
if (name.equalsIgnoreCase("WGS_72BE")) { return 4324; }
if (name.equalsIgnoreCase("WGS_84")) { return 4326; }
if (name.equalsIgnoreCase("Airy_1830_ellipsoid")) { return 5001; }
if (name.equalsIgnoreCase("Airy_Modified_1849_ellipsoid")) { return 5002; }
if (name.equalsIgnoreCase("ANS_ellipsoid")) { return 5003; }
if (name.equalsIgnoreCase("Bessel_1841_ellipsoid")) { return 5004; }
if (name.equalsIgnoreCase("Bessel_Modified_ellipsoid")) { return 5005; }
if (name.equalsIgnoreCase("Bessel_Namibia_ellipsoid")) { return 5006; }
if (name.equalsIgnoreCase("Clarke_1858_ellipsoid")) { return 5007; }
if (name.equalsIgnoreCase("Clarke_1866_ellipsoid")) { return 5008; }
if (name.equalsIgnoreCase("Clarke_1880_Benoit_ellipsoid")) { return 5010; }
if (name.equalsIgnoreCase("Clarke_1880_IGN_ellipsoid")) { return 5011; }
if (name.equalsIgnoreCase("Clarke_1880_RGS_ellipsoid")) { return 5012; }
if (name.equalsIgnoreCase("Clarke_1880_Arc_ellipsoid")) { return 5013; }
if (name.equalsIgnoreCase("Clarke_1880_SGA_1922_ellipsoid")) { return 5014; }
if (name.equalsIgnoreCase("Everest_1830_1937_Adjustment_ellipsoid")) { return 5015; }
if (name.equalsIgnoreCase("Everest_1830_1967_Definition_ellipsoid")) { return 5016; }
if (name.equalsIgnoreCase("Everest_1830_1975_Definition_ellipsoid")) { return 5017; }
if (name.equalsIgnoreCase("Everest_1830_Modified_ellipsoid")) { return 5018; }
if (name.equalsIgnoreCase("GRS_1980_ellipsoid")) { return 5019; }
if (name.equalsIgnoreCase("Helmert_1906_ellipsoid")) { return 5020; }
if (name.equalsIgnoreCase("INS_ellipsoid")) { return 5021; }
if (name.equalsIgnoreCase("International_1924_ellipsoid")) { return 5022; }
if (name.equalsIgnoreCase("International_1967_ellipsoid")) { return 5023; }
if (name.equalsIgnoreCase("Krassowsky_1940_ellipsoid")) { return 5024; }
if (name.equalsIgnoreCase("NWL_9D_ellipsoid")) { return 5025; }
if (name.equalsIgnoreCase("NWL_10D_ellipsoid")) { return 5026; }
if (name.equalsIgnoreCase("Plessis_1817_ellipsoid")) { return 5027; }
if (name.equalsIgnoreCase("Struve_1860_ellipsoid")) { return 5028; }
if (name.equalsIgnoreCase("War_Office_ellipsoid")) { return 5029; }
if (name.equalsIgnoreCase("WGS_84_ellipsoid")) { return 5030; }
if (name.equalsIgnoreCase("GEM_10C_ellipsoid")) { return 5031; }
if (name.equalsIgnoreCase("OSU86F_ellipsoid")) { return 5032; }
if (name.equalsIgnoreCase("OSU91A_ellipsoid")) { return 5033; }
if (name.equalsIgnoreCase("Newlyn")) { return 5101; }
if (name.equalsIgnoreCase("North_American_Vertical_Datum_1929")) { return 5102; }
if (name.equalsIgnoreCase("North_American_Vertical_Datum_1988")) { return 5103; }
if (name.equalsIgnoreCase("Yellow_Sea_1956")) { return 5104; }
if (name.equalsIgnoreCase("Baltic_Sea")) { return 5105; }
if (name.equalsIgnoreCase("Caspian_Sea")) { return 5106; }
if (name.equalsIgnoreCase("Meter")) { return 9001; }
if (name.equalsIgnoreCase("Foot")) { return 9002; }
if (name.equalsIgnoreCase("Foot_US_Survey")) { return 9003; }
if (name.equalsIgnoreCase("Foot_Modified_American")) { return 9004; }
if (name.equalsIgnoreCase("Foot_Clarke")) { return 9005; }
if (name.equalsIgnoreCase("Foot_Indian")) { return 9006; }
if (name.equalsIgnoreCase("Link")) { return 9007; }
if (name.equalsIgnoreCase("Link_Benoit")) { return 9008; }
if (name.equalsIgnoreCase("Link_Sears")) { return 9009; }
if (name.equalsIgnoreCase("Chain_Benoit")) { return 9010; }
if (name.equalsIgnoreCase("Chain_Sears")) { return 9011; }
if (name.equalsIgnoreCase("Yard_Sears")) { return 9012; }
if (name.equalsIgnoreCase("Yard_Indian")) { return 9013; }
if (name.equalsIgnoreCase("Fathom")) { return 9014; }
if (name.equalsIgnoreCase("Mile_International_Nautical")) { return 9015; }
if (name.equalsIgnoreCase("Angular_Radian")) { return 9101; }
if (name.equalsIgnoreCase("Angular_Degree")) { return 9102; }
if (name.equalsIgnoreCase("Angular_Arc_Minute")) { return 9103; }
if (name.equalsIgnoreCase("Angular_Arc_Second")) { return 9104; }
if (name.equalsIgnoreCase("Angular_Grad")) { return 9105; }
if (name.equalsIgnoreCase("Angular_Gon")) { return 9106; }
if (name.equalsIgnoreCase("Angular_DMS")) { return 9107; }
if (name.equalsIgnoreCase("Angular_DMS_Hemisphere")) { return 9108; }
/*
if (name.equalsIgnoreCase("MODEL_PIXELSCALE")) { return 33550; }
if (name.equalsIgnoreCase("MODEL_TIEPOINT")) { return 33922; }
if (name.equalsIgnoreCase("MODEL_TRANSFORMATION")) { return 34264; }
if (name.equalsIgnoreCase("GEO_KEY_DIRECTORY")) { return 34735; }
if (name.equalsIgnoreCase("GEO_DOUBLE_PARAMS")) { return 34736; }
if (name.equalsIgnoreCase("GEO_ASCII_PARAMS")) { return 34737; }
if (name.equalsIgnoreCase("GDAL_NODATA")) { return 42113; }
*/
    return Undefined;
    }
}
