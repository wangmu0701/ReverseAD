AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include -lmath

noinst_PROGRAMS = forward_over_reverse

forward_over_reverse_SOURCES = forward_over_reverse.cpp

forward_over_reverse_LDADD = $(top_builddir)/ReverseAD/libreversead.la
