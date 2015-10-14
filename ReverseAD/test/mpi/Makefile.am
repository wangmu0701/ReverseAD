AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include

noinst_PROGRAMS = test_mpi test_mpi_reduce test_mpi_thomson

test_mpi_SOURCES = test_mpi.cpp

test_mpi_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_mpi_reduce_SOURCES = test_mpi_reduce.cpp

test_mpi_reduce_LDADD = $(top_builddir)/ReverseAD/libreversead.la

test_mpi_thomson_SOURCES = test_mpi_thomson.cpp

test_mpi_thomson_LDADD = $(top_builddir)/ReverseAD/libreversead.la
