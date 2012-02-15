dnl Configure.ac for fedora-freemedia-tools
dnl
dnl Copyright Ankur Sinha: Franciscod 2011


AC_INIT([fedora-freemedia-tools],[0.2-alpha],[sanjay DOT ankur AT gmail DOT com],fedora-freemedia-tool, [https://gitorious.org/fedora-freemedia-tool])
AM_INIT_AUTOMAKE([-W -Wall -Werror dist-bzip2 dist-zip check-news])
PACKAGE=ffmt
AC_CONFIG_SRCDIR([src/main.cpp])
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

dnl AC_DEFINE_UNQUOTED([DATADIR], ["$datadir"], [Define to the read-only architecture-independent data directory.])
dnl AC_SUBST([DATADIR])


AC_CONFIG_FILES([Makefile src/Makefile])    
AC_OUTPUT
