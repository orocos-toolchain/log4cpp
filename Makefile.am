if DOC
SUBDIRS = debian msvc6 bcb5 config src include tests doc 
else
SUBDIRS = debian msvc6 bcb5 config src include tests
endif

DIST_SUBDIRS = debian msvc6 bcb5 config src include doc tests

bin_SCRIPTS = log4cpp-config

EXTRA_DIST = log4cpp.spec.in log4cpp.spec m4/*.m4

.PHONY: check rpm docs doc-dist

dist-hook:
	perl -pi -e 's/\n/\r\n/g' `find $(distdir) -name '*.ds?'`

distclean-local:
	$(MAKE) -C tests distclean
	-rm -rf CONTENTS TAGS

CONTENTS::
	find $(top_srcdir) \( ! -type l -a -name '*.cpp' -o -name '*.hh' -o -name Makefile.am \) > $@

TAGS:: CONTENTS
	etags `cat $<`

rpm: dist
	rpm -ta $(PACKAGE)-$(VERSION).tar.gz
	mv -f /usr/src/redhat/SRPMS/$(PACKAGE)-$(VERSION)-*.rpm $(top_srcdir)
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-$(VERSION)-*.rpm $(top_srcdir)
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-devel-$(VERSION)-*.rpm \
		$(top_srcdir)
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-doc-$(VERSION)-*.rpm \
		$(top_srcdir)

debian:
	chmod a+x $(top_srcdir)/debian/rules
	dpkg-buildpackage -rfakeroot -sa -us -uc -tc 

docs:
	$(MAKE) -C doc

doc-dist: docs
	tar -zcf $(PACKAGE)-docs-$(VERSION).tar.gz -C $(top_srcdir)/doc/html .
 
