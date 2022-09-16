##############################################################
#               CMake Project Wrapper Makefile               #
############################################################## 

SHELL := /bin/bash
RM    := rm -rf
MKDIR := mkdir -p

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile:
	@  ($(MKDIR) build > /dev/null)
	@  (cd build > /dev/null 2>&1 && cmake ..)

purge:
	@  ($(MKDIR) build > /dev/null)
	@- (cd build > /dev/null 2>&1 && cmake .. > /dev/null 2>&1)
	@- $(MAKE) --silent -C build clean || true
	@- $(RM) ./build/Makefile
	@- $(RM) ./build/app
	@- $(RM) ./build/src
	@- $(RM) ./build/tests
	@- $(RM) ./build/Testing
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
	@- $(RM) ./build/*.tcl
	@- $(RM) ./docs/*.html

ifeq ($(findstring purge,$(MAKECMDGOALS)),)
    $(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)
endif