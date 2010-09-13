# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([NHparser], [0.1], [alix.tofigh@gmail.com], [NHparser])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config/m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([NHparser/NHparser.c])
AC_CONFIG_HEADERS([config.h])
LT_PREREQ([2.2.6])
LT_INIT
AC_CANONICAL_BUILD

# Checks for programs.
AC_PROG_YACC
AC_PROG_CC
AM_PROG_LEX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([assert.h errno.h stdio.h stdlib.h string.h], [], 
                 [AC_MSG_ERROR([required header not found])])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([
    Makefile
    NHparser/Makefile
])
AC_OUTPUT
