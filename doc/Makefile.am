man_MANS = Pcre.3
EXTRA_DIST = $(man_MANS)

DOC_FILES = html/* ../README ../COPYING ../AUTHORS ../INSTALL ../ChangeLog ../config.log

install-data-local:
	$(INSTALL) -m 755 -d $(prefix)/doc/libpcre++-$(VERSION)
	$(INSTALL) -m 644 $(DOC_FILES) $(prefix)/doc/libpcre++-$(VERSION)/