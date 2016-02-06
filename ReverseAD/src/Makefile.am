AM_CXXFLAGS = @ac_reversead_cxxflags@ 
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include

SUBDIRS = activetype common util algorithm forwardtype driver checkpointing

if ENABLE_REVERSEAD_MPI

SUBDIRS += rmpi

endif
