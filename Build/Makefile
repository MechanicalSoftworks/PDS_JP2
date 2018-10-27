#	Makefile for the HiRISE at HiROC subsystems.
#
#	gmake syntax.
#
# CVS ID: Makefile,v 2.92 2015/02/23 22:35:53 schaller Exp

R := R
BUILD_MAKEFILE_REVISION	:=	2.92

#	Project Makefile configuration:
MASTER_MAKEFILE		=	true
include					Makefile.conf

#===============================================================================
#	Subsystems

#	The order of subsystems matters: put subsystems after their dependencies.
HiRISE_SUBSYSTEMS		:=	libHiRISE \
							Observation \
							Pipeline_Utilities \
							HiDog \
							EDRgen \
							HiPlan \
							HiCommand \
							EDR_Stats \
							HiCal \
							HiStitch \
							HiccdStitch \
							RedMosaic \
							RedGeom \
							HiGeomInit \
							HiMosMerge \
							RDRgen \
							HiColor \
							HiColorNorm \
							HiSPICE \
							HiArch \
							HiCat \
							HiVali \
							PDS_JP2 \
							HiGlyph \
							HiWish \
							HiReport \
							HiPrecision \
							DTM \
							HiPdsVal \
							HiRat \
							CTX \
							CTXGlyph \
							HiView

#	Categories of SUBSYSTEMS:

#	Subsystems that should not be built with SUBSYSTEMS = ALL. These will be
#	removed from the set of subsystems if SUBSYSTEMS is ALL.
SKIPPED_SUBSYSTEMS		+=	HiView

#	Restricted access (ITAR sequestration).
#	Subsystems to have limited access permissions.
PRIVATE_SUBSYSTEMS		+=	ENGmon \
							HiCommand

#-------------------------------------------------------------------------------
#	Release

RELEASE_VERSION			:=	$(shell grep '^[0-9]' VERSION)

ifeq ($(SUBSYSTEMS),)
#	The release target requires that SUBSYSTEMS be defined.
release:	SUBSYSTEMS	= $(error SUBSYSTEMS must be defined for a release \
	(define as ALL to release all subsystems))

#	By default all HiRISE_SUBSYSTEMS are built.
SUBSYSTEMS				= $(HiRISE_SUBSYSTEMS)
else
ifeq ($(SUBSYSTEMS),ALL)
override SUBSYSTEMS		= $(filter-out $(SKIPPED_SUBSYSTEMS),$(HiRISE_SUBSYSTEMS))
else
unknown_subsystems		= $(filter-out $(HiRISE_SUBSYSTEMS),$(SUBSYSTEMS))
ifneq ($(unknown_subsystems),)
$(error Uknown SUBSYSTEMS: $(unknown_subsystems))
endif
endif
endif

ifeq ($(RELEASE_DIR),)
#	The release target requires that RELEASE_DIR be defined.
release:		RELEASE_DIR = $(error RELEASE_DIR must be defined for a release)
source_release:	RELEASE_DIR = $(error RELEASE_DIR must be defined for a release)
endif

ifeq ($(HiRISE_ROOT),)
#	The release target requires that HiRISE_ROOT be defined.
release:	HiRISE_ROOT = $(error HiRISE_ROOT must be defined for a release)
endif

#	Release requires CVSROOT to specify the source of the release.
export 		CVSROOT		?=	$(HiRISE_ROOT)/CVS_Repository

#	The group for private files.
PRIVATE_GROUP			?=	hitar

#-------------------------------------------------------------------------------
#	Java Packages

#	HiRISE subsystem Java packages (must be named $(SUBSYSTEM)_JAVA_PACKAGES).
#	Used to select HiRISE Java packages for java target.

libHiRISE_JAVA_PACKAGES	=	HiRISE.libHiRISE

EDRgen_JAVA_PACKAGES	=	HiRISE.EDRgen

HiCommand_JAVA_PACKAGES	=	HiRISE.HiCommand

HiPlan_JAVA_PACKAGES	=	HiRISE.HiPlan.IO \
							HiRISE.HiPlan.PTF \
							HiRISE.HiPlan.SPICE \
							HiRISE.HiPlan.Help \
							HiRISE.HiPlan.Utilities \
							HiRISE.HiPlan.HiCat \
							HiRISE.HiPlan.HiWeb \
							HiRISE.HiPlan.HIPHOP \
							HiRISE.HiPlan.HiTemp \
							HiRISE.HiPlan.HiSEAS \
							HiRISE.HiPlan.Data_Slacker \
							HiRISE.HiPlan.Shapes \
							HiRISE.HiPlan.HOGG

HiCat_JAVA_PACKAGES		=	HiRISE.HiCat.HiTList \
							HiRISE.HiCat.Utilities \
							HiRISE.HiCat.HiVolume \
							HiRISE.HiCat.CleanUp

HiVali_JAVA_PACKAGES	=	HiRISE.HiVali

HiColor_JAVA_PACKAGES	=	HiRISE.HiColor

RedMosaic_JAVA_PACKAGES	=	HiRISE.RedMosaic

HiWish_JAVA_PACKAGES	=	HiRISE.HiWish

HiReport_JAVA_PACKAGES	=	HiRISE.HiReport \
							HiRISE.HiReport.database \
							HiRISE.HiReport.downlink \
							HiRISE.HiReport.form \
							HiRISE.HiReport.main \
							HiRISE.HiReport.model \
							HiRISE.HiReport.product \
							HiRISE.HiReport.servlets \
							HiRISE.HiReport.sql \
							HiRISE.HiReport.system \
							HiRISE.HiReport.tags \
							HiRISE.HiReport.tags.chart \
							HiRISE.HiReport.uplink \
							HiRISE.HiReport.util

DTM_JAVA_PACKAGES		=	HiRISE.DTM

Pipeline_Utilities_JAVA_PACKAGES =	HiRISE.Pipeline_Utilities

JAVA_SUBSYSTEMS			:=	\
	$(filter $(foreach subsystem,$(SUBSYSTEMS), \
		$(if $($(subsystem)_JAVA_PACKAGES),$(subsystem))), $(SUBSYSTEMS))

JAVA_PACKAGES			:=	\
	$(strip $(foreach subsystem,$(SUBSYSTEMS),$($(subsystem)_JAVA_PACKAGES)))

#	Documentation that must not be released (ITAR sequestration).
NO_JAVADOC_PACKAGES		=	$(HiCommand_JAVA_PACKAGES)

#	All (non ITAR) Java packages for which javadoc is to be generated.
JAVADOC_PACKAGES		:=	\
	$(filter-out $(NO_JAVADOC_PACKAGES), \
		$(foreach subsystem,$(HiRISE_SUBSYSTEMS),$($(subsystem)_JAVA_PACKAGES)))

#	Where the .java source files can be found.
JAVADOC_SOURCEPATH		:=	../..:../HiReport/src:../HiWish/src

#===============================================================================
#	Targets

All:				.BEGIN_MAKE \
					subsystems \
					.END_MAKE
.BEGIN_MAKE:
	@echo
	@echo "*** $(PROJECT) version $(RELEASE_VERSION)"
	@echo "    Build/Makefile $(BUILD_MAKEFILE_REVISION)"
	@date

#	Builds the MAKE_TARGET for each subsystem.
subsystems:			$(SUBSYSTEMS)
$(SUBSYSTEMS)::
	$(MAKE) -C $(PROJECT_ROOT)/$@ SUBSYSTEM=$@ $(MAKE_TARGET)

#-------------------------------------------------------------------------------
#	Installation:

.BEGIN_MAKE_INSTALL:
	@echo
	@echo "*** Installation on $(OS) $(PLATFORM)"
	@echo

install:			MAKE_TARGET = install
install:			.BEGIN_MAKE \
					.install \
					.END_MAKE
.install:			.BEGIN_MAKE_INSTALL \
					install_dirs \
					java \
					subsystems \
					javadocs \
					permissions \
					private_permissions \
					.install_date \
					.END_MAKE_INSTALL

bin_install:		MAKE_TARGET = bin_install
bin_install:		.BEGIN_MAKE \
					.BEGIN_MAKE_INSTALL \
					bin_dirs \
					subsystems \
					bin_permissions \
					.install_date \
					.END_MAKE_INSTALL \
					.END_MAKE

scripts_install:	MAKE_TARGET = scripts_install
scripts_install:	.BEGIN_MAKE \
					.BEGIN_MAKE_INSTALL \
					subsystems \
					bin_permissions \
					.END_MAKE_INSTALL \
					.END_MAKE

headers_install:	MAKE_TARGET = headers_install
headers_install:	.BEGIN_MAKE \
					.BEGIN_MAKE_INSTALL \
					subsystems \
					.END_MAKE_INSTALL \
					.END_MAKE

docs_install:		MAKE_TARGET = docs_install
docs_install:		.BEGIN_MAKE \
					.BEGIN_MAKE_INSTALL \
					docs_dirs \
					subsystems \
					docs_permissions \
					.END_MAKE_INSTALL \
					.END_MAKE

configs_install:	MAKE_TARGET = configs_install
configs_install:	.BEGIN_MAKE \
					.BEGIN_MAKE_INSTALL \
					subsystems \
					.END_MAKE_INSTALL \
					.END_MAKE

java:				.BEGIN_MAKE \
					java_subsystems \
					.END_MAKE
#	Because a target will only be invoked once, this target enables the
#	java target to be invoked, after the subsystems target, from .install
#	by eliding the real names of the SUBSYSTEMS.
SUBSYSTEMS_J	=	$(addsuffix .J,$(JAVA_SUBSYSTEMS))
java_subsystems:	$(SUBSYSTEMS_J)
$(SUBSYSTEMS_J)::
    ifneq ($(JAVA_PACKAGES),)
	$(MAKE) -C $(PROJECT_ROOT)/$(basename $@) SUBSYSTEM=$(basename $@) java
    endif

.install_date:
	@echo $(RELEASE_VERSION)-`date`-$(SUBSYSTEMS) >> Install-$(OS)-$(PLATFORM).date
	-@$(foreach subsystem, $(SUBSYSTEMS), \
		$(MAKE) --no-print-directory -C ../$(subsystem) VERSION_Report >> Install-$(OS)-$(PLATFORM).date;)

.END_MAKE_INSTALL:
	@echo
	@echo "*** Installation on $(OS) $(PLATFORM) Completed"
	-@$(foreach subsystem, $(SUBSYSTEMS), \
		$(MAKE) --no-print-directory -C ../$(subsystem) VERSION_Report;)
	@echo

#-------------------------------------------------------------------------------
#	Required directories:

install_dirs:		bin_dirs \
					docs_dirs \
					shared_dirs

BIN_DIRS				:=	$(INSTALL_DIR)/bin \
							$(INSTALL_DIR)/lib \
							$(TOMCAT_INSTALL_DIR)
bin_dirs:			$(BIN_DIRS)
$(BIN_DIRS):
	$(MKDIR) -p $@

DOCS_DIRS				:=	$(INSTALL_DIR)/docs \
							$(HiRISE_JAVADOCS_DIR)
docs_dirs:			$(DOCS_DIRS)
$(DOCS_DIRS):
	$(MKDIR) -p $@

SHARED_SUBSYSTEMS	:= \
	$(strip $(filter-out $(PRIVATE_SUBSYSTEMS),$(SUBSYSTEMS)))
SHARED_DIRS				:=	$(INSTALL_DIR)/include \
							$(SHARED_SUBSYSTEMS:%=$(INSTALL_DIR)/%)
shared_dirs:		$(SHARED_DIRS)
$(SHARED_DIRS):
	$(MKDIR) -p $@

subsystem_dirs:		MAKE_TARGET = standard_dirs
subsystem_dirs:		.BEGIN_MAKE \
					subsystems \
					.END_MAKE

#-------------------------------------------------------------------------------
#	Permissions:

permissions:		bin_permissions \
					docs_permissions \
					shared_permissions
bin_permissions:
	@echo
	@echo "--- Setting binary files permissions"
	-$(FIND) $(BIN_DIRS) \
		-type d \
		-exec $(CHMOD) $(DIR_PERMISSIONS) {} \;
	-$(FIND) \
		$(INSTALL_DIR)/bin \
		-type f \
		-exec $(CHMOD) $(BIN_PERMISSIONS) {} \;
	-$(FIND) \
		$(INSTALL_DIR)/lib \
		-type f \
		-exec $(CHMOD) $(SOURCE_FILE_PERMISSIONS) {} \;
docs_permissions:
	@echo
	@echo "--- Setting document files permissions"
	-$(FIND) \
		$(INSTALL_DIR)/docs \
		-type d \
		-exec $(CHMOD) $(DOCS_DIR_PERMISSIONS) {} \;
	-$(FIND) \
		$(INSTALL_DIR)/docs \
		-type f \
		-exec $(CHMOD) $(DOCS_FILE_PERMISSIONS) {} \;

shared_permissions:
	@echo
	@echo "--- Setting shared text files permissions"
	-$(FIND) \
		$(INSTALL_DIR)/Build $(SHARED_DIRS) \
		-type d \
		-exec $(CHMOD) $(DIR_PERMISSIONS) {} \;
	-$(FIND) \
		$(INSTALL_DIR)/Build $(SHARED_DIRS) \
		-type f \
		-exec $(CHMOD) $(SOURCE_FILE_PERMISSIONS) {} \;

#	N.B.: Set the private permissions on completion of an install.
USING_PRIVATE_SUBSYSTEMS	:=	\
	$(strip $(filter $(PRIVATE_SUBSYSTEMS),$(SUBSYSTEMS)))
PRIVATE_DIRS			:=	$(USING_PRIVATE_SUBSYSTEMS:%=$(INSTALL_DIR)/%)
private_permissions:
    ifneq ($(USING_PRIVATE_SUBSYSTEMS),)
	@echo
	@echo "--- Setting private subsystems permissions"
	-$(CHGRP) -R $(PRIVATE_GROUP) $(PRIVATE_DIRS)
	-$(FIND) \
		$(PRIVATE_DIRS) \
		-type d \
		-exec $(CHMOD) $(PRIVATE_DIR_PERMISSIONS) {} \;
	-$(FIND) \
		$(PRIVATE_DIRS) \
		-type f \
		-exec $(CHMOD) $(PRIVATE_FILE_PERMISSIONS) {} \;
    endif

#-------------------------------------------------------------------------------
#	Documentation:

docs:				MAKE_TARGET = docs
docs:				.BEGIN_MAKE \
					docs_dirs \
					subsystems \
					.END_MAKE

javadocs:			.BEGIN_MAKE \
					docs_dirs \
					.javadocs \
					.END_MAKE
#	Alias
javadoc:			javadocs

.javadocs:
    ifneq ($(JAVA_PACKAGES),)
    ifndef NO_JAVADOC
	javadoc \
		-d $(HiRISE_JAVADOCS_DIR) \
		-author \
		-version \
		-link $(JAVA_SDK_URL) \
		-link $(PIRL_JAVA_URL) \
		-link $(JFREECHART_URL) \
		-link $(JCOMMON_URL) \
		-link $(SWINGX_URL) \
		-link $(SWINGWORKER_URL) \
		-link $(ACTIVATION_URL) \
		-link $(MAIL_URL) \
		-link $(MTT_URL) \
		-windowtitle "HiRISE Java Packages" \
		-header '<a href="http://HiRISE.LPL.Arizona.EDU" \
			target="_top"><img src="{@docRoot}/HiRISE_Icon.png" \
			alt="HiRISE"></a>' \
		-bottom '<a href="{@docRoot}/Copyright.html">Copyright \
			(C)</a> Arizona Board of Regents on behalf of the \
			Planetary Image Research Laboratory, Lunar and \
			Planetary Laboratory at the University of Arizona' \
		-sourcepath $(JAVADOC_SOURCEPATH) \
		-classpath $(JPATH) \
		$(JAVADOC_PACKAGES)
	$(CP) HiRISE_Icon.png License/Copyright.html $(HiRISE_JAVADOCS_DIR)
    endif
    endif

#-------------------------------------------------------------------------------
#	Release:

.BEGIN_MAKE_RELEASE:
	@echo
	@echo "*** Source Release"
	@echo

#	Release all the source files before compiling.
#	This avoids cross dependencies on installed include files.
RELEASE:			release
release:			.BEGIN_MAKE \
					.BEGIN_MAKE_RELEASE \
					.source_release \
					.END_MAKE_RELEASE
	@$(MAKE) -C $(RELEASE_DIR)/Build install

source_release:		.BEGIN_MAKE \
					.BEGIN_MAKE_RELEASE \
					.source_release \
					.END_MAKE_RELEASE \
					.END_MAKE
.source_release:
	Release $(SUBSYSTEMS) \
		-directory $(RELEASE_DIR) \
		-no_strip \
		-no_make

.END_MAKE_RELEASE:
	@echo
	@echo "*** Source Release Completed"
	@date
	@echo

.END_MAKE:
	@echo
	@echo "*** $(PROJECT) version $(RELEASE_VERSION) Completed"
	@date
	@echo

#-------------------------------------------------------------------------------
#	Distribution:

dist:				DIST_DIR = HiROC-$(RELEASE_VERSION)
dist:				.BEGIN_MAKE \
					.dist \
					.END_MAKE
.dist:
	-$(RM) -r HiRISE $(DIST_DIR)
	$(MKDIR) $(DIST_DIR)
	$(LN) $(DIST_DIR) HiRISE
	Release \
		-dir $(DIST_DIR) \
		-no_strip_DEBUG \
		-no_make \
		Build $(SUBSYSTEMS)
	cd $(DIST_DIR)/Build && $(MAKE) docs_install javadocs
	cd $(DIST_DIR)/Build && $(MAKE) distclean
	gtar \
		--create --gzip \
		--file=$(DIST_DIR).tar.gz \
		HiRISE $(DIST_DIR)
	-$(RM) -r HiRISE $(DIST_DIR)

bin_dist:			DIST_DIR = HiROC-$(RELEASE_VERSION)-$(OS)-$(PLATFORM)
bin_dist:			.BEGIN_MAKE \
					.bin_dist \
					.END_MAKE
.bin_dist:
	-$(RM) -r HiRISE $(DIST_DIR)
	$(MKDIR) HiRISE
	Release \
		-dir HiRISE \
		-no_strip_DEBUG \
		-no_make \
		Build $(SUBSYSTEMS)
	cd HiRISE/Build && $(MAKE) headers_install
	cd HiRISE/Build && $(MAKE) bin_install
	$(MV) HiRISE $(DIST_DIR)
	$(LN) $(DIST_DIR) HiRISE
	gtar \
		--create --gzip \
		--file=$(DIST_DIR).tar.gz \
		HiRISE $(DIST_DIR)
	-$(RM) -r HiRISE $(DIST_DIR)

#-------------------------------------------------------------------------------
#	Cleaning:

clean:				MAKE_TARGET = clean
clean:				.BEGIN_MAKE \
					subsystems \
					.END_MAKE

dist_clean:			MAKE_TARGET = dist_clean
dist_clean:			.BEGIN_MAKE \
					subsystems \
					.END_MAKE
distclean:			dist_clean

#-------------------------------------------------------------------------------
.PHONY:				All subsystems $(SUBSYSTEMS) \
					.BEGIN_MAKE_RELEASE \
					RELEASE release source_release .source_release \
					.END_MAKE_RELEASE \
					.BEGIN_MAKE_INSTALL \
					install .install \
						bin_install scripts_install \
						headers_install configs_install \
						docs_install \
						.install_date \
					java java_subsystems javadocs javadoc .javadocs \
					install_dirs bin_dirs docs_dirs shared_dirs \
					permissions \
						bin_permissions \
						docs_permissions \
						shared_permissions \
						private_permissions\
					.END_MAKE_INSTALL \
					docs .docs \
					clean dist_clean \
					.END_MAKE

