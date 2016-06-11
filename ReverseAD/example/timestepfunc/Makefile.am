AM_CXXFLAGS = @ac_reversead_cxxflags@
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include -lmath

noinst_PROGRAMS = timestep_func

timestep_func_SOURCES = timestep_func.cpp

timestep_func_LDADD = $(top_builddir)/ReverseAD/libreversead.la
