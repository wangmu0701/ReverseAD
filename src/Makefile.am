AUTOMAKE_OPTIONS = foreign

SUBDIRS = tape trace

lib_LTLIBRARIES = libreversead.la
libreversead_la_LIBADD = tape/libreverseadtape.la
libreversead_la_LIBADD += trace/libreverseadtrace.la
libreversead_la_SOURCES = core/reversead.hpp dummy.cpp
