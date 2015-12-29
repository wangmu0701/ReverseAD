AUTOMAKE_OPTIONS = foreign

SUBDIRS = include src . test

lib_LTLIBRARIES = libreversead.la

libreversead_la_SOURCES = dummy.cpp
libreversead_la_LIBADD = src/common/libcommon.la
libreversead_la_LIBADD += src/util/libutil.la
libreversead_la_LIBADD += src/algorithm/libalgorithm.la

if ENABLE_REVERSEAD_MPI

libreversead_la_LIBADD += src/rmpi/librmpi.la

endif

test:
	cd test; $(MAKE) test

.PHONY: test
