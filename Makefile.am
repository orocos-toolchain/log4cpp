if DOC
SUBDIRS = config src include doc 
else
SUBDIRS = config src include
endif

DIST_SUBDIRS = config src include doc tests

bin_SCRIPTS = log4cpp-config

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
	mv -f /usr/src/redhat/RPMS/i386/log4cpp-doc-$(VERSION)-*.rpm .

docs:
	$(MAKE) -C doc

doc-dist: docs
	tar -zcf log4cpp-docs-$(VERSION).tar.gz -C doc/html .
 
