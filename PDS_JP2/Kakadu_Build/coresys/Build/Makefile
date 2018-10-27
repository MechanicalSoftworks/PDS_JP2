#	Kakadu Library
#
#	PROJECT_ROOT/coresys/Build/Makefile
#	gmake syntax
#
#	Author:	Bradford Castalia, UA/PIRL
#
#   PIRL CVS ID: Makefile,v 1.6 2011/07/08 04:10:42 castalia Exp

TITLE					:=	Kakadu JPEG2000 Core Library

#	Library name.
LIBRARY_NAME			:=	kdu

#	Default build target (must preceed targets in include file).
all:				.BEGIN \
					libraries \
					.END


#	Kakadu source base directory (must preceed include file).
ifdef FAT_MAC_ARCH
PROJECT_ROOT			:=	../../..
else
PROJECT_ROOT			:=	../..
endif


#	Makefile configuration.
include					$(PROJECT_ROOT)/Build/Makefile.conf


#	Kakadu-specific library name, for name compatibility.
KAKADU_LIBRARY_NAME		:=	lib$(LIBRARY_NAME)_v$(KAKADU_VERSION).$(SHARED_LIBRARY_EXTENSION)


#	Where the source code files can be found.
VPATH					:=	$(PROJECT_ROOT)/coresys/coding \
							$(PROJECT_ROOT)/coresys/common \
							$(PROJECT_ROOT)/coresys/compressed \
							$(PROJECT_ROOT)/coresys/kernels \
							$(PROJECT_ROOT)/coresys/messaging \
							$(PROJECT_ROOT)/coresys/parameters \
							$(PROJECT_ROOT)/coresys/roi \
							$(PROJECT_ROOT)/coresys/threads \
							$(PROJECT_ROOT)/coresys/transform


#	Library contents.
LIBRARY_OBJECTS			:=	block_coding_common.o \
							block_decoder.o \
							block_encoder.o \
							decoder.o \
							encoder.o \
							mq_decoder.o \
							mq_encoder.o \
							blocks.o \
							codestream.o \
							compressed.o \
							kernels.o \
							messaging.o \
							params.o \
							colour.o \
							analysis.o \
							synthesis.o \
							multi_transform.o \
							roi.o \
							kdu_arch.o \
							kdu_threads.o

SHARED_LIBRARY_OBJECTS	:=	$(LIBRARY_OBJECTS:%.o=%.slo)


#	Compiler/Linker options:

INCLUDES				:=	-I$(PROJECT_ROOT)/coresys/common $(HOST_INCLUDES)

CXXFLAGS				+=	$(HOST_CXXFLAGS) $(INCLUDES)
$(SHARED_LIBRARY):	CXXFLAGS	+=	$(SHARED_LIBRARY_CXXFLAGS)

LDFLAGS					+=	$(HOST_LDFLAGS)
$(SHARED_LIBRARY):	LDFLAGS		+=	$(SHARED_LIBRARY_OPTION)


#	Targets:

#	Default build target.
all:				.BEGIN \
					libraries \
					.END

libraries:			static_library \
					shared_library

#	Static library.
ifdef STATIC
static_library:		.BEGIN_STATIC $(STATIC_LIBRARY)

ifdef FAT_MAC_ARCHES
$(STATIC_LIBRARY):		$(ARCH_STATIC_LIBRARIES)
	$(BUILD_FAT_MAC)
$(ARCH_STATIC_LIBRARIES):
	$(BUILD_FAT_MAC_ARCHES)
else
$(STATIC_LIBRARY):		$(LIBRARY_OBJECTS)
	$(BUILD_STATIC_LIBRARY)
endif	#	FAT_MAC_ARCHES

static_library_install:	$(STATIC_LIBRARY)
	@echo
	@echo "Installing the static object library: $(STATIC_LIBRARY)"
	mkdir -p $(LIB_DIR)
	cp -f $(STATIC_LIBRARY) $(LIB_DIR)/$(STATIC_LIBRARY).$(VERSION)
	ranlib $(LIB_DIR)/$(STATIC_LIBRARY).$(VERSION)
	rm -f $(LIB_DIR)/$(STATIC_LIBRARY)
	ln -s $(STATIC_LIBRARY).$(VERSION) $(LIB_DIR)/$(STATIC_LIBRARY)
	@echo

else
static_library:			.NO_STATIC_LIBRARY
static_library_install:	.NO_STATIC_LIBRARY
endif	#	STATIC


#	Shared library.
ifdef SHARED
shared_library:		.BEGIN_SHARED $(SHARED_LIBRARY)

ifdef FAT_MAC_ARCHES
$(SHARED_LIBRARY):	$(ARCH_SHARED_LIBRARIES)
	$(BUILD_FAT_MAC)
$(ARCH_SHARED_LIBRARIES):
	@$(BUILD_FAT_MAC_ARCHES)
else
$(SHARED_LIBRARY):	$(SHARED_LIBRARY_OBJECTS)
	@echo
	$(CC) $(LDFLAGS) $(SHARED_LIBRARY_OBJECTS) -o $@
	@echo
endif	#	FAT_MAC_ARCHES

shared_library_install:	$(SHARED_LIBRARY)
	@echo
	@echo "Installing the shared/dynamic library: $(SHARED_LIBRARY)"
	mkdir -p $(LIB_DIR)
	cp -f $(SHARED_LIBRARY) $(LIB_DIR)/$(SHARED_LIBRARY).$(VERSION)
	rm -f $(LIB_DIR)/$(SHARED_LIBRARY)
	rm -f $(LIB_DIR)/$(SHARED_LIBRARY).$(MAJOR_VERSION)
	rm -f $(LIB_DIR)/$(KAKADU_LIBRARY_NAME)
	ln -s $(SHARED_LIBRARY).$(VERSION) $(LIB_DIR)/$(SHARED_LIBRARY)
	ln -s $(SHARED_LIBRARY).$(VERSION) $(LIB_DIR)/$(SHARED_LIBRARY).$(MAJOR_VERSION)
	ln -s $(SHARED_LIBRARY).$(VERSION) $(LIB_DIR)/$(KAKADU_LIBRARY_NAME)
	@echo

else
shared_library:			.NO_SHARED_LIBRARY
shared_library_install:	.NO_SHARED_LIBRARY
endif	#	SHARED


clean:
	rm -rf *.o *.slo $(STATIC_LIBRARY) $(SHARED_LIBRARY) $(FAT_MAC_ARCHES)


install:			.BEGIN \
					.BEGIN_INSTALL \
					bin_install \
					.END

bin_install:		static_library_install \
					shared_library_install

