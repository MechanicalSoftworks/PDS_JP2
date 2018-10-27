<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title></title>
    <filename>index</filename>
  </compound>
  <compound kind="file">
    <name>Dimensions.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>Dimensions_8cc</filename>
    <includes id="Dimensions_8hh" name="Dimensions.hh" local="yes" imported="no">Dimensions.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>afedd1aec3d30f99cd080405f375fff5d</anchor>
      <arglist>(std::ostream &amp;stream, const Point_2D &amp;point)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a3617777e4c6990c3a7fbdc22ab8e9931</anchor>
      <arglist>(std::ostream &amp;stream, const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a7d0829a7ea24e83475988d76d9b55776</anchor>
      <arglist>(std::ostream &amp;stream, const Rectangle &amp;rectangle)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Dimensions.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>Dimensions_8hh</filename>
    <class kind="struct">UA::HiRISE::Point_2D</class>
    <class kind="struct">UA::HiRISE::Size_2D</class>
    <class kind="struct">UA::HiRISE::Rectangle</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>afedd1aec3d30f99cd080405f375fff5d</anchor>
      <arglist>(std::ostream &amp;stream, const Point_2D &amp;point)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a3617777e4c6990c3a7fbdc22ab8e9931</anchor>
      <arglist>(std::ostream &amp;stream, const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a7d0829a7ea24e83475988d76d9b55776</anchor>
      <arglist>(std::ostream &amp;stream, const Rectangle &amp;rectangle)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_PDS_Converter.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>Generic__PDS__Converter_8cc</filename>
    <includes id="Generic__PDS__Converter_8hh" name="Generic_PDS_Converter.hh" local="yes" imported="no">Generic_PDS_Converter.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>double</type>
      <name>GDALGetRasterNoDataValue</name>
      <anchorfile>Generic__PDS__Converter_8cc.html</anchorfile>
      <anchor>a087441349e8ce2285c405fabf662aeaf</anchor>
      <arglist>(GDALRasterBandH, int *)</arglist>
    </member>
    <member kind="function">
      <type>CPLErr</type>
      <name>GDALSetRasterNoDataValue</name>
      <anchorfile>Generic__PDS__Converter_8cc.html</anchorfile>
      <anchor>a763e876f9b4c3f2b4bae2816af572fd2</anchor>
      <arglist>(GDALRasterBandH, double)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_PDS_Converter.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>Generic__PDS__Converter_8hh</filename>
    <includes id="PDS__Converter_8hh" name="PDS_Converter.hh" local="yes" imported="no">PDS_Converter.hh</includes>
    <class kind="class">UA::HiRISE::Generic_PDS_Converter</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>HiPrecision_PDS_Converter.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>HiPrecision__PDS__Converter_8cc</filename>
    <includes id="HiPrecision__PDS__Converter_8hh" name="HiPrecision_PDS_Converter.hh" local="yes" imported="no">HiPrecision_PDS_Converter.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>HiPrecision_PDS_Converter.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>HiPrecision__PDS__Converter_8hh</filename>
    <includes id="Generic__PDS__Converter_8hh" name="Generic_PDS_Converter.hh" local="yes" imported="no">Generic_PDS_Converter.hh</includes>
    <class kind="class">UA::HiRISE::HiPrecision_PDS_Converter</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>HiRISE_PDS_Converter.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>HiRISE__PDS__Converter_8cc</filename>
    <includes id="HiRISE__PDS__Converter_8hh" name="HiRISE_PDS_Converter.hh" local="yes" imported="no">HiRISE_PDS_Converter.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>HiRISE_PDS_Converter.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>HiRISE__PDS__Converter_8hh</filename>
    <includes id="Generic__PDS__Converter_8hh" name="Generic_PDS_Converter.hh" local="yes" imported="no">Generic_PDS_Converter.hh</includes>
    <class kind="class">UA::HiRISE::HiRISE_PDS_Converter</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>Image_Data_Block.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>Image__Data__Block_8cc</filename>
    <includes id="Image__Data__Block_8hh" name="Image_Data_Block.hh" local="yes" imported="no">Image_Data_Block.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>Image_Data_Block.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>Image__Data__Block_8hh</filename>
    <includes id="PDS__Data__Block_8hh" name="PDS_Data_Block.hh" local="yes" imported="no">PDS_Data_Block.hh</includes>
    <class kind="class">UA::HiRISE::Image_Data_Block</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>JP2_Box.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>JP2__Box_8cc</filename>
    <includes id="JP2__Box_8hh" name="JP2_Box.hh" local="yes" imported="no">JP2_Box.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>JP2_Box.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>JP2__Box_8hh</filename>
    <class kind="class">UA::HiRISE::JP2_Box</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>JP2_Decoder.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>JP2__Decoder_8cc</filename>
    <includes id="JP2__Decoder_8hh" name="JP2_Decoder.hh" local="yes" imported="no">JP2_Decoder.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>JP2_Decoder.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>JP2__Decoder_8hh</filename>
    <class kind="class">UA::HiRISE::JP2_Decoder</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="define">
      <type>#define</type>
      <name>UUID_SIZE</name>
      <anchorfile>JP2__Decoder_8hh.html</anchorfile>
      <anchor>a5db91c4b658dc322b42959cb5c851020</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>JP2_Encoder.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>JP2__Encoder_8cc</filename>
    <includes id="JP2__Encoder_8hh" name="JP2_Encoder.hh" local="yes" imported="no">JP2_Encoder.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="define">
      <type>#define</type>
      <name>PROGRESSION_ORDER</name>
      <anchorfile>JP2__Encoder_8cc.html</anchorfile>
      <anchor>ae9f0f933c4731760729aa4d439bd82e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INCREMENTAL_FLUSH_BYTES</name>
      <anchorfile>JP2__Encoder_8cc.html</anchorfile>
      <anchor>a678ff9d78cbb2ef99edbf5cf06e24b24</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>power_of_2</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>ab4397cd73688a99073d18ba0c80359f1</anchor>
      <arglist>(unsigned int value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>JP2_Encoder.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>JP2__Encoder_8hh</filename>
    <includes id="JP2__Box_8hh" name="JP2_Box.hh" local="yes" imported="no">JP2_Box.hh</includes>
    <class kind="class">UA::HiRISE::JP2_Encoder</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>bool</type>
      <name>power_of_2</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>ab4397cd73688a99073d18ba0c80359f1</anchor>
      <arglist>(unsigned int value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>JP2_to_PDS.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/PDS_JP2/</path>
    <filename>JP2__to__PDS_8cc</filename>
    <includes id="PDS__Converters_8hh" name="PDS_Converters.hh" local="yes" imported="no">PDS_Converters.hh</includes>
    <includes id="JP2__Decoder_8hh" name="JP2_Decoder.hh" local="yes" imported="no">JP2_Decoder.hh</includes>
    <member kind="define">
      <type>#define</type>
      <name>_VERSION_</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a1c8158f4181b6031be30281a24e63011</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FILESYSTEM_PATHNAME_DELIMITER</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>ad972595337192f6bf40545ad5117a383</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>usage</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>aaec40e1c88638587b4f9b18825885b35</anchor>
      <arglist>(int exit_status=BAD_SYNTAX, bool list_descriptions=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a5d474dbfbae98dbc733874c8062c4c10</anchor>
      <arglist>(int argument_count, char **arguments)</arglist>
    </member>
    <member kind="variable">
      <type>const char *const</type>
      <name>JP2_EXTENSION</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>aa28cd6d1eb39fbb62f8ee004f04c050e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *const</type>
      <name>LABEL_EXTENSION</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>adae288b34d625c5ec47902a0f78b2a74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *const</type>
      <name>PDS_IMAGE_EXTENSION</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>ace3801e0e4b304cd30895ef529fb4c0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DEFAULT_DATA_ORDER</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>aa20d546b5297b04721780d6c1c859763</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>SUCCESS</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>abe60a9f2bde8bc2afea53b9efcf055bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>BAD_SYNTAX</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>af93cfb3a87408f3cb2796b0643a8b67e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>INVALID_ARGUMENT</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a3adcc0bab563d82c434bd785f2b7027a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>PDS_LABEL_ERROR</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a87fd75f26c93bbba0fe2798f0578c1fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NO_IMAGE_DATA</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>afbbb716cb98093d5dab00c8229ce16e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>LABEL_INCONSISTENCY</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a4e5ea5df200837673143d46a23cbac74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>LOGIC_ERROR</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a2076c994f3896133f7e555f327aef70f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NO_INPUT_FILE</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a4d21fbc1069012c5c7360e927e190379</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>EXISTING_OUTPUT_FILE</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a991934f41e46a23f998f98660c448bf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>IO_FAILURE</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a0bc6b2aba767375fef4414897c952b02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>PVL_ERROR</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>ab07b297b2cf09ed3ffd48e6fe0927b7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DECODER_ERROR</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>aac9cb6e61a0fd0499515882bcb063c1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>UNKNOWN_ERROR</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a4bb126350f7b83d9afc2225e37c7c6a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>ID</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a008afb659faa4db617717c29b61383c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>SOFTWARE_NAME_PARAMETER</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a849c44de1bb5bba118860fdf46b827a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>Program_Name</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a2f6686484cf5517d8fa4dbf8bf1f85e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char</type>
      <name>PATHNAME_DELIMITER</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a477a54382fdf84bf294890d966d72376</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>LABEL_WIDTH</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>ab3ff54b51374ea9b53c9c763a428577c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>VALUE_WIDTH</name>
      <anchorfile>JP2__to__PDS_8cc.html</anchorfile>
      <anchor>a0b9580f087e6a985a1314e83efa9b228</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Overview.doxygen</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/</path>
    <filename>Overview_8doxygen</filename>
  </compound>
  <compound kind="file">
    <name>PDS_Converter.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Converter_8cc</filename>
    <includes id="PDS__Converter_8hh" name="PDS_Converter.hh" local="yes" imported="no">PDS_Converter.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>PDS_Converter.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Converter_8hh</filename>
    <includes id="PDS__Data_8hh" name="PDS_Data.hh" local="yes" imported="no">PDS_Data.hh</includes>
    <includes id="Image__Data__Block_8hh" name="Image_Data_Block.hh" local="yes" imported="no">Image_Data_Block.hh</includes>
    <class kind="class">UA::HiRISE::PDS_Converter</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>PDS_Converters.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Converters_8cc</filename>
    <includes id="PDS__Converters_8hh" name="PDS_Converters.hh" local="yes" imported="no">PDS_Converters.hh</includes>
    <includes id="Generic__PDS__Converter_8hh" name="Generic_PDS_Converter.hh" local="yes" imported="no">Generic_PDS_Converter.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>PDS_Converter *</type>
      <name>converter_for</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>ad4204e6d28fdf565637661593015bcd1</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PDS_Converters.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Converters_8hh</filename>
    <includes id="PDS__Converter_8hh" name="PDS_Converter.hh" local="yes" imported="no">PDS_Converter.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>PDS_Converter *</type>
      <name>converter_for</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>ad4204e6d28fdf565637661593015bcd1</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PDS_Data.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Data_8cc</filename>
    <includes id="PDS__Data_8hh" name="PDS_Data.hh" local="yes" imported="no">PDS_Data.hh</includes>
    <includes id="Image__Data__Block_8hh" name="Image_Data_Block.hh" local="yes" imported="no">Image_Data_Block.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>Parameter *</type>
      <name>find_parameter</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>aeec8f83af454c90619560be7c9512432</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;pathname, bool case_sensitive=false, int skip=0, PDS_Data::Parameter_Class_Selection parameter_class=PDS_Data::ANY_PARAMETER)</arglist>
    </member>
    <member kind="function">
      <type>Parameter *</type>
      <name>remove_parameter</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>aabd4d2c38c27df970c65fac020fd563f</anchor>
      <arglist>(idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;pathname, bool case_sensitive=false, int skip=0, PDS_Data::Parameter_Class_Selection parameter_class=PDS_Data::ANY_PARAMETER)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>numeric_value</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a30e37a999ea01651f99e789dc97e3e89</anchor>
      <arglist>(const idaeim::PVL::Parameter &amp;parameter)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>string_value</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a5b723ec57eba7a70df03110ecbd4ded7</anchor>
      <arglist>(const idaeim::PVL::Parameter &amp;parameter)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>absolute_pathname</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a9da4c41c010220afa469f58d60b7c965</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>to_uppercase</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a9ec9e9c9924ce59c9d541077ec4ad009</anchor>
      <arglist>(const string &amp;a_string)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>indent</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a6e250d7e138a411cdb80b1d45a97d88d</anchor>
      <arglist>(std::string lines, int amount)</arglist>
    </member>
    <member kind="function">
      <type>idaeim::PVL::Lister *</type>
      <name>label_lister</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a7b01bf9a4d016c4be4ea787d4f28bc82</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PDS_Data.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Data_8hh</filename>
    <class kind="class">UA::HiRISE::PDS_Data</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>Parameter *</type>
      <name>find_parameter</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>aeec8f83af454c90619560be7c9512432</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;pathname, bool case_sensitive=false, int skip=0, PDS_Data::Parameter_Class_Selection parameter_class=PDS_Data::ANY_PARAMETER)</arglist>
    </member>
    <member kind="function">
      <type>Parameter *</type>
      <name>remove_parameter</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>aabd4d2c38c27df970c65fac020fd563f</anchor>
      <arglist>(idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;pathname, bool case_sensitive=false, int skip=0, PDS_Data::Parameter_Class_Selection parameter_class=PDS_Data::ANY_PARAMETER)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>numeric_value</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a30e37a999ea01651f99e789dc97e3e89</anchor>
      <arglist>(const idaeim::PVL::Parameter &amp;parameter)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>string_value</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a5b723ec57eba7a70df03110ecbd4ded7</anchor>
      <arglist>(const idaeim::PVL::Parameter &amp;parameter)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>absolute_pathname</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a9da4c41c010220afa469f58d60b7c965</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>to_uppercase</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a27c8e8dfc370766211441591f1b10784</anchor>
      <arglist>(const std::string &amp;a_string)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>indent</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a6e250d7e138a411cdb80b1d45a97d88d</anchor>
      <arglist>(std::string lines, int amount)</arglist>
    </member>
    <member kind="function">
      <type>idaeim::PVL::Lister *</type>
      <name>label_lister</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a7b01bf9a4d016c4be4ea787d4f28bc82</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PDS_Data_Block.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Data__Block_8cc</filename>
    <includes id="PDS__Data__Block_8hh" name="PDS_Data_Block.hh" local="yes" imported="no">PDS_Data_Block.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>PDS_Data_Block.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Data__Block_8hh</filename>
    <includes id="PDS__Data_8hh" name="PDS_Data.hh" local="yes" imported="no">PDS_Data.hh</includes>
    <class kind="class">UA::HiRISE::PDS_Data_Block</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>PDS_Projection_Data.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Projection__Data_8cc</filename>
    <includes id="PDS__Projection__Data_8hh" name="PDS_Projection_Data.hh" local="yes" imported="no">PDS_Projection_Data.hh</includes>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
    <member kind="function">
      <type>CPLErr</type>
      <name>GTIFMemBufFromWkt</name>
      <anchorfile>PDS__Projection__Data_8cc.html</anchorfile>
      <anchor>ac988589a6f062f9185d1de0a041c3ff6</anchor>
      <arglist>(const char *WKT, const double *geo_transform, int GCPList_size, const GDAL_GCP *GCPList, int *pointer_to_returned_size, unsigned char **pointer_to_returned_data_buffer)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PDS_Projection_Data.hh</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/libPDS_JP2/</path>
    <filename>PDS__Projection__Data_8hh</filename>
    <includes id="PDS__Data_8hh" name="PDS_Data.hh" local="yes" imported="no">PDS_Data.hh</includes>
    <includes id="JP2__Box_8hh" name="JP2_Box.hh" local="yes" imported="no">JP2_Box.hh</includes>
    <class kind="class">UA::HiRISE::PDS_Projection_Data</class>
    <class kind="struct">UA::HiRISE::PDS_Projection_Data::Projection_Definition</class>
    <class kind="struct">UA::HiRISE::PDS_Projection_Data::Projection_Definition::Required_Projection_Parameter</class>
    <class kind="struct">UA::HiRISE::PDS_Projection_Data::Projection_Definition::Default_Projection_Parameter</class>
    <namespace>UA</namespace>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="file">
    <name>PDS_to_JP2.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/PDS_JP2/</path>
    <filename>PDS__to__JP2_8cc</filename>
    <includes id="PDS__Converters_8hh" name="PDS_Converters.hh" local="yes" imported="no">PDS_Converters.hh</includes>
    <includes id="PDS__Projection__Data_8hh" name="PDS_Projection_Data.hh" local="yes" imported="no">PDS_Projection_Data.hh</includes>
    <includes id="JP2__Encoder_8hh" name="JP2_Encoder.hh" local="yes" imported="no">JP2_Encoder.hh</includes>
    <member kind="define">
      <type>#define</type>
      <name>PRODUCER_UUID</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a7dfa72bcf4b79a23cfce982d8b029637</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_VERSION_</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a1c8158f4181b6031be30281a24e63011</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FILESYSTEM_PATHNAME_DELIMITER</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>ad972595337192f6bf40545ad5117a383</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>recommended_resolution_levels</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>aee5ef0cec4672d32af74b70d3951eb6d</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>UUID</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a917e163e93766011747d1860934e7d5e</anchor>
      <arglist>(const char *signature)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>usage</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>aaec40e1c88638587b4f9b18825885b35</anchor>
      <arglist>(int exit_status=BAD_SYNTAX, bool list_descriptions=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a5d474dbfbae98dbc733874c8062c4c10</anchor>
      <arglist>(int argument_count, char **arguments)</arglist>
    </member>
    <member kind="variable">
      <type>const char *const</type>
      <name>LABEL_EXTENSION</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>adae288b34d625c5ec47902a0f78b2a74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *const</type>
      <name>JP2_EXTENSION</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>aa28cd6d1eb39fbb62f8ee004f04c050e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DEFAULT_TILE_SIZE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>ab783c106e0e70157fad23c273b9f2056</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>MIN_RESOLUTION_SIZE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a59dfdb3953f0cb7b1e8af1d18eafcea4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *const</type>
      <name>DEFAULT_PROGRESSION_ORDER</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a9d2a4651dab81822b1903e62d1d2ae4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DEFAULT_SIGNED_DATA</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>af7c108c980f67890b26ad41ec93b2fad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DEFAULT_DATA_ORDER</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>aa20d546b5297b04721780d6c1c859763</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DEFAULT_PRECINCT_SIZE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a6bef60f89f95dbe0e5bd5a79e97dfce1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DEFAULT_CODE_BLOCK_SIZE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>ab73f448722934cd6b3d2c9cf48cb68d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>DEFAULT_PRODUCER_SIGNATURE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>ad8426245b074706ba68169abe19eacc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>DEFAULT_PRODUCER_UUID</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a0abad2acf38ec0bd02fb2a097ad2ae47</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>SUCCESS</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>abe60a9f2bde8bc2afea53b9efcf055bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>BAD_SYNTAX</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>af93cfb3a87408f3cb2796b0643a8b67e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>INVALID_ARGUMENT</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a3adcc0bab563d82c434bd785f2b7027a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>PDS_LABEL_ERROR</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a87fd75f26c93bbba0fe2798f0578c1fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NO_IMAGE_DATA</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>afbbb716cb98093d5dab00c8229ce16e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>LOGIC_ERROR</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a2076c994f3896133f7e555f327aef70f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NO_INPUT_FILE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a4d21fbc1069012c5c7360e927e190379</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>EXISTING_OUTPUT_FILE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a991934f41e46a23f998f98660c448bf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>IO_FAILURE</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a0bc6b2aba767375fef4414897c952b02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>PVL_ERROR</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>ab07b297b2cf09ed3ffd48e6fe0927b7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>ENCODER_ERROR</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a61b6f86bd96f63652ba6856b231bdf8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>UNKNOWN_ERROR</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a4bb126350f7b83d9afc2225e37c7c6a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>ID</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a008afb659faa4db617717c29b61383c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>SOFTWARE_NAME_PARAMETER</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a849c44de1bb5bba118860fdf46b827a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>MAX_RESOLUTION_LEVELS</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a3600ab6b02eff260fec4aba570c13965</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>MAX_QUALITY_LAYERS</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>aac015113a3c6bd75bd083d12dd71b803</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>DEFAULT_LOSSY_QUALITY_LAYERS</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a68e583bbfd317513a4241341d07f6fb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char</type>
      <name>PATHNAME_DELIMITER</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a477a54382fdf84bf294890d966d72376</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>LABEL_WIDTH</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>ab3ff54b51374ea9b53c9c763a428577c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>VALUE_WIDTH</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a0b9580f087e6a985a1314e83efa9b228</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>Program_Name</name>
      <anchorfile>PDS__to__JP2_8cc.html</anchorfile>
      <anchor>a2f6686484cf5517d8fa4dbf8bf1f85e5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>relocate_label.cc</name>
    <path>/data/hirise07/Users/guym/HiRISE/PDS_JP2/PDS_JP2/</path>
    <filename>relocate__label_8cc</filename>
    <member kind="define">
      <type>#define</type>
      <name>_VERSION_</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a1c8158f4181b6031be30281a24e63011</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BACKUP_FILENAME_SUFFIX</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a2faf21022c8f61cda17dc9232dad2aa9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>usage</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>ab23eac7f5c579e99ab460b9ad4d2549c</anchor>
      <arglist>(const char *program_name, int exit_status=BAD_SYNTAX, bool list_descriptions=false)</arglist>
    </member>
    <member kind="function">
      <type>kdu_uint32</type>
      <name>box_type</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a1dee7d0157337ec27dc99c876ffbabab</anchor>
      <arglist>(const char *box_name)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>box_name</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>acf80717cb0d3143d5b92b0b775e5b490</anchor>
      <arglist>(kdu_uint32 box_type)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a5d474dbfbae98dbc733874c8062c4c10</anchor>
      <arglist>(int argument_count, char **arguments)</arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>SUCCESS</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>abe60a9f2bde8bc2afea53b9efcf055bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>BAD_SYNTAX</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>af93cfb3a87408f3cb2796b0643a8b67e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NO_INPUT_FILE</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a4d21fbc1069012c5c7360e927e190379</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>NO_LABEL_LOCATION</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a05d670f610ef861143086530ce9c37f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>EXISTING_BACKUP_FILE</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>ada1d8667e46e816c95a66b66ff9070ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>IO_FAILURE</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a0bc6b2aba767375fef4414897c952b02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>JP2_ERROR</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>aba1cc0c0dcf91c7f4ff91ccab2cc6962</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>ID</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a008afb659faa4db617717c29b61383c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>Program_Name</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a2f6686484cf5517d8fa4dbf8bf1f85e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *const</type>
      <name>UUID_INFO_BOX_NAME</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a6759491cbd4458297f208c6c6f8dffd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *const *const</type>
      <name>URL_BOX_NAME</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a65e19cc7a7025e212c1209cffd16a7a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>VERS_AND_FLAG_BYTES</name>
      <anchorfile>relocate__label_8cc.html</anchorfile>
      <anchor>a1958911397411eb01902a0c7b323227f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>idaeim</name>
    <filename>namespaceidaeim.html</filename>
  </compound>
  <compound kind="namespace">
    <name>UA</name>
    <filename>namespaceUA.html</filename>
    <namespace>UA::HiRISE</namespace>
  </compound>
  <compound kind="namespace">
    <name>UA::HiRISE</name>
    <filename>namespaceUA_1_1HiRISE.html</filename>
    <class kind="struct">UA::HiRISE::Point_2D</class>
    <class kind="struct">UA::HiRISE::Size_2D</class>
    <class kind="struct">UA::HiRISE::Rectangle</class>
    <class kind="class">UA::HiRISE::Generic_PDS_Converter</class>
    <class kind="class">UA::HiRISE::HiPrecision_PDS_Converter</class>
    <class kind="class">UA::HiRISE::HiRISE_PDS_Converter</class>
    <class kind="class">UA::HiRISE::Image_Data_Block</class>
    <class kind="class">UA::HiRISE::JP2_Box</class>
    <class kind="class">UA::HiRISE::JP2_Decoder</class>
    <class kind="class">UA::HiRISE::JP2_Encoder</class>
    <class kind="class">UA::HiRISE::PDS_Converter</class>
    <class kind="class">UA::HiRISE::PDS_Data</class>
    <class kind="class">UA::HiRISE::PDS_Data_Block</class>
    <class kind="class">UA::HiRISE::PDS_Projection_Data</class>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>afedd1aec3d30f99cd080405f375fff5d</anchor>
      <arglist>(std::ostream &amp;stream, const Point_2D &amp;point)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a3617777e4c6990c3a7fbdc22ab8e9931</anchor>
      <arglist>(std::ostream &amp;stream, const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a7d0829a7ea24e83475988d76d9b55776</anchor>
      <arglist>(std::ostream &amp;stream, const Rectangle &amp;rectangle)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>power_of_2</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>ab4397cd73688a99073d18ba0c80359f1</anchor>
      <arglist>(unsigned int value)</arglist>
    </member>
    <member kind="function">
      <type>PDS_Converter *</type>
      <name>converter_for</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>ad4204e6d28fdf565637661593015bcd1</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>Parameter *</type>
      <name>find_parameter</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>aeec8f83af454c90619560be7c9512432</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;pathname, bool case_sensitive=false, int skip=0, PDS_Data::Parameter_Class_Selection parameter_class=PDS_Data::ANY_PARAMETER)</arglist>
    </member>
    <member kind="function">
      <type>Parameter *</type>
      <name>remove_parameter</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>aabd4d2c38c27df970c65fac020fd563f</anchor>
      <arglist>(idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;pathname, bool case_sensitive=false, int skip=0, PDS_Data::Parameter_Class_Selection parameter_class=PDS_Data::ANY_PARAMETER)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>numeric_value</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a30e37a999ea01651f99e789dc97e3e89</anchor>
      <arglist>(const idaeim::PVL::Parameter &amp;parameter)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>string_value</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a5b723ec57eba7a70df03110ecbd4ded7</anchor>
      <arglist>(const idaeim::PVL::Parameter &amp;parameter)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>absolute_pathname</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a9da4c41c010220afa469f58d60b7c965</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>to_uppercase</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a9ec9e9c9924ce59c9d541077ec4ad009</anchor>
      <arglist>(const string &amp;a_string)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>indent</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a6e250d7e138a411cdb80b1d45a97d88d</anchor>
      <arglist>(std::string lines, int amount)</arglist>
    </member>
    <member kind="function">
      <type>idaeim::PVL::Lister *</type>
      <name>label_lister</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a7b01bf9a4d016c4be4ea787d4f28bc82</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>to_uppercase</name>
      <anchorfile>namespaceUA_1_1HiRISE.html</anchorfile>
      <anchor>a27c8e8dfc370766211441591f1b10784</anchor>
      <arglist>(const std::string &amp;a_string)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UA::HiRISE::Point_2D</name>
    <filename>structUA_1_1HiRISE_1_1Point__2D.html</filename>
    <member kind="function">
      <type></type>
      <name>Point_2D</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a48127af1e5ef6c3fbc7a44d1b723bc24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point_2D</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a8b1487fecc9f83fa9b2677a27d66ae96</anchor>
      <arglist>(const int &amp;x, const int &amp;y)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point_2D</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a4bc57f9f4f2b55b9c83382d357224456</anchor>
      <arglist>(const Point_2D &amp;point)</arglist>
    </member>
    <member kind="function">
      <type>Point_2D &amp;</type>
      <name>operator=</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>afbbafbfc13c647779f11b63d67f1eeb6</anchor>
      <arglist>(const Point_2D &amp;point)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>x</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a971a06eb44d062213dea454cf065b247</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Point_2D &amp;</type>
      <name>x</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a9eaf90993b61c23c2ed88fd50bb8f6e1</anchor>
      <arglist>(const int &amp;x_position)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>y</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a5db7363c1b8382ca9e9479dbf7cdc5f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Point_2D &amp;</type>
      <name>y</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a5ee1526e914330cfb6b69a62ef65319a</anchor>
      <arglist>(const int &amp;y_position)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>X</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>a80c0944640e62d3ed6c5419c1bcc0c88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Y</name>
      <anchorfile>structUA_1_1HiRISE_1_1Point__2D.html</anchorfile>
      <anchor>aa482c4cc86a24474e4fb19b5b5978778</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UA::HiRISE::Size_2D</name>
    <filename>structUA_1_1HiRISE_1_1Size__2D.html</filename>
    <member kind="function">
      <type></type>
      <name>Size_2D</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a7856430840c96a77e48415e100ee0508</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Size_2D</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a7c634cd06908d286bc02cffbf5a44981</anchor>
      <arglist>(const unsigned int &amp;width, const unsigned int &amp;height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Size_2D</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>ac2994df39241436dcafc13ab4f1873ae</anchor>
      <arglist>(const unsigned int &amp;side)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Size_2D</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a29a0e666cc50af9c560dc6c0757c41ef</anchor>
      <arglist>(const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>Size_2D &amp;</type>
      <name>operator=</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a55bc9526188200080c0096be3b7d1f96</anchor>
      <arglist>(const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>width</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a7b736ec9a05be5c498760d35a0406ed3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Size_2D &amp;</type>
      <name>width</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a24faa810b6f032a8c016de3bfc3d6a2e</anchor>
      <arglist>(const unsigned int &amp;width)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>height</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>aa420a28166e708e3f8b9ecc8e527fc09</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Size_2D &amp;</type>
      <name>height</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a26866a4dfac2d04faaac60527a8d8b66</anchor>
      <arglist>(const unsigned int &amp;height)</arglist>
    </member>
    <member kind="function">
      <type>unsigned long</type>
      <name>area</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>ad6c9fd4a125c3243a0a47cb434ef8cdc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>Width</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>ac84be1826e5c85da15a1e0b53fcaf561</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>Height</name>
      <anchorfile>structUA_1_1HiRISE_1_1Size__2D.html</anchorfile>
      <anchor>a872215ae3210eabe6df31eaebe21bb73</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UA::HiRISE::Rectangle</name>
    <filename>structUA_1_1HiRISE_1_1Rectangle.html</filename>
    <base>UA::HiRISE::Point_2D</base>
    <base>UA::HiRISE::Size_2D</base>
    <member kind="function">
      <type></type>
      <name>Rectangle</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a254e93337c6debb79cd318ef4139a84f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Rectangle</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a3a652786dd6b2eaa950aba2b553af471</anchor>
      <arglist>(const Point_2D &amp;position, const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Rectangle</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a35ec051235c86c3b7f99d95b26e9aeb2</anchor>
      <arglist>(const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Rectangle</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a7e2e0262c3ba4aa3855ebd3c0092424e</anchor>
      <arglist>(const int x, const int y, const unsigned int width=0, const unsigned int height=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Rectangle</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a70efb9ff7967e6a50bff0c0281a12a37</anchor>
      <arglist>(const Rectangle &amp;rectangle)</arglist>
    </member>
    <member kind="function">
      <type>Rectangle &amp;</type>
      <name>operator=</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a21ee84990881de14207868b5fc70edce</anchor>
      <arglist>(const Rectangle &amp;rectangle)</arglist>
    </member>
    <member kind="function">
      <type>Point_2D</type>
      <name>position</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a0aefe40fb0c1e0870a342fa23fa487b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Rectangle &amp;</type>
      <name>position</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>acd675ae72678cd1ff3fc21c00928e7ac</anchor>
      <arglist>(const Point_2D &amp;point)</arglist>
    </member>
    <member kind="function">
      <type>Rectangle &amp;</type>
      <name>position</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>ad6c8d07f8a9d09a8c3ecb8dcfe4964e3</anchor>
      <arglist>(const int x, const int y)</arglist>
    </member>
    <member kind="function">
      <type>Size_2D</type>
      <name>size</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a9b5933463aed8eceb5c98c045e4d71ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Rectangle &amp;</type>
      <name>size</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>aff4ff979bd203d3b17b60c08f68644ee</anchor>
      <arglist>(const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>Rectangle &amp;</type>
      <name>size</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a30f3ec41ec7bab471bc8bd2a983aaa36</anchor>
      <arglist>(const unsigned int width, const unsigned int height)</arglist>
    </member>
    <member kind="function">
      <type>Rectangle &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>structUA_1_1HiRISE_1_1Rectangle.html</anchorfile>
      <anchor>a80d8a790fb93283eee7481b74ce1c1cd</anchor>
      <arglist>(const Rectangle &amp;rectangle)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::Generic_PDS_Converter</name>
    <filename>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</filename>
    <base>UA::HiRISE::PDS_Converter</base>
    <member kind="function">
      <type></type>
      <name>Generic_PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>aa5d38096968914f5682699dcf4505c21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Generic_PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>a937925f926f83b75d1b5fc01edd44794</anchor>
      <arglist>(const std::string &amp;pathname, const char **excluded_names=NULL, const char **image_names=NULL)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>product_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>af8c05130617b27278aa401ca58bea68f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>label_recognized</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>a00b0ce21f67a4cbea23f97d15b15b38c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_PDS_JP2_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>add2690f5af2b48858fb52d6de7053afc</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const std::string &amp;JP2_pathname, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_PDS_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>ad0a1f9ebe03ac433fc2753ddfc62b02b</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const Rectangle *image_region=NULL, unsigned int resolution_level=1, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PRODUCT_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>a3ec92789ab088abdcc26327f7cdade72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>DATA_POINTER_PARAMETER_UNITS</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>a29d0e68350d9d34a81c36fddf4a1a15d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>REMOVED_PDS_PARAMETER_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>a92a02a0d92a74037f0dd87824f9033e6</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>REMOVED_PDS_JP2_PARAMETER_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>a9a130651159f990a12c97308089cbbfd</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>DEFAULT_PDS_LABEL_SIZE</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>a14150a20931c96e112896bf615771c73</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Parameter *</type>
      <name>parameter_of</name>
      <anchorfile>classUA_1_1HiRISE_1_1Generic__PDS__Converter.html</anchorfile>
      <anchor>ad12a5cd8966f39d3a62db238b76c6c77</anchor>
      <arglist>(idaeim::PVL::Aggregate &amp;parameters, const char *name, bool throw_unless_found=true)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::HiPrecision_PDS_Converter</name>
    <filename>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</filename>
    <base>UA::HiRISE::Generic_PDS_Converter</base>
    <member kind="function">
      <type></type>
      <name>HiPrecision_PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a886bd6a65af799ac565d361085356bc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HiPrecision_PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>aea4492d64d3892ea6dcd70685a5bffd3</anchor>
      <arglist>(const std::string &amp;pathname, const char **excluded_names=NULL, const char **image_names=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>label_recognized</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a00b0ce21f67a4cbea23f97d15b15b38c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_PDS_JP2_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>add2690f5af2b48858fb52d6de7053afc</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const std::string &amp;JP2_pathname, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_PDS_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>ad0a1f9ebe03ac433fc2753ddfc62b02b</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const Rectangle *image_region=NULL, unsigned int resolution_level=1, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>product_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>af8c05130617b27278aa401ca58bea68f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>data_set_version</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a3fe243cc67ecd6244cfabc5a76974749</anchor>
      <arglist>(PDS_Data *additional_parameters)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>adjust_image_map_projection</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a424d30a3e85cafe9352a34ac6607559f</anchor>
      <arglist>(idaeim::PVL::Aggregate *image_map_projection, const Rectangle &amp;image_region, unsigned int ratio)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PRODUCT_TYPE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>ad1b935796f0effadf1a57b9824f03347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>HIPRECISION_PRODUCT_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>aaed1c02771ef1c3dd00fb41a1686b739</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>EXCLUDED_DATA_BLOCK_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a2ae48dfc86880888b65531393798c41b</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_DATA_BLOCK_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a12e86c5a6437d5563e0b0929fc32aabc</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>DEFAULT_PDS_LABEL_SIZE</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a14150a20931c96e112896bf615771c73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>UPDATE_VERSION_PARAMETER_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>ae704c493495030b1bd9e8b63ed3933eb</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>DATA_SET_VERSION_MINOR_VALUE</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>a20114ae0a3e0ef743eab5cde4cf35865</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_HEIGHT_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>af42936e02fbeb668662060e741d5c36d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_WDITH_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiPrecision__PDS__Converter.html</anchorfile>
      <anchor>ade60f34384d56e7228db2f8d2d620107</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::HiRISE_PDS_Converter</name>
    <filename>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</filename>
    <base>UA::HiRISE::Generic_PDS_Converter</base>
    <member kind="function">
      <type></type>
      <name>HiRISE_PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a811c64c708bed6a380d14ee4dd199ffc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HiRISE_PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a2455865328393dd28669568445ccb53c</anchor>
      <arglist>(const std::string &amp;pathname, const char **excluded_names=NULL, const char **image_names=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>label_recognized</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a00b0ce21f67a4cbea23f97d15b15b38c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_PDS_JP2_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>add2690f5af2b48858fb52d6de7053afc</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const std::string &amp;JP2_pathname, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_PDS_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>ad0a1f9ebe03ac433fc2753ddfc62b02b</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const Rectangle *image_region=NULL, unsigned int resolution_level=1, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>product_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>af8c05130617b27278aa401ca58bea68f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>data_set_version</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a3fe243cc67ecd6244cfabc5a76974749</anchor>
      <arglist>(PDS_Data *additional_parameters)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>adjust_image_map_projection</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a424d30a3e85cafe9352a34ac6607559f</anchor>
      <arglist>(idaeim::PVL::Aggregate *image_map_projection, const Rectangle &amp;image_region, unsigned int ratio)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PRODUCT_TYPE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>ad1b935796f0effadf1a57b9824f03347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>HIRISE_PRODUCT_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a8813488f7bd18fe43ca77e701c786a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>EXCLUDED_DATA_BLOCK_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a2ae48dfc86880888b65531393798c41b</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_DATA_BLOCK_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a12e86c5a6437d5563e0b0929fc32aabc</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>DEFAULT_PDS_LABEL_SIZE</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a14150a20931c96e112896bf615771c73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>UPDATE_VERSION_PARAMETER_NAMES</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>ae704c493495030b1bd9e8b63ed3933eb</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>DATA_SET_VERSION_MINOR_VALUE</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a20114ae0a3e0ef743eab5cde4cf35865</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_MAP_PROJECTION_GROUP_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>aa8cbe211db56b5a335545b3ba0e3c192</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PROJECTION_TYPE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a81e0f5290bb6bdfe92e50b9ad41a90dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>HORIZONATAL_OFFSET_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>ae3d3964b5f8332c8aa4999651a69ed89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>VERTICAL_OFFSET_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>ac2683ece441c14f55f1e746a766bb16e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_HEIGHT_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a6c6d5720eebe103d3195b1707cda6e8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_WDITH_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>adc042d1156b08358345c49072ba912f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PIXELS_PER_DEGREE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a46783f80544641fd023f73135bab9342</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>METERS_PER_PIXEL_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a0c3acce6b4b3baeb1d59358c5f1506ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>MINIMUM_LATITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a68458bb8ae865a7426a3e8614e736b86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>MAXIMUM_LATITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a521690bfc48d0699830a6d5c2bb6ee07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>EASTERN_LONGITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>ad8e7711f850a8bf2becbe5373c6d664f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>WESTERN_LONGITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1HiRISE__PDS__Converter.html</anchorfile>
      <anchor>a9184b4ea09861c9696ec08cde00c4455</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::Image_Data_Block</name>
    <filename>classUA_1_1HiRISE_1_1Image__Data__Block.html</filename>
    <base>UA::HiRISE::PDS_Data_Block</base>
    <member kind="function">
      <type></type>
      <name>Image_Data_Block</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>ad203629f5848d758fc7668d2907bcf16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Image_Data_Block</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a1c814406614e0aacf67246f6f9a2a004</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, std::ios::off_type file_offset)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Image_Data_Block</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>af5adfec4f87ed06dc014eb1d1d87981e</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;filename)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>image_bands</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a3910fe98e797a2ba476a8d619e234107</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>image_width</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a79e4660deb76c2037b5960f0a6b28a17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>image_height</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>aff0bafda7068eddd70c41d6451d29e02</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a848ba4553c8ed82663006bc895543f23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>pixel_bits</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>af53380e73e299b0925a1404e4a501133</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>signed_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a7f05047e9ffee3d5e5e8eb4273e0f86e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>MSB_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a303a65d3be039c70fc405b969f24efbd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>line_prefix_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>aa338e856be365cb30ce895fc08c7dea5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>line_suffix_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a95502742039c1f739c3006101bf5cf47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>source_filename</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a163d8d094fde2e678db4a26d649efdaf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>source_filename</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a9abaad80b2d9571dba411f3f9ce2273d</anchor>
      <arglist>(std::string &amp;pathname)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>IMAGE_BANDS_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a0c301c2bfadefaac7b4db253f6aece31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>IMAGE_WIDTH_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>af1b55853a2fe241832826d114b74b5cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>IMAGE_HEIGHT_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a43e12ff35b71ca42d86e487c5ad24cce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>PIXEL_BYTES_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a11e66affe12300deda09d5fbf9220b49</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>PIXEL_BITS_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a8dfd7bcc719f7d51067eb99f1d28fc1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>PIXEL_DATA_TYPE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a9bd4c4001a435db0d86a3cb6ea6c0053</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>UNSIGNED_PIXEL_TYPE_IDENTIFIER</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>af698ddd6a043eba8755e6411b8b09e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>SIGNED_PIXEL_TYPE_IDENTIFIER</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a04888e51391630b6d05d14acdfb6ce35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>LSB_PIXEL_TYPE_IDENTIFIER</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>ab77854caae5acf1e3ccafdd58e4ab423</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>MSB_PIXEL_TYPE_IDENTIFIER</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>ad9d0540ad55181eb5651b3baf6bb8ccf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>LINE_PREFIX_BYTES_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a5c425e9da10763abf61134dffaf7964b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>LINE_SUFFIX_BYTES_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a519a50b82b5a1a1df84669b21317c3c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual unsigned long long</type>
      <name>data_block_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1Image__Data__Block.html</anchorfile>
      <anchor>a31d61daf4713998efdf8fc6511bd365b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::JP2_Box</name>
    <filename>classUA_1_1HiRISE_1_1JP2__Box.html</filename>
    <member kind="typedef">
      <type>std::vector&lt; JP2_Box * &gt;</type>
      <name>JP2_Box_List</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>ac8e22910eeb29954933f588269bfa301</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JP2_Box</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>aa30f5a2821f0d31eb6ce1ccc01993bb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JP2_Box</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>afe7632e0e23cdca7023bf24ab2494ad3</anchor>
      <arglist>(unsigned int box_type, const unsigned char *data=NULL, unsigned int amount=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JP2_Box</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a591ccb4c0e9b4b20fb1efb1340adb262</anchor>
      <arglist>(unsigned int box_type, const std::string &amp;text)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~JP2_Box</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a3136e8cdc7045d3c6e7dff4598f69ec2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>type_name</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>aa5efab8061e2e94e862df13c14215fe9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>type_name</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a8b88dcb3ac697578c3fa77e58d2b6f01</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>type_code</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a9dcd8a6b453684a8d3402eb0291ea533</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>type_code</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a401533a4776130acb2b3992b0ee0a993</anchor>
      <arglist>(unsigned int box_type)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>content_amount</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>add01a1708e1486ba11f684743acd8ef2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a21f8d325ee253038bfd84c0e0a9b08ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a32af45090bd62782285ef53e71dc6a9d</anchor>
      <arglist>(const unsigned char *data, unsigned int amount=0)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>af4608d895d81f545d337831fed5b472a</anchor>
      <arglist>(const std::string &amp;text)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>locally_owned_content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a4288c77cf9681a7dd6c37100136c9e44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>attach_content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a3e534a70c1d67cf00c6aeff538a7ce57</anchor>
      <arglist>(unsigned char *data, unsigned int amount=0)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>append_content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>ac4865486f61d41e1217b64b59b34db34</anchor>
      <arglist>(const unsigned char *data, unsigned int amount)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>append_content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>ade1d075a942f48386f33ae664e75f089</anchor>
      <arglist>(const std::string &amp;text)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>add</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a17a8c47012d9a38c2637f58e87446519</anchor>
      <arglist>(JP2_Box *sub_box)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box &amp;</type>
      <name>add</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a92b88a70df0797f45fee784f6ca72505</anchor>
      <arglist>(JP2_Box &amp;sub_box)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>remove</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a0849bd0d89e6a14d79548b2210863d1b</anchor>
      <arglist>(JP2_Box *sub_box)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box_List &amp;</type>
      <name>sub_boxes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>aad15e074bf7f8f71a4ed04a64e03956f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box *</type>
      <name>container</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a2b397910f5df5a40c4abd8a6d0f779c7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>type_name</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a97b173b14bd54bb28a98dc933ca154c4</anchor>
      <arglist>(unsigned int box_type)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unsigned int</type>
      <name>type_code</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a9ee4fdef19155681d9c4ece40aac42c0</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>UUID_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a5018d3fb25e0f8e02ed2e71821728ace</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>UUID_SIZE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a5ce4658cb1645fe2a0a194d4d17e4155</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>UUID_INFO_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>aa5a41398988d5279ffc6c1bc4b51dbb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>UUID_LIST_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a36cc15b74e16bd3a70fcf905e094754c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>URL_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a8a45eb5c24171d1d4eb555f4e4040773</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>XML_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>af517e446f3748236f5e0359d6aabc9dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>ASSOCIATION_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a9c5ff677c3e609fd040d9a7a3bee144b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>LABEL_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a363f3bbc0d8414cfb6c8d070250d5190</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>INTELLECTUAL_PROPERTY_BOX_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>ab83a48de03d765e8d7a961538beef4bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Type</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a88ec70b0f678ae449a7da2670bcaa873</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned char *</type>
      <name>Content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a7c5bda85f142cf6023cd02dc37e441b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Content_Amount</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a51b024e63fa7a3140e844f0e387a0e0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Locally_Owned_Content</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>ab7e51a1bdb12dba205d6a0392ae825a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>JP2_Box *</type>
      <name>Container</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>ae90124dad3b88c0222898ba57114502d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>JP2_Box_List</type>
      <name>Sub_Boxes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Box.html</anchorfile>
      <anchor>a8e0e71ac525ef41d2395e710bbd8074c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::JP2_Decoder</name>
    <filename>classUA_1_1HiRISE_1_1JP2__Decoder.html</filename>
    <member kind="function">
      <type></type>
      <name>JP2_Decoder</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>aecb5f004b21969721296b7098dcef188</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>source</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>af68784cf3df5718934627d89ac7fb9fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Decoder &amp;</type>
      <name>source</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>adcb9cba151bced33b74acf4e5c093490</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>Size_2D</type>
      <name>image_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a659d92efb57a5bbc5c16f1ab4fdd7776</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>image_width</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a2ddc0484dfe61c2726e2136743796c65</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>image_height</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a3b840d8b60d6d77ec5538ba9436fd183</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>image_bands</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a6d11ed5e2d2a120ba70a246dced7fda7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>resolution_levels</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ab45d0666341ccedec93acee169945503</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a33e2c73da8eed5d46ffbd7187140129a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>pixel_bits</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ad11fb74db1a966c47e356037302583ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>signed_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a88339a348fe031b1f7812344fd44ac08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned char *const</type>
      <name>producer_UUID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a59cdcb96097b04b8c9c8f53daa978c20</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>URL</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a136d66a31a22886fa3aa323581029256</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>destination</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a650a7245f13215671c651146ebb794b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Decoder &amp;</type>
      <name>destination</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a3b9930a6ce652dcd7220b04567cd38c3</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>Size_2D</type>
      <name>rendered_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>aac9865153202bdd88af147add4ecec9d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>rendered_width</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a263b3b0b69962a2221b54594b7e5aa61</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>rendered_height</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a58248c90417c12af52416b7aa578c3ae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Rectangle</type>
      <name>image_region</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a1e1faf31cad20d64f315303a3e31df5b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Decoder &amp;</type>
      <name>image_region</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a6e2ee7019752b88149b3ce27cb25b8f1</anchor>
      <arglist>(const Rectangle &amp;region)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Decoder &amp;</type>
      <name>image_region</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a4967c3b0040934553a6764088e0b6cde</anchor>
      <arglist>(int x, int y, int width, int height)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>resolution_level</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a71ef3baae1a1c962e41825c7d9e532aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Decoder &amp;</type>
      <name>resolution_level</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a851f00e339b6a1671a97a701dffeb47c</anchor>
      <arglist>(unsigned int level)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>swap_pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a2e05d4202403d9a6aa6bf6e6b95269f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Decoder &amp;</type>
      <name>swap_pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>aafb5ce76065b7b645cfb856ed0770b13</anchor>
      <arglist>(bool swap_data)</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>bytes_written</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ad2343b8b2d1420304951ab97cfeeca54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ready</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a9fb588fd953e06ac889fc2789a5d3467</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>reasons</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a6b6040c233481c8cc0f48e3c35757735</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>decode</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a32a33a3f76c19a1199a2d18acfcb693e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>open</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a9e8555112049fc2b4945120b3c45f8ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_open</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a6879dafb5eadff1a2880c8a255393ef9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>write_image_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a3fb116be2a41b4c705775485b50a24bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>close</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a5ae591df94fc66ccb85cbb6565368bca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>JP2_Decoder_Error *</type>
      <name>decoder_error</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a430d76ee058f740ef9a4844978b3c088</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>static const int</type>
      <name>MAX_STRIPE_HEIGHT</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ad4f73c95431a772d5c003ad36d7621e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>UUID_INFO_BOX_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a3841d73e046880e998c7eb1f8c6d8afe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>UUID_BOX_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>aee3e067eec3b7974e418fe4aa026948a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>URL_BOX_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a7170f139f0b3e017edb013f5fca451c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>MIN_STRIPE_HEIGHT</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a715a2309a73c793ccdd161df4618bee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>DECODER_EXCEPTION</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ada030f10690ee9e2d36a31fde604e8a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::streamsize</type>
      <name>write_stripe</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ace33074e53a59c103a6693c07ca11a4b</anchor>
      <arglist>(std::ostream &amp;destination, std::streamoff file_offset, int band, int line, int lines, kdu_int16 *buffer)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::streamsize</type>
      <name>write_stripe</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a97c3f3ae55ef48955e59f8decd8fed2d</anchor>
      <arglist>(std::ostream &amp;destination, std::streamoff file_offset, int band, int line, int lines, kdu_int32 *buffer)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_resolution_and_region</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a47cdc1f9fb349dfcffe39798d1be3311</anchor>
      <arglist>(unsigned int level, const Rectangle &amp;region)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>JP2_Pathname</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a66e6e40ffd74f7af8f56aab1ca4ea774</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Image_Bands</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a49f36ecee79f46811756dbf104fda084</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Size_2D</type>
      <name>Image_Size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>aae32c6e8be8d80f60f1a09e435d8907d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Pixel_Bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a4734c597ab9f2c34af0b5b28de726113</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Pixel_Bits</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ab98584b7b8e9ee1d73b52a5df82dc1bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Signed_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a13e7208228af057e8b999bd1a24c1fa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Resolution_Levels</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>aa8c79a000474b008a27a7a83383b85f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned char *</type>
      <name>UUID_Info_UUID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a15656f0a94fcaaf3b64cbd7e72a42fb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>UUID_Info_URL</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>acaf183ce19f764cebe0d3d8c8b2ad6ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>Image_Destination</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a7801d7eb9c9ee8c52a03497674b10382</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Size_2D</type>
      <name>Rendered_Size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a96423c9163fc979b7f1226281d52b135</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Rectangle</type>
      <name>Image_Region</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a02bae32b39c9992b23fab0734aa52be2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Resolution_Level</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>a92452ac18cdd10206566c6bd98cf32b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Swap_Pixel_Bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>ac19404d9fa6b52035dcf43ac9476f87e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned long long</type>
      <name>Bytes_Written</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Decoder.html</anchorfile>
      <anchor>aa1158843d3220c30fe6f4a6a5dc04e4d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::JP2_Encoder</name>
    <filename>classUA_1_1HiRISE_1_1JP2__Encoder.html</filename>
    <member kind="function">
      <type></type>
      <name>JP2_Encoder</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a5f2e4904d68871b50684e5cad19bae01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~JP2_Encoder</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ab833e666c953689a80e086fff995f211</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>source</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af68784cf3df5718934627d89ac7fb9fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>source</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a388d8933c2770d1e589c44e176e5c008</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>destination</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a650a7245f13215671c651146ebb794b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>destination</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a51e912443daf093e90360af1c487fca6</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>PDS_label_pathname</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a4b44903f41b37a92143a9e7494986f1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>PDS_label_pathname</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>adc108c2336ffa6fa51f3ec1c2bb8ed15</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>std::streamoff</type>
      <name>image_data_location</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a913a8f023096aaacf45caff9536496e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>image_data_location</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a9ef6359dab40ccce37ffc1ed7cc8865d</anchor>
      <arglist>(std::streamoff file_offset)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>image_bands</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a6d11ed5e2d2a120ba70a246dced7fda7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>image_bands</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a77ddca67765cbaee2babb0cd858b30a0</anchor>
      <arglist>(unsigned int bands)</arglist>
    </member>
    <member kind="function">
      <type>const Size_2D</type>
      <name>image_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ae09ac58cd76e76e0f92f327ca13cc565</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>image_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a35bd5642f28ef01cdcb6a0c658d1ffe0</anchor>
      <arglist>(const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a33e2c73da8eed5d46ffbd7187140129a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a9ce3adca2743985466da7f21fc3e166a</anchor>
      <arglist>(unsigned int bytes_per_pixel)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>pixel_bits</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ad11fb74db1a966c47e356037302583ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>pixel_bits</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aaaabc6b0b848cca0432d7c1287a35090</anchor>
      <arglist>(unsigned int bits_per_pixel)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>signed_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a88339a348fe031b1f7812344fd44ac08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>signed_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ae270d8a0b5c84df3f2b34b52168b3b5e</anchor>
      <arglist>(bool data_is_signed)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>MSB_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a0006baa340d89ef04dec9eef090e73e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>MSB_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af3137e909e703c402edd9c84139f0ced</anchor>
      <arglist>(bool data_is_MSB)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>swap_pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a2e05d4202403d9a6aa6bf6e6b95269f7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>swap_pixel_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a4a8cf571c66595c0ebaeb698e873b91b</anchor>
      <arglist>(bool swap_data)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>line_prefix_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aa0a8cad18059e4be9f4a8b29e8f53064</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>line_prefix_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ad9b8ff5bb928bb0564a9784b8a1a98ce</anchor>
      <arglist>(unsigned int prefix_bytes)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>line_suffix_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a965a1ccec81139acad00a81d817fb845</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>line_suffix_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a84d16faa1a743e4d6bfdc7dd5db99d4a</anchor>
      <arglist>(unsigned int suffix_bytes)</arglist>
    </member>
    <member kind="function">
      <type>const Size_2D</type>
      <name>tile_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a7d599f4054730d600fcd10e2667220ea</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>tile_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ae41aa17eab48bbf469f3300ba71e8001</anchor>
      <arglist>(const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>resolution_levels</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ab45d0666341ccedec93acee169945503</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>resolution_levels</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ab28b3a1ba0acfa0e4d4656d7bab88285</anchor>
      <arglist>(unsigned int resolution_levels)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>quality_layers</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a4683d5be0bce5d470a1b62036da419bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>quality_layers</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a5e54f8fc9ef8bab14b37e39107cce867</anchor>
      <arglist>(unsigned int quality_layers)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>bit_rate</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aef6fb21fbb4d9db06b8257ebd80f07d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>bit_rate</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a10ff3533a1a3257f0477b456bd39544b</anchor>
      <arglist>(double rate)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>progression_order</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ad485b3a84b801c2daad65ce6b39d3a18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>progression_order</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ad2d84621ce1d3b8aa7ebee00da10cf05</anchor>
      <arglist>(const std::string &amp;progression)</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; Size_2D &gt;</type>
      <name>precinct_sizes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af5cbdefdbb4be391b6b432405d6d2519</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Size_2D</type>
      <name>precinct_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ae354720248d512b8766278e70abaeee0</anchor>
      <arglist>(unsigned int resolution_level=0) const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>precinct_sizes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>addd435a9391ec692a1412e74282baf24</anchor>
      <arglist>(const std::vector&lt; Size_2D &gt; &amp;sizes)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>precinct_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ade2bcf93cd74809fe3cefd75b390e486</anchor>
      <arglist>(const Size_2D &amp;size, unsigned int resolution_level=0)</arglist>
    </member>
    <member kind="function">
      <type>const Size_2D</type>
      <name>code_block_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a0243d53b14a0439f1cae3db6c9ee9358</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>code_block_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af6a7cff5dc1aa4657008d27ea9a95657</anchor>
      <arglist>(const Size_2D &amp;size)</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box::JP2_Box_List &amp;</type>
      <name>added_boxes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a491c98921fc6b49e8c691b81cd321526</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>add_box</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aaae5a22d69b2509096241875e62799f8</anchor>
      <arglist>(JP2_Box *box)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>remove_box</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ab9bcc6b0e7da6d06345282d187ecf09d</anchor>
      <arglist>(JP2_Box *box)</arglist>
    </member>
    <member kind="function">
      <type>const unsigned char *</type>
      <name>producer_UUID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af80775fd0d8ea77c52ac6da0bc06f189</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>producer_UUID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aa0f96307301569db0471e02d32183a88</anchor>
      <arglist>(const unsigned char *id)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>comment</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ac1b5a31a17f179a84ecb73e9bf3642d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>comment</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a6a4255b963d6fefee47b11c98adc75b8</anchor>
      <arglist>(const std::string &amp;text)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ready</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a9fb588fd953e06ac889fc2789a5d3467</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>reasons</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a6b6040c233481c8cc0f48e3c35757735</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>needs</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ade0a9291ae40251f86112adea19a74f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder_Error *</type>
      <name>encoder_error</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a30c6ff0a80b4e2ce411c9246280a5cfb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>encode</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>abfcd8471a23cac1fd9d3085f0229b574</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>open</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a9e8555112049fc2b4945120b3c45f8ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>write_header</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ac7e141a4e537928bda2dbb518eb939d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>write_user_boxes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a8f22286f6663ef73fe1a7b89998177e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>write_codestream</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ab24dbea39f05c67225df966ad43c3fe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>incremental_flush_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aff5f6a64cf854d5ce691bd448a3238ac</anchor>
      <arglist>(long long bytes)</arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>incremental_flush_bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a266e86ba886aa744a0c057fc440fc2ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Encoder &amp;</type>
      <name>incremental_flush_lines</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af9d96c119f5f908abcce2967095dabf6</anchor>
      <arglist>(unsigned int lines)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>incremental_flush_lines</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a2094275c450d0a247bfd79c5069893dd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>long long</type>
      <name>close</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a00e96507d9d7dc0a02871cb887c07d0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>invalid_precinct_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ae113ecab710857fcc815a4a6a65f2ea3</anchor>
      <arglist>(const std::vector&lt; Size_2D &gt; &amp;sizes)</arglist>
    </member>
    <member kind="variable">
      <type>static const int</type>
      <name>MAX_STRIPE_HEIGHT</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ad4f73c95431a772d5c003ad36d7621e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>static const int</type>
      <name>NEEDS_DESTINATION</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a067b41e100a29425d2d7227c4b064f0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>static const int</type>
      <name>NEEDS_IMAGE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a9f0d19db9a16d8361676754e47ad9263</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>DEFAULT_RESOLUTION_LEVELS</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a5ec2f6e6af4998a2efa54dfd79184bfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>MAX_RESOLUTION_LEVELS</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a0ca02aed38299337deec61bad8da7ae3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>MAX_QUALITY_LAYERS</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a4f7cb36b13133ed8eaf943b657df007a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>UUID_INFO_BOX_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a3841d73e046880e998c7eb1f8c6d8afe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>UUID_BOX_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aee3e067eec3b7974e418fe4aa026948a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>UUID_SIZE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a705430f772633a96a0749d0ae5026af3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>URL_BOX_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a7170f139f0b3e017edb013f5fca451c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>MIN_STRIPE_HEIGHT</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a715a2309a73c793ccdd161df4618bee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>NEEDS_SOURCE</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a566deca2eac11d42545ad397896ef5a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>ENCODER_EXCEPTION</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ad73d471ed6b506e20009c299afdb06e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>read_stripe</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ac3be8a517e15c1998fceae21f40ffe2d</anchor>
      <arglist>(std::istream &amp;source, int band, int line, int lines, kdu_int16 *buffer)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>read_stripe</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>af1776da41f5bf22ae33f904a42f34859</anchor>
      <arglist>(std::istream &amp;source, int band, int line, int lines, kdu_int32 *buffer)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>Image_Source</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a357fbcda81e64a96beb566c97ffb020e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>JP2_Pathname</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a66e6e40ffd74f7af8f56aab1ca4ea774</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::streamoff</type>
      <name>Image_Offset</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a0e95baf7a4b316aedda04edf642f414a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Image_Bands</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a49f36ecee79f46811756dbf104fda084</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Size_2D</type>
      <name>Image_Size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aae32c6e8be8d80f60f1a09e435d8907d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Line_Prefix_Bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a2b63db1c9e96299540ec15a12a58f895</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Line_Suffix_Bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a455c9a35613878c04ca12c397b5d7353</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Pixel_Bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a4734c597ab9f2c34af0b5b28de726113</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Pixel_Bits</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ab98584b7b8e9ee1d73b52a5df82dc1bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Signed_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a13e7208228af057e8b999bd1a24c1fa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>JP2_Box::JP2_Box_List</type>
      <name>Added_Boxes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a59f3e33113e888dc50fb72fe292f264a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>PDS_Label_Pathname</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a36fd2670e1bf7321f5cfeae4f37fd6be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned char *</type>
      <name>Producer_UUID</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a1da0baeb48fe273890f94b8830958cf2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>Comment</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a3cfa61d9d3fae2ec10c1563b6ffb7610</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Swap_Pixel_Bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ac19404d9fa6b52035dcf43ac9476f87e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Resolution_Levels</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aa8c79a000474b008a27a7a83383b85f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Quality_Layers</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ad929ab5214c017693634892c1b12173e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Bit_Rate</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aa6163a59a56e70b3f2718ab3845547b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>Progression_Order</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>aabc6d305a450aa821dfe4afb894f5a02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Size_2D</type>
      <name>Tile_Size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>abf884838be09e087d95d234e7b2c756f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; Size_2D &gt;</type>
      <name>Precinct_Sizes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a65f846a6b6aeb3342bc8ef125078c347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Size_2D</type>
      <name>Code_Block_Size</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>ab909ab999c43e6376c1657f371aa2e8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long long</type>
      <name>Incremental_Flush_Bytes</name>
      <anchorfile>classUA_1_1HiRISE_1_1JP2__Encoder.html</anchorfile>
      <anchor>a830cd847619f456d6a5a654f36ec0ab1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::PDS_Converter</name>
    <filename>classUA_1_1HiRISE_1_1PDS__Converter.html</filename>
    <base>UA::HiRISE::PDS_Data</base>
    <member kind="function">
      <type></type>
      <name>PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a805ea9c7a9fa3f0273a0561e503b2ac2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a3dcdd09929e6661b75805b1d440c1859</anchor>
      <arglist>(const std::string &amp;pathname, const char **excluded_names=NULL, const char **image_names=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a2e2381e4d99fe07cfe71e455b8c95139</anchor>
      <arglist>(const PDS_Converter &amp;converter)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual PDS_Converter &amp;</type>
      <name>operator=</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a13844bb28fdf404c46343632ab58e87f</anchor>
      <arglist>(const PDS_Converter &amp;converter)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PDS_Converter</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a28fffb73dbd5ab78ef9546786a19fdcf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>write_PDS_JP2_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a8e3aa23636915345720f242ff05cec85</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const std::string &amp;JP2_pathname, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>write_PDS_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a8fa73bee2b6401e7b842bfc1bebc4047</anchor>
      <arglist>(const std::string &amp;PDS_label_pathname, const Rectangle *image_region=NULL, unsigned int resolution_level=1, const char **removed_parameter_names=NULL, PDS_Data *additional_parameters=NULL)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>product_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>af8c05130617b27278aa401ca58bea68f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>label_recognized</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a71867d28b5df2ca483f70dc4a82207d2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function">
      <type>PDS_Converter &amp;</type>
      <name>label_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a26bc403afda8aec861030c84ade52034</anchor>
      <arglist>(unsigned int size)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>label_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>acdce99bb9fb6be5fd896d1403aaa5885</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PDS_Data::PDS_Data_Block_List *</type>
      <name>data_blocks</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>ab3a672aab60ce43dd74083ace4cc9359</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>refresh_data_blocks</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a279fa8ff11e78650edbec074d8f6a30e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image_Data_Block *</type>
      <name>image_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a0c34e2b02bb30baf980bdcbfd948a53a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PDS_Converter &amp;</type>
      <name>excluded_data_block_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>ae46946d4a41ee3a9314d0a3e13c76cec</anchor>
      <arglist>(const char **names)</arglist>
    </member>
    <member kind="function">
      <type>const char **</type>
      <name>excluded_data_block_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a0aa542880941d663ba72719b03ce0e7b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PDS_Converter &amp;</type>
      <name>image_data_block_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a6c94b3989668eda3b4f2a5803a9b2bf5</anchor>
      <arglist>(const char **names)</arglist>
    </member>
    <member kind="function">
      <type>const char **</type>
      <name>image_data_block_names</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a0a584ea1334531e0587aefae0ab55642</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>idaeim::PVL::Aggregate *</type>
      <name>PDS_JP2_image_parameters</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>af0a9840c1be67d0452a7efa7dc85405e</anchor>
      <arglist>(const std::string &amp;JP2_pathname)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>write_label</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a336e5aef7e982f641436c3a4d39148e0</anchor>
      <arglist>(const std::string &amp;pathname, PDS_Data &amp;label, idaeim::PVL::Lister *lister=NULL, bool pad_label=false)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>DEFAULT_PRODUCT_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a0b9196371046b8bb8dfe1738ad291ddb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>UNCOMPRESSED_FILE_PARAMETERS_GROUP</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a7dfecd7a50b3a35e23f9e6d6b940254e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>COMPRESSED_FILE_PARAMETERS_GROUP</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a408bf30cb000bd2140db1c096cc2d565</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>GeoTIFF_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a27b1dc45ccacc525b63e3b8dbb39f902</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>GML_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a95475ca051709101d8896cd0c1f3eaab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>NO_VERSION_CHANGE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>aaeaea370fbfad67d8ba55eb4a28cc29b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>clear_data_blocks</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>aa9dee14bdda2a433bd84cd9f7a71dc7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char **</type>
      <name>Excluded_Data_Block_Names</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>aee0cbbf9d216795b1fc11fe65985c6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PDS_Data::PDS_Data_Block_List *</type>
      <name>Data_Blocks</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>af7f47217f681cb880425c0c01fda0354</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char **</type>
      <name>Image_Data_Block_Names</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>acc3f2f3cdf097a5f9898633e15b54cee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Image_Data_Block *</type>
      <name>IMAGE_Data_Block</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>a551ddcada57c12041245309272d31ea7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>Label_Size</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Converter.html</anchorfile>
      <anchor>aeb7b6b6e875ee6ef5b121cf3fbebe076</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::PDS_Data</name>
    <filename>classUA_1_1HiRISE_1_1PDS__Data.html</filename>
    <base>idaeim::PVL::Aggregate</base>
    <member kind="enumeration">
      <name>Parameter_Class_Selection</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a1c8b7158935340fa1213c00ad41e02eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AGGREGATE_PARAMETER</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a1c8b7158935340fa1213c00ad41e02ebaafdebfa5ebe93409df76e8b04dd2f3c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ANY_PARAMETER</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a1c8b7158935340fa1213c00ad41e02ebae496bfe8810416146f7089bc0463c22f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ASSIGNMENT_PARAMETER</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a1c8b7158935340fa1213c00ad41e02eba108237036091e679bc1c1d581c896d1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; PDS_Data_Block * &gt;</type>
      <name>PDS_Data_Block_List</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a79323ef419b3fabebc6279d2bc37bbb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>ac08698ffa8771ec6e498a010bfae7cf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>addeea4c4d8ca63559e24536c57115b4c</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a3bd668da0c107364554ad210aab20acb</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;detached)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a95ac8f1579a873b831249c3d4997dd65</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function">
      <type>PDS_Data_Block_List *</type>
      <name>data_blocks</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a8831fb4f315963432f5780cc0a780d9e</anchor>
      <arglist>(const char **excluded=NULL, const char **image_block_names=NULL)</arglist>
    </member>
    <member kind="function">
      <type>idaeim::PVL::Parameter *</type>
      <name>find_parameter</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a9671cb319ba150c9c1d17d5114298ef7</anchor>
      <arglist>(const std::string &amp;pathname, bool case_sensitive=false, int skip=0, Parameter_Class_Selection parameter_class=ANY_PARAMETER) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual PDS_Data &amp;</type>
      <name>parameters</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a50fe486323b78840f9ee86883348b14b</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual PDS_Data &amp;</type>
      <name>parameters</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a3b791f3813b0dc2496a2b8b22a40dcaf</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters)</arglist>
    </member>
    <member kind="function">
      <type>idaeim::PVL::Parameter *</type>
      <name>remove_parameter</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a842ec40efe27692bb2a4b7e95e5750c2</anchor>
      <arglist>(const std::string &amp;pathname, bool case_sensitive=false, int skip=0, Parameter_Class_Selection parameter_class=ANY_PARAMETER)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parameter_value</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a746f868c702aa2019a68351be0760e94</anchor>
      <arglist>(const std::string &amp;pathname, T &amp;value, bool case_sensitive=false, int skip=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>numeric_value</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a09875d6d9d8032d4e5647b32349fefb3</anchor>
      <arglist>(const std::string &amp;pathname, bool case_sensitive=false, int skip=0) const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>string_value</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a62f3e2249877c6b432b2b0a8ca00580c</anchor>
      <arglist>(const std::string &amp;pathname, bool case_sensitive=false, int skip=0) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image_Data_Block *</type>
      <name>image_data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>ac7f72e061ac91642e4b1a15f6e5217a1</anchor>
      <arglist>(PDS_Data_Block_List *data_block_list)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PDS_ID_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>acfe37b1297d366625b2e9768f5e62868</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>RECORD_TYPE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a748ae2be69f195c3168f0eaea5d3d370</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>BYTE_RECORD_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a7731723058c3268daf812a17a06d944b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>FIXED_LENGTH_RECORD_TYPE</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a1edca8c96c277165fcd79d8e251899ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>LABEL_RECORDS_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a81f37a1d898591dbf65a62be1ffd3ca5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>RECORD_BYTES_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>acde598782313b6aad2cc6662f9319152</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>FILE_RECORDS_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a07553b3fb74ae82fa8f4689cc0c8b421</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>INTERCHANGE_FORMAT_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a92560c9e556ce0f832aa43e13e2f0815</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_DATA_BLOCK_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>ab7da4c94a5c59ae6954e7d23132055c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>BYTES_UNITS</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a66c7c6e91797795d061a6e2c94240352</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char</type>
      <name>RECORD_POINTER_PARAMETER_MARKER</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data.html</anchorfile>
      <anchor>a2465375fba1eae4cde32e1d269e0f813</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::PDS_Data_Block</name>
    <filename>classUA_1_1HiRISE_1_1PDS__Data__Block.html</filename>
    <base>UA::HiRISE::PDS_Data</base>
    <member kind="function">
      <type></type>
      <name>PDS_Data_Block</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a6611942f68b249a66c2d7de2f4e1287d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Data_Block</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>aa0b141934f6b735d36c252181c931a67</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, std::ios::off_type file_offset)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Data_Block</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a1bbe2ce6cbfb3c221b51890e217a0085</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters, const std::string &amp;filename)</arglist>
    </member>
    <member kind="function">
      <type>std::ios::off_type</type>
      <name>location</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a2c549559e7f6bf2e2f7398ae47e2d686</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned long long</type>
      <name>size</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a4a402b57bf1a44aec3e1207879b18d17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>BLOCK_WIDTH_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a77e521e8c190d3095cea2dc77aef4d0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>BLOCK_HEIGHT_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a39510ad8470f9b75c228e7faf71078d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual unsigned long long</type>
      <name>data_block_size</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a31d61daf4713998efdf8fc6511bd365b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::ios::off_type</type>
      <name>Location</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>acd4f749facc71d94850878446467c6d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned long long</type>
      <name>Size</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Data__Block.html</anchorfile>
      <anchor>a254f9ca5c1e1232788dedebd142044aa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>UA::HiRISE::PDS_Projection_Data</name>
    <filename>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</filename>
    <base>UA::HiRISE::PDS_Data</base>
    <class kind="struct">UA::HiRISE::PDS_Projection_Data::Projection_Definition</class>
    <member kind="enumeration">
      <name>Projection_Type</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UNKNOWN_PROJECTION</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa0fc6cca87defa42b98c8f1796c05c4bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EQUIRECTANGULAR</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa28bea395a5cde49bc5a721d5ddbd5392</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>POLAR_STEREOGRAPHIC</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44faaa7c671997d2bc16ae2731b5eeb998c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ALBERS</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa2cae54ebd8129eb3520098f7f92bfedd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BONNE</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fab67e5684561ee82a5a54e378be35edb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CYLINDRICAL_EQUAL_AREA</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa88046a92015c8a7f36ef0a78c009e18d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>GNOMONIC</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa053be5b59712c7827fb64ccfff34e449</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAMBERT_AZIMUTHAL_EQUAL_AREA</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa3af904b603a9f424a822024ad60c1c3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAMBERT_CONFORMAL_CONIC</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fafabe72568cc66e96877b301b8d3e4a0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MERCATOR</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44faddc5ad3753aaf14d653a4b635abcef6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MOLLWEIDE</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fabddf36d2c19ac8b05e75a80f97fb51e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OBLIQUE_CYLINDRICAL</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa5a3b7691e7262eef441d35307c683d9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ORTHOGRAPHIC</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fae7bf29f117630a30ba5ffc75b33ac624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SINUSOIDAL</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa57192b70b0c04faf4397674b0dfb5093</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STEREOGRAPHIC</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa8779ef52d7afd5a2c6e162514c210366</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TRANSVERSE_MERCATOR</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa02697db0c50798dcab18abd6f84cd882</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VANDERGRINTEN</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fa2c6bbce7db0960d006ac219c0b2370fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOTAL_PROJECTION_TYPES</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a87a0445356181e2e247b2102b5fcf44fae1a36c534f950f6173e01c3c4b1a7958</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Projection_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ac7ba4291473cbe43d00b5bdd4eaeebba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Projection_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>acf03333d4f6bb318001d0edcdbb784b9</anchor>
      <arglist>(const PDS_Data &amp;PDS_data)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PDS_Projection_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a46936da9917698026971462d41749fda</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PDS_Projection_Data</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ad95810b1d4118279848c74a584e615ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual PDS_Data &amp;</type>
      <name>parameters</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a50fe486323b78840f9ee86883348b14b</anchor>
      <arglist>(const std::string &amp;pathname)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual PDS_Data &amp;</type>
      <name>parameters</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a3b791f3813b0dc2496a2b8b22a40dcaf</anchor>
      <arglist>(const idaeim::PVL::Aggregate &amp;parameters)</arglist>
    </member>
    <member kind="function">
      <type>const double *</type>
      <name>geo_transform</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>afad1364683e784693b63dcb53161a193</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>OGRSpatialReference *</type>
      <name>spatial_reference</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ad961ff277bb3de09072578d3ff0ad7f5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Projection_Type</type>
      <name>projection_type</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a4bd44d892621e06c0c497210a0d582a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>projection_name</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>aae3cf6d8c0faa7cb65b7031607bfeed9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PDS_Projection_Data &amp;</type>
      <name>initialize_geo_transform</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a97c7b7c90ec746d26f835d5d98b30ae6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PDS_Projection_Data &amp;</type>
      <name>initialize_spatial_reference</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a76c4061d64b475bfc23cd2d6acd3e8e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>JP2_Box *</type>
      <name>JP2_GeoTIFF</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a286836bb4e5db180830b38c60131d849</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>JP2_Box *</type>
      <name>JP2_GML</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a9b5ee0f4215d0993d988f274eb2e68d3</anchor>
      <arglist>(unsigned int image_width=0, unsigned int image_height=0) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>named_in_list</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>af7c7b8085cc1fae8b6f8df6bca865ea6</anchor>
      <arglist>(std::string name, const char *const *aliases)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Projection_Type</type>
      <name>projection_type</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>af23e199324dec4fe9ef10fe051842190</anchor>
      <arglist>(const std::string &amp;projection_name)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>ID</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>af226ef210c4d2bc1c3fa77146e691a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PLANET_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a8fdbea796cf4cc852892cc6da635f1c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_MAP_PROJECTION_GROUP_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>aa8cbe211db56b5a335545b3ba0e3c192</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PROJECTION_TYPE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a81e0f5290bb6bdfe92e50b9ad41a90dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>COORDINATE_SYSTEM_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ac08d14fd6ec5a9501da199de7e479a0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>LATITUDE_TYPE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>aaff6f9076422b1ff120676ac71e1f600</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>HORIZONATAL_OFFSET_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ae3d3964b5f8332c8aa4999651a69ed89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>VERTICAL_OFFSET_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ac2683ece441c14f55f1e746a766bb16e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_HEIGHT_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a6c6d5720eebe103d3195b1707cda6e8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>IMAGE_WIDTH_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a1d177f71e0f51567c781c9deffe772b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PIXELS_PER_DEGREE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a46783f80544641fd023f73135bab9342</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PIXEL_SIZE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a639b37504c2bc60653c6af56ec3cbb68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>SEMI_MAJOR_RADIUS_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ad8d23d603fe7f02c433966dcc98fe7bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>SEMI_MINOR_RADIUS_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a95a1d8900a3dcd61886f3a4c884a2d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>FIRST_STANDARD_PARALLEL_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>af81216290c94283eb0ba8e8c6f249a2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>SECOND_STANDARD_PARALLEL_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>aee9b8c06964f11ccc712e95f649ba67c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>CENTER_LONGITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a6f3ce261842b02c15c35f186d237c2c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>CENTER_LATITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a2dcec6cc0594d9d2e60447c3740904aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>MINIMUM_LATITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a68458bb8ae865a7426a3e8614e736b86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>MAXIMUM_LATITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a521690bfc48d0699830a6d5c2bb6ee07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>MINIMUM_LONGITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a268f5d83538c2576f6b1ee04f59cbf53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>MAXIMUM_LONGITUDE_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a2df8c8abfb9cb307c033130da576a9ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>PROJECTION_ROTATION_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ab24024e8b0d0f5545c1e3cf4e3381c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>MISSING_CONSTANT_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a421a9377d75bd65052333f3b63a719b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *</type>
      <name>GDAL_NODATA_PARAMETER_NAME</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a1d01591f66e26b31249cf7be097a7ad1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const Projection_Definition</type>
      <name>Projection_Definitions</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>af9849f380fe15cb9491b3e6e5d0a4abb</anchor>
      <arglist>[TOTAL_PROJECTION_TYPES]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>DEFAULT_GEO_TIFF_TRANSFORM</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>afe8aada3529b1993ab2062563dd50283</anchor>
      <arglist>[6]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned char</type>
      <name>GEO_TIFF_UUID</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a366b6258ac600fb1fb5bdf5a2bf33206</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>Projection_Name</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a301b01da6b59ab6f8ce94ea474dfea44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Projection_Type</type>
      <name>Projection_Type_Code</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>aa7b97afcf530b4fa95e83e300d0bed5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>OGRSpatialReference *</type>
      <name>Spatial_Reference</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>a5ab024ce5b01f79316904b4378efb024</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Geo_Transform</name>
      <anchorfile>classUA_1_1HiRISE_1_1PDS__Projection__Data.html</anchorfile>
      <anchor>ae89b6d71386c71b606225745624e6ef3</anchor>
      <arglist>[6]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UA::HiRISE::PDS_Projection_Data::Projection_Definition</name>
    <filename>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition.html</filename>
    <class kind="struct">UA::HiRISE::PDS_Projection_Data::Projection_Definition::Default_Projection_Parameter</class>
    <class kind="struct">UA::HiRISE::PDS_Projection_Data::Projection_Definition::Required_Projection_Parameter</class>
    <member kind="variable">
      <type>Projection_Type</type>
      <name>Code</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition.html</anchorfile>
      <anchor>aab345a9327c3713f5ead134b8b5ceee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>Aliases</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition.html</anchorfile>
      <anchor>a977b4230b78145df6bb74ccf383234ae</anchor>
      <arglist>[MAX_ARRAY_ENTRIES]</arglist>
    </member>
    <member kind="variable">
      <type>struct UA::HiRISE::PDS_Projection_Data::Projection_Definition::Required_Projection_Parameter</type>
      <name>Required_Parameters</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition.html</anchorfile>
      <anchor>a779542499f16f34bab169cd83053aae5</anchor>
      <arglist>[MAX_ARRAY_ENTRIES]</arglist>
    </member>
    <member kind="variable">
      <type>struct UA::HiRISE::PDS_Projection_Data::Projection_Definition::Default_Projection_Parameter</type>
      <name>Default_Parameters</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition.html</anchorfile>
      <anchor>a13e59e783834c5e30cdff37850becdef</anchor>
      <arglist>[MAX_ARRAY_ENTRIES]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>MAX_ARRAY_ENTRIES</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition.html</anchorfile>
      <anchor>a7a7101681f1f0ea53694f0591800ae51</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UA::HiRISE::PDS_Projection_Data::Projection_Definition::Default_Projection_Parameter</name>
    <filename>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition_1_1Default__Projection__Parameter.html</filename>
    <member kind="variable">
      <type>const char *</type>
      <name>SRS_Parameter_Name</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition_1_1Default__Projection__Parameter.html</anchorfile>
      <anchor>ac89fd7638ee250e813a0a59e6782c315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Value</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition_1_1Default__Projection__Parameter.html</anchorfile>
      <anchor>a7b7e5af44fffe84c91c63ba0781ffdb3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>UA::HiRISE::PDS_Projection_Data::Projection_Definition::Required_Projection_Parameter</name>
    <filename>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition_1_1Required__Projection__Parameter.html</filename>
    <member kind="variable">
      <type>const char *</type>
      <name>SRS_Parameter_Name</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition_1_1Required__Projection__Parameter.html</anchorfile>
      <anchor>ac89fd7638ee250e813a0a59e6782c315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>PDS_Parameter_Name</name>
      <anchorfile>structUA_1_1HiRISE_1_1PDS__Projection__Data_1_1Projection__Definition_1_1Required__Projection__Parameter.html</anchorfile>
      <anchor>a94a2c22080c4a0ee59f970b92190df75</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
