if DOC
SUBDIRS = config src include doc 
else
SUBDIRS = config src include
endif

DIST_SUBDIRS = config src include doc tests

check: 
	$(MAKE) -C tests

distclean-local:
	$(MAKE) -C tests distclean
	-rm -rf CONTENTS TAGS

CONTENTS::
	find . \( ! -type l -a -name '*.[cCh]' -o -name Makefile.am \) > $@

TAGS:: CONTENTS
	etags `cat $<`

