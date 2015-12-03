AM_CXXFLAGS = @ac_reversead_cxxflags@ 
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include

SUBDIRS = util

if ENABLE_REVERSEAD_MPI

SUBDIRS += rmpi

endif

noinst_LTLIBRARIES = libreverseadsrc.la

libreverseadsrc_la_SOURCES = reversead_base.cpp
