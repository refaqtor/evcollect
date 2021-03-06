## Process this file with automake to produce Makefile.in

MAINTAINERCLEANFILES =   \
  Makefile.in

# we'll fill those later
bin_PROGRAMS =
noinst_LIBRARIES =
dist_noinst_DATA =
BUILT_SOURCES =
TESTS =
check_PROGRAMS =


################# DEPENDENCIES ####################
if HAVE_ZLIB
ZLIB_DEF = -DHAVE_ZLIB=1
else
ZLIB_DEF =
endif

if HAVE_PTHREAD
PTHREAD_DEF = -DHAVE_PTHREAD=1
PTHREAD_LDFLAGS_=-lpthread
else
PTHREAD_DEF =
endif

DL_LDFLAGS_ = -ldl

if HAVE_SYSLOG_H
SYSLOG_DEF = -DHAVE_SYSLOG_H=1
else
SYSLOG_DEF =
endif

if HAVE_GETHOSTBYNAME_R
GETHOSTBYNAME_R_DEF = -DHAVE_GETHOSTBYNAME_R=1
else
GETHOSTBYNAME_R_DEF =
endif

PCRE_LDFLAGS_=-lpcre
CURL_LDFLAGS_=-lcurl

AM_CXXFLAGS = -DEVCOLLECT_VERSION=\"v@PACKAGE_VERSION@\" $(PTHREAD_CFLAGS) $(PTHREAD_DEF) $(SYSLOG_DEF) $(ZLIB_DEF) $(GETHOSTBYNAME_R_DEF) -std=c++0x -ftemplate-depth=500 -mno-omit-leaf-frame-pointer -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -Wdelete-non-virtual-dtor -Wno-predefined-identifier-outside-function -Wno-invalid-offsetof -g -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CFLAGS =  $(PTHREAD_CFLAGS) $(PTHREAD_DEF) $(SYSLOG_DEF) $(ZLIB_DEF) $(GETHOSTBYNAME_R_DEF) -std=c11 -mno-omit-leaf-frame-pointer -fno-omit-frame-pointer -Wall -pedantic -g
AM_LDFLAGS = $(PTHREAD_CFLAGS) -export-dynamic -rdynamic
AM_LDADD = $(PCRE_LDFLAGS_) $(CURL_LDFLAGS_) $(PTHREAD_LDFLAGS_) $(DL_LDFLAGS_)

EVCOLLECT_SOURCES_ = \
		util/ansicolor.h \
		util/ansicolor.cc \
    util/logging.h \
    util/logging.cc \
    util/flagparser.h \
    util/flagparser.cc \
    util/return_code.h \
    util/stringutil.h \
    util/stringutil_impl.h \
    util/stringutil.cc \
    util/testing.h \
    util/testing.cc \
    util/time.h \
    util/time_impl.h \
    util/time.cc \
    util/sha1.h \
    util/sha1.cc \
    util/base64.h \
    config.h \
    config.cc \
    plugin.h \
    plugin.cc \
    logfile.h \
    logfile.cc \
    service.h \
    service.cc \
    evcollect.h

####### EVCOLLECTD ############################################################

evcollectd_SOURCES = \
		${EVCOLLECT_SOURCES_} \
		evcollectd.cc

evcollectd_LDADD = \
		${AM_LDADD}

bin_PROGRAMS += evcollectd

####### TESTS #################################################################

TESTS += evcollectd_test
check_PROGRAMS += evcollectd_test

evcollectd_test_LDFLAGS = \
		${AM_LDADD}

evcollectd_test_SOURCES = \
		util/testing_main.cc \
		${EVCOLLECT_SOURCES_} \
		evcollectd_test.cc
