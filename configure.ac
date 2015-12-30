dnl This is how it begins
AC_INIT(ReverseAD, 0.0.1, wangmu0701@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])

LT_INIT


AC_PROG_CC
AC_PROG_CXX

ac_reversead_cxxflags="-O3 -std=c++11 -Wall -m64"
AC_SUBST(ac_reversead_cxxflags)
AC_MSG_RESULT($ac_reversead_cxxflags)
#AX_CXX_COMPILE_STDCXX_11(noext,mandatory)

AC_MSG_CHECKING(whether to enable mpi)
AC_ARG_ENABLE(mpi, [AS_HELP_STRING([--enable-mpi],
  [enable mpi in ReverseAD [default=no]])],
  [enable_mpi=$enableval], [enable_mpi=no])
AC_MSG_RESULT($enable_mpi)

AM_CONDITIONAL(ENABLE_REVERSEAD_MPI, [test x$enable_mpi = xyes])

if test x$enable_mpi = xyes ; then
  ENABLE_MPI="#define ENABLE_REVERSEAD_MPI 1"
else
  ENABLE_MPI="#undef ENABLE_REVERSEAD_MPI"
fi
AC_SUBST(ENABLE_MPI)


# output
AC_CONFIG_FILES(Makefile
                ReverseAD/Makefile
                ReverseAD/src/Makefile
                ReverseAD/src/activetype/Makefile
                ReverseAD/src/common/Makefile
                ReverseAD/src/algorithm/Makefile
                ReverseAD/src/forwardtype/Makefile
                ReverseAD/src/util/Makefile
                ReverseAD/src/rmpi/Makefile
                ReverseAD/include/Makefile
                ReverseAD/include/reversead/Makefile
                ReverseAD/include/reversead/activetype/Makefile
                ReverseAD/include/reversead/algorithm/Makefile
                ReverseAD/include/reversead/forwardtype/Makefile
                ReverseAD/include/reversead/common/Makefile
                ReverseAD/include/reversead/tape/Makefile
                ReverseAD/include/reversead/trace/Makefile
                ReverseAD/include/reversead/util/Makefile
                ReverseAD/include/reversead/rmpi/Makefile
                ReverseAD/include/reversead/common/reversead_config.h
                ReverseAD/test/Makefile
                ReverseAD/test/regression/Makefile
                ReverseAD/test/forward/Makefile
                ReverseAD/test/algorithm/Makefile
                ReverseAD/test/tape/Makefile
                ReverseAD/test/trace/Makefile
                ReverseAD/test/rosenbrock/Makefile
                ReverseAD/test/simple/Makefile
                ReverseAD/test/mpi/Makefile
)

AC_OUTPUT
