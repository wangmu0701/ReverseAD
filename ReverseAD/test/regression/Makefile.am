AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include -lmath

noinst_PROGRAMS = test_identity test_square test_param test_preacc test_quad

test_identity_SOURCES = test_identity.cpp

test_identity_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_square_SOURCES = test_square.cpp

test_square_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_quad_SOURCES = test_quad.cpp

test_quad_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_param_SOURCES = test_param.cpp

test_param_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_preacc_SOURCES = test_preacc.cpp

test_preacc_LDADD = $(top_builddir)/ReverseAD/libreversead.la
