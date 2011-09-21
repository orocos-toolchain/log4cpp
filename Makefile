ifdef ROS_ROOT
#include $(shell rospack find mk)/cmake.mk
all: build/CMakeCache.txt
	cd build && ${MAKE} install
build/CMakeCache.txt:
	mkdir -p build; cd build; cmake .. -DCMAKE_INSTALL_PREFIX=$(shell pwd)/../install

else
$(warning This Makefile only works with ROS rosmake. Without rosmake, create a build directory and run cmake ..)
endif
