AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include -lmath

noinst_PROGRAMS = test_simple

test_simple_SOURCES = test_simple.cpp

test_simple_LDADD = $(top_builddir)/ReverseAD/libreversead.la
