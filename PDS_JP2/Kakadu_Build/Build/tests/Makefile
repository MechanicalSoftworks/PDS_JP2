#	Kakadu architecture test
#
#	PROJECT_ROOT/Build/tests/Makefile
#	gmake syntax
#
#	Author:	Bradford Castalia, UA/PIRL
#
#	PIRL CVS ID: Makefile,v 1.2 2011/07/08 03:55:43 castalia Exp

TITLE			:=	Kakadu host system architecture test

PROGRAMS		:=	kdu_arch_test

#	Kakadu source base directory.
PROJECT_ROOT	:=	../..

#	Default build target (must preceed targets in include file).
all:		.BEGIN clean programs
	@echo
	kdu_arch_test
	@echo


#	Kakadu source base directory.
ifdef FAT_MAC_ARCH
PROJECT_ROOT			:=	../../..
else
PROJECT_ROOT			:=	../..
endif

#	Makefile configuration.
include					$(PROJECT_ROOT)/Build/Makefile.conf


#	Where the source code files can be found.
VPATH			:=	$(PROJECT_ROOT)/coresys/common \
					..

ADDITIONAL_PROGRAM_OBJECTS	:=	kdu_arch.o


#	Compiler/Linker options:

INCLUDES		:=	-I$(PROJECT_ROOT)/coresys/common

CXXFLAGS		+=	$(HOST_CXXFLAGS) $(INCLUDES)


#	Targets:

programs:		$(PROGRAMS)

ifdef FAT_MAC_ARCHES
$(PROGRAMS):	$(ARCH_PROGRAMS)
	$(BUILD_FAT_MAC)
$(ARCH_PROGRAMS):
	$(BUILD_FAT_MAC_ARCHES)
else
$(PROGRAMS):	$(ADDITIONAL_PROGRAM_OBJECTS)
$(PROGRAMS):	%: %.o
	@echo
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo
endif	#	FAT_MAC_ARCHES


clean:
	rm -rf *.o $(FAT_MAC_ARCHES) $(PROGRAMS)


.PHONY:		.BEGIN all clean
