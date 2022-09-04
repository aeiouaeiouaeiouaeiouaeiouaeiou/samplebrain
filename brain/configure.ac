AC_INIT(samplebrain, version-0.1)
: ${CXXFLAGS="-O3"}
AC_PROG_CC

AC_CHECK_LIB(m, cos)
AC_CHECK_LIB(pthread, main)
AC_CHECK_LIB(fftw3, main)
AC_CHECK_LIB(portaudio, main)
AC_CHECK_LIB(sndfile, main)
AC_CHECK_LIB(lo, main)

AC_PROG_CXX
AC_LANG(C++)
AC_CHECK_HEADERS(iostream)

AC_CONFIG_HEADER(src/config.h)
AC_OUTPUT(Makefile)
