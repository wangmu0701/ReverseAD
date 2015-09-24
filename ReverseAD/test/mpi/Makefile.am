AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include

noinst_PROGRAMS = test_mpi

test_mpi_SOURCES = test_mpi.cpp

test_mpi_LDADD = $(top_builddir)/ReverseAD/libreversead.la
