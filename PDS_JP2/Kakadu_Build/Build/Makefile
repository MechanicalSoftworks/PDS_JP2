#	Kakadu JPEG2000 Software
#
#	PROJECT_ROOT/Build/Makefile
#	gmake syntax
#
#	PIRL CVS ID: Makefile,v 1.7 2011/07/08 03:16:34 castalia Exp

PROJECT_ROOT			:=	..

#	Default build target (must preceed targets in include file).
all:				subdirectories

#	Makefile configuration.
include						Makefile.conf


#	The subdirectories are listed in the order they are to be built.
LIBRARY_SUBDIRECTORIES	:=	coresys \
							managed
PROGRAM_SUBDIRECTORIES	:=	apps

SUBDIRECTORIES			:=	$(LIBRARY_SUBDIRECTORIES) \
							$(PROGRAM_SUBDIRECTORIES)
			

#	Targets:


#	Builds the TARGET for each subdirectory.
subdirectories:		.BEGIN_BUILD \
					$(SUBDIRECTORIES) \
					.END_BUILD
$(SUBDIRECTORIES):
	@echo
	@echo "--> $(PROJECT): $@"
	@echo
	$(MAKE) -C $(PROJECT_ROOT)/$@/Build $(TARGET)


programs:			TARGET = programs
programs:			.BEGIN _BUILD\
					$(PROGRAM_SUBDIRECTORIES) \
					.END_BUILD

libraries:			TARGET = libraries
libraries:			.BEGIN_BUILD \
					$(LIBRARY_SUBDIRECTORIES) \
					.END_BUILD

static_libraries:	TARGET = static_library
static_libraries:	.BEGIN_BUILD \
					$(LIBRARY_SUBDIRECTORIES) \
					.END_BUILD

shared_libraries:	TARGET = shared_library
shared_libraries:	.BEGIN_BUILD \
					$(LIBRARY_SUBDIRECTORIES) \
					.END_BUILD


#	Installation:

install:			TARGET = install
install:			subdirectories

bin_install:		TARGET = bin_install
bin_install:		subdirectories


#	Documentation:

docs:				TARGET = docs
docs:				.BEGIN_BUILD \
					managed \
					.END_BUILD

text:				TARGET = text
text:				.BEGIN _BUILD\
					apps \
					.END_BUILD

#	Cleaning:

clean:				TARGET = clean
clean:				subdirectories


.BEGIN_BUILD:
	@echo
	@echo ">>> $(PROJECT) version $(VERSION)"
	@date
	@echo "On host system $(HOSTNAME), $(OS) OS, $(ARCH) architecture"
	@echo

.END_BUILD:
	@echo
	@echo "<<< $(PROJECT) version $(VERSION) Completed"
	@date
	@echo

.PHONY:				.BEGIN_BUILD \
					subdirectories $(SUBDIRECTORIES) \
					.END_BUILD
