man3dir = $(mandir)/man3
docdir  = $(prefix)/doc/log4cpp-@VERSION@

all-local: dox #pdf

dox: html/index.html
html/index.html:
	@DOXYGEN@

pdf: log4cpp.pdf
log4cpp.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 log4cpp.ps
	ln -s ./latex/refman.pdf log4cpp.pdf


install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(man3dir)
	@for i in ./man/man3/*.3; do \
		inst=`basename $$i | sed 's/_/:/g'`; \
		echo "$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst"; \
		$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst; \
	done
	$(mkinstalldirs) $(DESTDIR)$(docdir)
#	@for i in ../README ../ChangeLog log4cpp.ps log4cpp.pdf; do \
#		echo "$(INSTALL_DATA) $$i $(DESTDIR)$(docdir)"; \
#		$(INSTALL_DATA) $$i $(DESTDIR)$(docdir); \
#	done
	cp -r html $(docdir)

clean-local:
	$(RM) -r latex
	$(RM) -r html man log4cpp.ps log4cpp.pdf
