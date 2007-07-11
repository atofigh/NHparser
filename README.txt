This file contains information on how to compile and install the
NHparser library.

                     COMPILATION AND INSTALLATION
                     ============================

To compile and install the NHparser library do:

$ cd <NHparser-directory>
$ make
$ make lib

Then, copy the files NHparser.h and NHtypes.h to an appropriate
directory containing the system's include-files -- typically
/usr/include --, and copy the file libNHparser.a to an appropriate
directory containing the system's library files -- typically /usr/lib:

$ cp NHparser.h NHtypes.h /usr/include
$ cp libNHparser.a /usr/lib

To use the parser, just include the file NHparser.h in your C-code and
use the functions declared in the include file. During linking make
sure that your linker/compiler links with libNHparser. You would
typically do this by giving the flag -lNHparser.

The makefile assumes that the GNU C-Compiler, 'gcc', and the program
'ar' are available in your system. If not, or if you would like to use
a different compiler, you will have to manually tweak the makefile.
