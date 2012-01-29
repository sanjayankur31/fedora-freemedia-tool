dnl Configure.ac for fedora-freemedia-tools
dnl
dnl TODOs: 
dnl - correct url
dnl - change test.cpp to main.cpp in srcdir
dnl
dnl Copyright Ankur Sinha: Franciscod 2011


AC_INIT([fedora-freemedia-tools],[0.1-alpha],[ankursinha@fedoraproject.org], , [http://gitorious.org/fedora-freemedia-tools])
AM_INIT_AUTOMAKE([-W -Wall -Werror dist-bzip2 dist-zip check-news])
PACKAGE=fft
AC_CONFIG_SRCDIR([src/test.cpp])
AC_CONFIG_HEADER(config.h)

AM_MAINTAINER_MODE    
AC_PROG_CXX
AC_PROG_INSTALL


PKG_CHECK_MODULES(PACKAGE, sqlite3 Magick++ curlpp)
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

dnl add boost
AC_ARG_WITH([boost-include-path],
            [AS_HELP_STRING([--with-boost-include-path],
                            [location of the boost headers, defaults to /usr/include/boost])],
                            [BOOST_CFLAGS="-I$withval"],
                            [BOOST_CFLAGS='-I/usr/include/boost'])
AC_SUBST([BOOST_CFLAGS])

AC_ARG_WITH([boost-lib-path],
            [AS_HELP_STRING([--with-boost-lib-path], [location of the boost libraries])],
            [BOOST_LIBS="-L$withval -lboost_program_options"],
            [BOOST_LIBS='-lboost_program_options'])
AC_SUBST([BOOST_LIBS])

AC_CONFIG_FILES([Makefile src/Makefile])    
AC_OUTPUT
