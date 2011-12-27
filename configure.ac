dnl Configure.ac for fedora-freemedia-tools
dnl
dnl TODOs: 
dnl - correct url
dnl - change test.cpp to main.cpp in srcdir
dnl
dnl Copyright Ankur Sinha: Franciscod 2011


AC_INIT([fedora-freemedia-tools],[1.0],[ankursinha@fedoraproject.org], , [http://gitorious.org/fedora-freemedia-tools])
AM_INIT_AUTOMAKE([-W -Wall -Werror dist-bzip2 dist-zip check-news])
PACKAGE=fft
AC_CONFIG_SRCDIR([src/test.cpp])

AM_MAINTAINER_MODE    
AC_PROG_CXX
AC_PROG_INSTALL



PKG_CHECK_MODULES(PACKAGE, sqlite3)
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

AC_CONFIG_FILES([Makefile src/Makefile])    
AC_OUTPUT
