## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libNHparser.la
libNHparser_la_SOURCES = NHgrammar.y NH.l NHerror.c NHerror.h \
	NHgrammar-common.h NHparser.c NHparser.h NHtypes.h
BUILT_SOURCES = NHgrammar.h
libNHparser_la_LDFLAGS = -version-info 0:0:0
libNHparser_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)
AM_YFLAGS = -d

pkginclude_HEADERS = NHparser.h NHtypes.h

check_PROGRAMS = NHtester
NHtester_SOURCES = NHtester.c NHtypes.h NHparser.h
NHtester_LDADD = libNHparser.la
NHtester_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)

MOSTLYCLEANFILES = NHgrammar.output
