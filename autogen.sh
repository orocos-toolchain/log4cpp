#!/bin/sh

echo "Adding libtools."
libtoolize --automake

echo "Building macros."
aclocal $ACLOCAL_FLAGS

echo "Building config header."
autoheader

echo "Building makefiles."
automake   --add-missing

echo "Building configure."
autoconf

echo 'run "configure; make"'
