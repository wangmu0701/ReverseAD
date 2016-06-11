AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include -lmath

noinst_PROGRAMS = high_order

high_order_SOURCES = high_order.cpp

high_order_LDADD = $(top_builddir)/ReverseAD/libreversead.la
