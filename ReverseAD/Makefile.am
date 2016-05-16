AUTOMAKE_OPTIONS = foreign

SUBDIRS = include src . test

lib_LTLIBRARIES = libreversead.la

libreversead_la_SOURCES = dummy.cpp
libreversead_la_LIBADD = src/common/libcommon.la
libreversead_la_LIBADD += src/util/libutil.la
libreversead_la_LIBADD += src/algorithm/libalgorithm.la
libreversead_la_LIBADD += src/activetype/libactivetype.la
libreversead_la_LIBADD += src/forwardtype/libforwardtype.la
libreversead_la_LIBADD += src/driver/libdriver.la
libreversead_la_LIBADD += src/checkpointing/libcheckpointing.la

test:
	cd test; $(MAKE) test

.PHONY: test
