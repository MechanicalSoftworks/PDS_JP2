#	UA HiRISE libPDS_JP2
#
#	gmake syntax
#
#	CVS ID: Makefile,v 1.10 2013/08/03 02:05:45 guym Exp

SUBSYSTEM				=	PDS_JP2
TITLE					=	$(SUBSYSTEM) - lib$(SUBSYSTEM)
R := R
MAKEFILE_REVISION		:=	1.10

PROJECT_ROOT			=	../..

64_BIT_BUILDS			=	true
64_BIT_ONLY				=	true
NO_CONFIG_DIR			=	true
NO_DATA_DIR				=	true
NO_LOGS_DIR				=	true

#	The library:

LIBRARY					=	$(SUBSYSTEM)

#	Host system architecture identification.
empty :=
space := $(empty) $(empty)
MACHINE					:=	$(subst $(space),_,$(shell uname -m))
PLATFORM				:=	$(subst $(space),_,$(shell uname -p))
OS						:=  $(subst $(space),_,$(shell uname -s))
KERNEL_RELEASE			:=	$(subst .,$(space),$(shell uname -r))
ifeq ($(PLATFORM),unknown)
PLATFORM = $(MACHINE)
endif
ifneq (,$(findstring CYGWIN, $(OS)))
OS := WIN
endif


#	Set the following macro to a positive value if incrementatal
#	codestream flushing is to be enabled by default in the JP2_Encoder
#	used by PDS_to_JP2. The value is the maximum amount of memory that
#	should be used by the codestream generation machinery before causing
#	a flush of the accumulated codestream to the output file.
#	Incremental codestream flushing can reduce the amount of runtime
#	memory requirement - which can be large for large image files - at
#	the expense of possible additional tile-parts being generated in the
#	codestream, some or all of which might be empty (this is known to
#	confuse a few decoders that do not fully implement the JPEG2000 Part
#	1 standard). A value of 0 will set the default to disable codestream
#	flushing.
#
#!!	Subsystem Makefile overrides this value.
#
#	This definition sets the incrementatal flushing threshold to 1 GB.
#INCREMENTAL_FLUSH_BYTES	?=	(1024 * 1024 * 1024)
#
#	This definition disables incrementatal flushing.
INCREMENTAL_FLUSH_BYTES		?=	0


LIBRARY_SOURCES			=	PDS_Data.cc \
							PDS_Data_Block.cc \
							Image_Data_Block.cc \
							PDS_Converter.cc \
							PDS_Converters.cc \
							Generic_PDS_Converter.cc \
							Dimensions.cc \
							JP2_Box.cc \
							JP2_Encoder.cc \
							JP2_Decoder.cc \

#	Product-specific PDS_Converters:

#	If the HiRISE_PDS_Converter is to be included,
#		uncomment the next line.
#!!	Subsystem Makefile overrides this value.
HiRISE					?=	HiRISE
ifneq ($(strip $(HiRISE)),)
PDS_CONVERTERS			+=	-DHiRISE_PDS_CONVERTER -DHiPrecision_PDS_CONVERTER
LIBRARY_SOURCES		+=	HiRISE_PDS_Converter.cc
LIBRARY_SOURCES      += HiPrecision_PDS_Converter.cc
endif


#	Libraries:

#	GDAL library.
#	If support for Geo_TIFF and GML JP2 boxes is to be included,
#		uncomment the next line.
#!!	Subsystem Makefile overrides this value.
#GDAL					?=	GDAL
GDAL_SUPPORT			=	-DINCLUDE_GDAL
GDAL_INCLUDE			=	-I$(GDAL_ROOT)/include
GDAL_LIBRARY			=	-L$(GDAL_ROOT)/lib -lgdal$(64)
ifneq ($(strip $(GDAL)),)
LIBRARY_SOURCES			+=	PDS_Projection_Data.cc
endif

#	PVL library.
PVL_INCLUDE				=	-I$(IDAEIM_ROOT)/include -I$(IDAEIM_ROOT)/include/PVL -I$(IDAEIM_ROOT)/include/Strings -I$(IDAEIM_ROOT)/include/Utility
ifeq ($(OS),WIN)
	PVL_LIBRARY				=	-L$(IDAEIM_ROOT)/lib \
									PVL$(64).lib \
									Strings$(64).lib \
									Utility$(64).lib
else
	PVL_LIBRARY				=	-L$(IDAEIM_ROOT)/lib \
									-lPVL$(64) \
									-lStrings$(64) \
									-lUtility$(64)
endif

#	Kakadu JPEG2000 library.
KAKADU_INCLUDE			=	-I$(KAKADU_ROOT)/include
ifneq ($(OS),WIN)
KAKADU_LIBRARY			=	-L$(KAKADU_ROOT)/lib \
								-lkdu_a63$(64) \
								-lkdu63$(64) \
								-lpthread
else

# ifndef 64
# KAKADU_LIBRARY			=	-L$(KAKADU_ROOT)/lib/Win32 \
								# kdu_a63R.lib \
								# kdu_v63R.lib
# else
KAKADU_LIBRARY			=	-L$(KAKADU_ROOT)/lib/x64 \
								kdu_a63R.lib \
								kdu_v63R.lib
# endif

endif

#	PIRL C++ class library.
PIRL_INCLUDE			=	-I$(PIRL_ROOT)/include
PIRL_LIBRARY			=	-L$(PIRL_ROOT)/lib \
								-lPIRL++$(64) \

#	Used to link the shared object library.
LIBRARIES				+= 	$(PVL_LIBRARY) \
							$(KAKADU_LIBRARY) \
							$($(GDAL)_LIBRARY) \
							$(PIRL_LIBRARY) 

#	Include files:
ifeq ($(OS),WIN)
LIBRARIES				+=	ADVAPI32.LIB \
							WS2_32.LIB \
							USERENV.LIB

INCLUDES 				=	$(PVL_INCLUDE) \
							$(KAKADU_INCLUDE) \
							$(PIRL_INCLUDE) \
							$($(GDAL)_INCLUDE)
else
INCLUDE 				=	$(PVL_INCLUDE) \
							$(KAKADU_INCLUDE) \
							$(PIRL_INCLUDE) \
							$($(GDAL)_INCLUDE)
endif

#	Preprocessor flags:


#	Targets:

all:
.all:				.libraries

#	DEBUG
debug:				.libraries


#	Installation:

.install:			.headers_install \
					.bin_install

.bin_install:		.libraries_install


#	Cleaning:

.dist_clean:		clean_links

clean_links:
	-$(RM) VERSION

clean_subdirectories:
	$(MAKE) -C tests .dist_clean


#	Project Makefile configuration.
include				$(PROJECT_ROOT)/Build/Makefile.conf

#	This section comes after the Makefile.conf include 
#	because $(64) and $(SHARED_LIBRARY_OBJECTS_EXT)
#	must be defined first for these targets.
 
ifneq ($(strip $(64_BIT_BUILDS)),)
CPPFLAGS 					+=	-D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
endif
PDS_Converters.o$(64):			CPPFLAGS	+=	$(PDS_CONVERTERS)
PDS_Converters.slo$(64):		CPPFLAGS	+=	$(PDS_CONVERTERS)

JP2_Encoder.o$(64):								CPPFLAGS	+=	-DINCREMENTAL_FLUSH_BYTES='$(INCREMENTAL_FLUSH_BYTES)'
JP2_Encoder.$(SHARED_LIBRARY_OBJECTS_EXT)$(64):	CPPFLAGS	+=	-DINCREMENTAL_FLUSH_BYTES='$(INCREMENTAL_FLUSH_BYTES)'
