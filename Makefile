ifdef ROS_ROOT
#include $(shell rospack find mk)/cmake.mk
all: build/configure.stamp
	cd build && ${MAKE} install
build/configure.stamp:
	mkdir -p build; cd build; cmake .. -DCMAKE_INSTALL_PREFIX=$(shell pwd)/install
	touch build/configure.stamp
else
$(warning This Makefile only works with ROS rosmake. Without rosmake, create a build directory and run cmake ..)
endif
