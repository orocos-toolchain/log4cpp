ifdef ROS_ROOT
#include $(shell rospack find mk)/cmake.mk
all: build/configure.stamp
	cd build && make install
build/configure.stamp:
	mkdir -p build; cd build; ../configure --prefix=$(shell pwd)/install --disable-dot --disable-doxygen --disable-html-docs
	touch build/configure.stamp
else
$(warning This Makefile only works with ROS rosmake, without rosmake do the normal configure, make, make install)
endif