man3dir = $(mandir)/man3
docdir  = $(prefix)/doc/@PACKAGE@-@VERSION@

all-local: dox #pdf

dox: html/index.html
html/index.html: Doxyfile
	@DOXYGEN@

pdf: @PACKAGE@.pdf
@PACKAGE@.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 @PACKAGE@.ps
	ln -s ./latex/refman.pdf @PACKAGE@.pdf


install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(man3dir)
	@for i in ./man/man3/*.3; do \
		inst=`basename $$i | sed 's/_/:/g'`; \
		echo "$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst"; \
		$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst; \
	done
	$(mkinstalldirs) $(DESTDIR)$(docdir)
#	@for i in ../README ../ChangeLog @PACKAGE@.ps @PACKAGE@.pdf; do \
#		echo "$(INSTALL_DATA) $$i $(DESTDIR)$(docdir)"; \
#		$(INSTALL_DATA) $$i $(DESTDIR)$(docdir); \
#	done
	cp -r html $(docdir)

clean-local:
	$(RM) -r latex
	$(RM) -r html man @PACKAGE@.ps @PACKAGE@.pdf
