#	UA HiRISE PDS_JP2 subsystem
#
#	gmake syntax
#
#	CVS ID: Makefile,v 2.25 2014/02/03 21:09:22 guym Exp

export SUBSYSTEM		=	PDS_JP2

R := R
MAKEFILE_REVISION		:=	2.25

#	Build options:
#
#	To enable an option set its value to the option name.
#	To disable an option set its value to be empty.

#	JP2 file producer UUID signature.
#	An empty signature produces a null (a zeros) UUID.
#		Requires OSSP uuid support.
export PRODUCER_SIGNATURE		?=	
#		If no OSSP support the UUID values may be specified.
#		The UUID must be 16 8-bit, comma separated values.
export PRODUCER_UUID			?=

#	Include the HiRISE_PDS_Converter.
export HiRISE					?=	HiRISE

#	OSSP support for UUID generation.
#		Requires the OSSP uuid++ library.
export OSSP_UUID				?=	OSSP_UUID

#	GDAL support for Geo_TIFF and GML JP2 boxes.
#		Requires the gdal library with OGR and LIBTIFF support.
export GDAL						?=	GDAL

#	Default runtime values:

#	JP2_Encoder incrementatal codestream bytes flushing rate.
#		Recommended - 0 to disable
export INCREMENTAL_FLUSH_BYTES	?=	0


PROJECT_ROOT			=	..

SUBDIRECTORIES			:=	libPDS_JP2 \
							PDS_JP2 \
							util

#	Targets:

NO_CONFIG_DIR		=	true
NO_DATA_DIR			=	true
NO_LOGS_DIR			=	true

#	Subdirectories:

#	Builds the TARGET for each subdirectory.

subdirectories:		$(SUBDIRECTORIES)
$(SUBDIRECTORIES):
	$(MAKE) -C $@ $(TARGET)


.applications:		TARGET = .applications
.applications:		PDS_JP2

.libraries:			TARGET = .libraries
.libraries:			libPDS_JP2

.library:			TARGET = .library
.library:			libPDS_JP2

.shared_library:	TARGET = .shared_library
.shared_library:	libPDS_JP2


#	Installation:

.install:			TARGET = .install
.install:			subdirectories

.bin_install:		TARGET = .bin_install
.bin_install:		subdirectories
.bin_install:     TARGET = .scripts_install
.bin_install:     subdirectories

.headers_install:	TARGET = .headers_install
.headers_install:	libPDS_JP2


#	Documentation:

.docs:				.doxygen


#	Cleaning:

.clean:				TARGET = .clean
.clean:				subdirectories

.dist_clean:		TARGET = .dist_clean
.dist_clean:		dist_wipe \
					subdirectories


#	Project Makefile configuration.
include				$(PROJECT_ROOT)/Build/Makefile.conf

#	Source distribution:

#	Software distribution (needs SUBSYSTEM_VERSION from Makefile.conf).
DISTRIBUTION			=	$(SUBSYSTEM)-$(SUBSYSTEM_VERSION)
TARBALL					=	$(DISTRIBUTION).tar.gz
TARBALL_LINK			=	$(SUBSYSTEM).tar.gz

DISTRIBUTION_PLATFORM	=	$(SUBSYSTEM)-$(SUBSYSTEM_VERSION)_$(OS)-$(PLATFORM)
TARBALL_PLATFORM		=	$(DISTRIBUTION_PLATFORM).tar.gz
TARBALL_LINK_PLATFORM	=	$(SUBSYSTEM)_$(OS)-$(PLATFORM).tar.gz


KAKADU_BUILD			=	Kakadu_Build
KAKADU_VERSION			:=	$(shell grep '^[0-9]' $(KAKADU_BUILD)/VERSION)
KAKADU_TARBALL			:=	$(KAKADU_BUILD)-$(KAKADU_VERSION)-$(SUBSYSTEM_VERSION).tar.gz

#	The location for distribution files.
DIST_DIR				?=	/data/ftp/pub/PDS_JP2

dist:				.BEGIN \
					source_dist \
					bin_dist \
					.END

source_dist:		$(TARBALL)
$(TARBALL):			dist_wipe
	@echo
	@echo	"=== Assembling the source distribution package: $@"
	@echo
	$(MKDIR) -p $(DISTRIBUTION)
	$(CP) INSTALL-source $(DISTRIBUTION)
	Release -d $(DISTRIBUTION) -no_make Build $(SUBSYSTEM)
    ifneq ($(strip $(PRODUCER_SIGNATURE)),)
	@echo
	@$(RM) MF
	$(SED) \
		-e s=$(PRODUCER_SIGNATURE)== \
		$(DISTRIBUTION)/$(SUBSYSTEM)/Makefile > MF
	$(MV) -f MF $(DISTRIBUTION)/$(SUBSYSTEM)/Makefile
	$(SED) \
		-e s=$(PRODUCER_SIGNATURE)== \
		$(DISTRIBUTION)/$(SUBSYSTEM)/$(SUBSYSTEM)/Makefile > MF
	$(MV) -f MF $(DISTRIBUTION)/$(SUBSYSTEM)/$(SUBSYSTEM)/Makefile
    endif
	@echo
	@$(MAKE) --no-print-directory DOCS_INSTALL_DIR=$(DISTRIBUTION)/$(SUBSYSTEM) .docs_install
	@echo
	gtar czf $@ $(DISTRIBUTION)
	$(LN) $@ $(TARBALL_LINK)
    ifeq ($(strip $(OS)),Darwin)
	-$(RM) -r $(DISTRIBUTION)
	-$(RM) -r $(DISTRIBUTION)
	-$(RM) -r $(DISTRIBUTION)
    endif
	-$(RM) -r $(DISTRIBUTION)

Kakadu_Build_dist:	$(KAKADU_TARBALL)
$(KAKADU_TARBALL):
	@echo
	@echo "=== Assembling the Kakadu Build tarball: $@"
	@echo
	$(RM) $@ $(KAKADU_BUILD).dist
	$(MKDIR) $(KAKADU_BUILD).dist
	Release -d $(KAKADU_BUILD).dist -no_make $(SUBSYSTEM)
	@echo
	(cd $(KAKADU_BUILD).dist/$(SUBSYSTEM)/$(KAKADU_BUILD); gtar czf ../../../$@ *)
	@echo
    ifeq ($(strip $(OS)),Darwin)
	-$(RM) -r $(KAKADU_BUILD).dist
	-$(RM) -r $(KAKADU_BUILD).dist
	-$(RM) -r $(KAKADU_BUILD).dist
    endif
	-$(RM) -r $(KAKADU_BUILD).dist

dist_wipe:
    ifeq ($(strip $(OS)),Darwin)
	-$(RM) -r $(TARBALL) $(DISTRIBUTION) \
		$(TARBALL_PLATFORM) $(DISTRIBUTION_PLATFORM)
	-$(RM) -r $(TARBALL) $(DISTRIBUTION) \
		$(TARBALL_PLATFORM) $(DISTRIBUTION_PLATFORM)
	-$(RM) -r $(TARBALL) $(DISTRIBUTION) \
		$(TARBALL_PLATFORM) $(DISTRIBUTION_PLATFORM)
    endif
	$(RM) -r $(TARBALL) $(DISTRIBUTION) \
		$(TARBALL_PLATFORM) $(DISTRIBUTION_PLATFORM)
	$(RM) $(TARBALL_LINK) \
		$(TARBALL_LINK_PLATFORM)
	$(RM) $(KAKADU_TARBALL)

bin_dist:
	@echo
	$(MAKE) -C PDS_JP2 bin_dist

distribute:
	@echo
	@echo "*** Archiving the tarball files to the archive directory."
	$(MKDIR) -p archive
	$(CP) -f $(DISTRIBUTION)*.tar.gz archive
	@echo
	@echo "*** Moving the distribution files to the $(DIST_DIR) directory."
	$(MKDIR) -p $(DIST_DIR)
	$(MV) -f $(SUBSYSTEM)*.tar.gz $(DIST_DIR)
	$(CP) -f \
		README \
		Release_Notes \
		../Build/License/Copyright_Notice.GPL \
		../Build/License/LICENSE.GPL \
		INSTALL-source PDS_JP2/INSTALL-binary \
		$(DIST_DIR)



.PHONY:		subdirectories $(SUBDIRECTORIES) \
			dist source_dist $(TARBALL) \
			Kakadu_Build_dist $(KAKADU_TARBALL) \
			dist_wipe bin_dist distribute
