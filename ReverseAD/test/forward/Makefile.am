AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include -lmath

noinst_PROGRAMS = test_forward test_multi_forward

test_forward_SOURCES = test_forward.cpp

test_forward_LDADD = $(top_builddir)/ReverseAD/libreversead.la


test_multi_forward_SOURCES = test_multi_forward.cpp

test_multi_forward_LDADD = $(top_builddir)/ReverseAD/libreversead.la

