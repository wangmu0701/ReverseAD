AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include

noinst_PROGRAMS = test_base_reverse test_checkpointing

test_base_reverse_SOURCES = test_base_reverse.cpp

test_base_reverse_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_checkpointing_SOURCES = test_checkpointing.cpp

test_checkpointing_LDADD = $(top_builddir)/ReverseAD/libreversead.la
