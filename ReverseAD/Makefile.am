AUTOMAKE_OPTIONS = foreign

SUBDIRS = include src . test

lib_LTLIBRARIES = libreversead.la

libreversead_la_SOURCES = dummy.cpp
libreversead_la_LIBADD = src/libreverseadsrc.la
libreversead_la_LIBADD += src/util/libutil.la
libreversead_la_LIBADD += src/reverseadmpi/libreverseadmpi.la

test:
	cd test; $(MAKE) test

.PHONY: test
