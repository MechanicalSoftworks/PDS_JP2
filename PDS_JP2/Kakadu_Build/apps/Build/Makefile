#	Kakadu Applications
#
#	PROJECT_ROOT/apps/Build/Makefile
#	gmake syntax
#
#	Author:	Bradford Castalia, UA/PIRL
#
#	PIRL CVS ID: Makefile,v 1.6 2011/07/08 04:10:42 castalia Exp

TITLE					:=	Kakadu Applications

#	The application program names.
PROGRAMS				:=	kdu_buffered_compress \
							kdu_buffered_expand \
							kdu_compress \
							kdu_expand \
							kdu_maketlm \
							kdu_merge \
							kdu_render \
							kdu_server \
							kdu_server_admin \
							kdu_transcode \
							kdu_v_compress \
							kdu_v_expand \
							kdu_vex_fast \
							simple_example_c \
							simple_example_d \
							kdu_text_extractor

#	Default build target (must preceed targets in include file).
all:			.BEGIN \
				programs \
				.END


#	Kakadu source base directory.
ifdef FAT_MAC_ARCH
PROJECT_ROOT			:=	../../..
else
PROJECT_ROOT			:=	../..
endif

#	Makefile configuration.
include					$(PROJECT_ROOT)/Build/Makefile.conf


#	Where the source code files can be found.
VPATH					:=	$(PROJECT_ROOT)/apps/kdu_buffered_compress \
							$(PROJECT_ROOT)/apps/kdu_buffered_expand \
							$(PROJECT_ROOT)/apps/kdu_client \
							$(PROJECT_ROOT)/apps/kdu_compress \
							$(PROJECT_ROOT)/apps/kdu_expand \
							$(PROJECT_ROOT)/apps/kdu_maketlm \
							$(PROJECT_ROOT)/apps/kdu_merge \
							$(PROJECT_ROOT)/apps/kdu_render \
							$(PROJECT_ROOT)/apps/kdu_server \
							$(PROJECT_ROOT)/apps/kdu_server_admin \
							$(PROJECT_ROOT)/apps/kdu_transcode \
							$(PROJECT_ROOT)/apps/kdu_v_compress \
							$(PROJECT_ROOT)/apps/kdu_v_expand \
							$(PROJECT_ROOT)/apps/kdu_vex_fast \
							$(PROJECT_ROOT)/apps/simple_example \
							$(PROJECT_ROOT)/apps/kdu_text_extractor

#	Additional non-library program objects.

kdu_compress_OBJECTS		:=	roi_sources.o

kdu_server_OBJECTS			:=	connection.o \
								sources.o

kdu_vex_fast_OBJECTS		:=	kdu_vex.o
							
ADDITIONAL_PROGRAM_OBJECTS	:=	$(kdu_compress_OBJECTS) \
								$(kdu_server_OBJECTS) \
								$(kdu_server_admin_OBJECTS) \
								$(kdu_vex_fast_OBJECTS)


#	Compiler/Linker options:

INCLUDES				:=	-I$(PROJECT_ROOT)/coresys/common \
							-I$(PROJECT_ROOT)/apps/args \
							-I$(PROJECT_ROOT)/apps/image \
							-I$(PROJECT_ROOT)/apps/jp2 \
							-I$(PROJECT_ROOT)/apps/compressed_io \
							-I$(PROJECT_ROOT)/apps/support \
							-I$(PROJECT_ROOT)/apps/client_server \
							-I$(PROJECT_ROOT)/apps/kdu_server \
							$(HOST_INCLUDES)

CXXFLAGS				+=	$(HOST_CXXFLAGS) $(INCLUDES)

#	Kakadu coresys library.
KDU_LIBRARY				:=	-L$(PROJECT_ROOT)/coresys/Build \
							-lkdu$(LIBRARY_NAME_SUFFIX)

#	Kakadu auxixiliary library with managed interfaces.
AUX_LIBRARY				:=	-L$(PROJECT_ROOT)/managed/Build \
							-lkdu_a$(LIBRARY_NAME_SUFFIX)

LIBRARIES				:=	$(KDU_LIBRARY) \
							$(AUX_LIBRARY) \
							$(HOST_LIBRARIES) \
							-lm
ifndef KDU_NO_THREADS
LIBRARIES				+=	-lpthread
endif

LDFLAGS					+=	$($(LIBRARY_SELECTION)_LIBRARY_OPTION) \
							$(HOST_LDFLAGS)



#	Targets:

programs:		$(PROGRAMS)

ifdef FAT_MAC_ARCHES
$(PROGRAMS):	$(ARCH_PROGRAMS)
	$(BUILD_FAT_MAC)
$(ARCH_PROGRAMS):
	@$(BUILD_FAT_MAC_ARCHES)
else
$(PROGRAMS):	$(ADDITIONAL_PROGRAM_OBJECTS)
$(PROGRAMS):	%: %.o
	@echo
	$(CC) $< $($@_OBJECTS) $(LDFLAGS) $(LIBRARIES) -o $@
	@echo
endif	#	FAT_MAC_ARCHES


text:		kdu_text_extractor
	@echo
	@echo Extracting language text ...
	cd $(PROJECT_ROOT)/language; \
	../apps/Build/kdu_text_extractor -quiet -s coresys.src; \
	../apps/Build/kdu_text_extractor -quiet -s jp2.src; \
	../apps/Build/kdu_text_extractor -quiet -s jpx.src; \
	../apps/Build/kdu_text_extractor -quiet -s mj2.src; \
	../apps/Build/kdu_text_extractor -quiet -s client.src; \
	../apps/Build/kdu_text_extractor -quiet -s misc.src
	@echo


install:		.BEGIN \
				.BEGIN_INSTALL \
				bin_install \
				.END

bin_install:	programs
	@echo
	@echo "Installing the application programs"
	mkdir -p $(BIN_DIR)
	cp -f $(PROGRAMS) $(BIN_DIR)
	@echo


clean:
	rm -rf  *.o $(FAT_MAC_ARCHES) \
		$(PROGRAMS)


.PHONY:	text
