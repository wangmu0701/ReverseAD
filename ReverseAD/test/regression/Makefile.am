AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include -lmath

noinst_PROGRAMS = test_identity test_square test_quad\
                  test_param test_preacc\
                  test_checkpointing\
                  test_single_forward test_multi_forward

test_identity_SOURCES = test_identity.cpp test_main.cpp
test_identity_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_square_SOURCES = test_square.cpp test_main.cpp
test_square_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_quad_SOURCES = test_quad.cpp test_main.cpp
test_quad_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_param_SOURCES = test_param.cpp test_main.cpp
test_param_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_preacc_SOURCES = test_preacc.cpp test_main.cpp
test_preacc_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_checkpointing_SOURCES = test_checkpointing.cpp
test_checkpointing_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_single_forward_SOURCES = test_single_forward.cpp test_util.cpp
test_single_forward_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_multi_forward_SOURCES = test_multi_forward.cpp test_util.cpp
test_multi_forward_LDADD = $(top_builddir)/ReverseAD/libreversead.la
