dnl This is how it begins
AC_INIT(ReverseAD, 0.0.1, wangmu0701@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])

LT_INIT


AC_PROG_CC
AC_PROG_CXX

ac_reversead_cxxflags="-O3 -std=c++11 -Wall"
AC_SUBST(ac_reversead_cxxflags)
AC_MSG_RESULT($ac_reversead_cxxflags)
#AX_CXX_COMPILE_STDCXX_11(noext,mandatory)

# output
AC_CONFIG_FILES(Makefile
                ReverseAD/Makefile
                ReverseAD/src/Makefile
                ReverseAD/include/Makefile
                ReverseAD/include/reversead/Makefile
                ReverseAD/include/reversead/algorithm/Makefile
                ReverseAD/include/reversead/trace/Makefile
                ReverseAD/include/reversead/tape/Makefile
                ReverseAD/test/Makefile
                ReverseAD/test/algorithm/Makefile
                ReverseAD/test/tape/Makefile
                ReverseAD/test/trace/Makefile
                ReverseAD/test/rosenbrock/Makefile
                ReverseAD/test/simple/Makefile
                ReverseAD/test/mpi/Makefile
)

AC_OUTPUT
