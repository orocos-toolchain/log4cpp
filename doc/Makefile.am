SUBDIRS = html

man3dir = $(mandir)/man3
docdir  = $(prefix)/doc/@PACKAGE_TARNAME@-@PACKAGE_VERSION@

EXTRA_DIST = \
	mainPage.txt

.PHONY: dox pdf

all-local: dox #pdf

dox: html html/api/index.html
html/api/index.html: Doxyfile
	@DOXYGEN@

pdf: @PACKAGE_TARNAME@.pdf
@PACKAGE@.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 @PACKAGE_TARNAME@.ps
	ln -s ./latex/refman.pdf @PACKAGE_TARNAME@.pdf


install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(man3dir)
	@for i in ./man/man3/log4cpp.3 ./man/man3/log4cpp_*.3; do \
		inst=`basename $$i | sed 's/_/:/g'`; \
		echo "$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst"; \
		$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst; \
	done
	$(mkinstalldirs) $(DESTDIR)$(docdir)
	cp -r html $(docdir)
	$(RM) -r -f $(docdir)/html/CVS \
		$(docdir)/html/Makefile.am \
		$(docdir)/html/Makefile.in \
		$(docdir)/html/Makefile

uninstall-data-local:
	$(RM) $(DESTDIR)$(man3dir)/log4cpp.3
	$(RM) $(DESTDIR)$(man3dir)/log4cpp_*.3
	$(RM) -r -f $(docdir)

clean-local:
	$(RM) -r latex
	$(RM) -r html/api man @PACKAGE_TARNAME@.ps @PACKAGE_TARNAME@.pdf
