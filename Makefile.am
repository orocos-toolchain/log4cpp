if DOC
SUBDIRS = config src include doc 
else
SUBDIRS = config src include
endif

DIST_SUBDIRS = config src include doc tests

bin_SCRIPTS = log4cpp-config

EXTRA_DIST = log4cpp.spec.in log4cpp.spec

.PHONY: check rpm docs doc-dist

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
	rpm -ta $(PACKAGE)-$(VERSION).tar.gz
	mv -f /usr/src/redhat/SRPMS/$(PACKAGE)-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-devel-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-doc-$(VERSION)-*.rpm .

docs:
	$(MAKE) -C doc

doc-dist: docs
	tar -zcf $(PACKAGE)-docs-$(VERSION).tar.gz -C doc/html .
 
