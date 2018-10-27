#	UA HiRISE PDS_JP2
#
#	gmake syntax
#
#	CVS ID: Makefile,v 1.5 2007/07/03 21:12:37 guym Exp

MAKEFILE_REVISION		=	1.5

PROJECT_ROOT     = ..

#	Scripts, config files, etc. (non-compiled):

SCRIPTS				=	GeotiffReader

JAVA_SOURCES		=	Geotiff.java GeotiffReader.java

NO_DATA_DIR			=       true
NO_LOGS_DIR			=       true

#	Targets:

all:
.all: .java

.install: .bin_install

.bin_install: .scripts_install

#	Project Makefile configuration:
include			../../Build/Makefile.conf
