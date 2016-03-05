AM_CXXFLAGS = @ac_reversead_cxxflags@ 
AM_CPPFLAGS = -I$(top_builddir)/ReverseAD/include

noinst_LTLIBRARIES = libalgorithm.la

libalgorithm_la_SOURCES = base_reverse_mode.cpp\
                          base_reverse_adjoint.cpp\
                          base_reverse_hessian.cpp\
                          base_reverse_third.cpp\
                          base_reverse_generic.cpp\
                          base_function_replay.cpp\
                          base_reverse_generator.cpp
