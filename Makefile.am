if DOC
SUBDIRS = config src include doc 
else
SUBDIRS = config src include
endif

DIST_SUBDIRS = config src include doc tests

EXTRA_DIST = log4cpp.spec.in log4cpp.spec

check: 
	$(MAKE) -C tests

distclean-local:
	$(MAKE) -C tests distclean
	-rm -rf CONTENTS TAGS

CONTENTS::
	find . \( ! -type l -a -name '*.cpp' -o -name '*.hh' -o -name Makefile.am \) > $@

TAGS:: CONTENTS
	etags `cat $<`

rpm: dist
	rpm -ta log4cpp-$(VERSION).tar.gz
	mv -f /usr/src/redhat/SRPMS/log4cpp-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/i386/log4cpp-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/i386/log4cpp-devel-$(VERSION)-*.rpm .
