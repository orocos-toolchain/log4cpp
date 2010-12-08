ifdef ROS_ROOT
#include $(shell rospack find mk)/cmake.mk
all: configure.stamp
	cd build && make install
configure.stamp:
	mkdir -p build; cd build; ../configure --prefix=$(shell pwd)/install
	touch configure.stamp
else
$(warning This Makefile only works with ROS rosmake, without rosmake do the normal configure, make, make install)
endif