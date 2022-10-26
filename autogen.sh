#!/bin/sh
set -x

find . -name Makefile -exec rm {} \;
find . -name "*~"     -exec rm {} \;
find . -name config.h -exec rm {} \;
find . -name stamp.h  -exec rm {} \;
find . -name .deps    -exec rm -rf {} \;
find . -name .libs    -exec rm -rf {} \;

rm -rf config.cache config.status config.log pcre++-config *~

aclocal
autoheader
autoconf2.50
automake -a

doxygen doc/.doxygen

cd doc
    rm -f Pcre.3
    ln -s man/man3/Pcre.3 .
