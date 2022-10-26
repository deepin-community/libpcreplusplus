pcre_linklib    = ../libpcre++/.libs/libpcre++.a
noinst_PROGRAMS = demo replace_demo search_demo

demo_SOURCES    = demo.cc
demo_LDADD      = $(pcre_linklib)

replace_demo_SOURCES = replace_demo.cc
replace_demo_LDADD   = $(pcre_linklib)

search_demo_SOURCES  = search_demo.cc
search_demo_LDADD    = $(pcre_linklib)

CXXFLAGS        = -Wall -Wstrict-prototypes -O -g