#	UA HiRISE Observation Library tests
#
#	gmake syntax
#
#	CVS ID:	Makefile,v 1.8 2007/12/15 03:25:16 castalia Exp

SUBSYSTEM				=	PDS_JP2
TITLE					=	$(SUBSYSTEM) - unit tests
R := R
MAKEFILE_REVISION		:=	1.8

PROJECT_ROOT			=	../../..

#	Programs:

APPLICATIONS			=	PDS_Test_Image \
							JP2_box_type


#	Libraries:

#	PVL library.
PVL_INCLUDE				=	-I$(IDAEIM_ROOT)/include
PVL_LIBRARY				=	-L$(IDAEIM_ROOT)/lib \
								-lPVL$(64) \
								-lString$(64) \
								-lidaeim$(64)

#	If GDAL support for Geo_TIFF and GML JP2 boxes is to be included,
#	uncomment the next line.
GDAL					=	GDAL
GDAL_SUPPORT			=	-DINCLUDE_GDAL
GDAL_INCLUDE			=	-I/opt/pub/include
GDAL_LIBRARY			=	-L/opt/pub/lib -lgdal

ifeq ($(strip $(GDAL)),GDAL)
APPLICATIONS			+=	test_PDS_Projection_Data

#	Kakadu JPEG2000 library:
KAKADU_INCLUDE			=	-I$(KAKADU_ROOT)/include
KAKADU_LIBRARY			=	-L$(KAKADU_ROOT)/lib \
								-lkdu_a$(64) \
								-lkdu$(64) \
								-lpthread

test_PDS_Projection_Data:	LIBRARIES	+=	\
							-L../../lib$(SUBSYSTEM) \
								-l$(SUBSYSTEM)$(64) \
							-L$(IDAEIM_ROOT)/lib \
								-lPVL$(64) \
								-lString$(64) \
								-lidaeim$(64) \
							-L$(PIRL_ROOT)/lib \
								-lPIRL++$(64) \
							$(KAKADU_LIBRARY) \
							$($(GDAL)_LIBRARY)
endif

LIBRARIES				+=	$(PVL_LIBRARY)


#	Include files:

INCLUDE 				=	-I../../lib$(SUBSYSTEM) \
							-I$(IDAEIM_ROOT)/include \
							$($(GDAL)_INCLUDE)

					
CPPFLAGS 				=	-D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64


#	Targets:

64_BIT_BUILDS		=	true
64_BIT_ONLY			=	true

#	No HiRISE subsystem directories are to be created at installation.
NO_CONFIG_DIR		=	true
NO_DATA_DIR			=	true
NO_LOGS_DIR			=	true

all:
.all:				.applications

#	DEBUG
debug:				.applications

#	Installation:

.install:			.bin_install

.bin_install:		.applications_install


#	Cleaning:

.dist_clean:		clean_links

clean_links:
	-$(RM) -rf VERSION docs


#	Project Makefile configuration.
include				$(PROJECT_ROOT)/Build/Makefile.conf


