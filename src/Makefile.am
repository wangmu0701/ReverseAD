AUTOMAKE_OPTIONS = foreign

SUBDIRS = tape trace core algorithm

lib_LTLIBRARIES = libreversead.la
libreversead_la_LIBADD = tape/libreverseadtape.la
libreversead_la_LIBADD += trace/libreverseadtrace.la
libreversead_la_LIBADD += core/libreverseadcore.la
libreversead_la_LIBADD += algorithm/libreverseadalgorithm.la
libreversead_la_SOURCES = dummy.cpp
