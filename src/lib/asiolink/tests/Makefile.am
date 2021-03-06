AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(srcdir)/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/asiolink/tests\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda test-socket

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += addr_utilities_unittest.cc
run_unittests_SOURCES += io_address_unittest.cc
run_unittests_SOURCES += hash_address_unittest.cc
run_unittests_SOURCES += io_endpoint_unittest.cc
run_unittests_SOURCES += io_socket_unittest.cc
run_unittests_SOURCES += interval_timer_unittest.cc
run_unittests_SOURCES += tcp_endpoint_unittest.cc
run_unittests_SOURCES += tcp_socket_unittest.cc
run_unittests_SOURCES += udp_endpoint_unittest.cc
run_unittests_SOURCES += udp_socket_unittest.cc
run_unittests_SOURCES += io_service_unittest.cc
run_unittests_SOURCES += dummy_io_callback_unittest.cc
run_unittests_SOURCES += tcp_acceptor_unittest.cc
run_unittests_SOURCES += unix_domain_socket_unittest.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)

run_unittests_LDADD  = $(top_builddir)/src/lib/asiolink/testutils/libasiolinktest.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

# Note: the ordering matters: -Wno-... must follow -Wextra (defined in
# KEA_CXXFLAGS)
run_unittests_CXXFLAGS = $(AM_CXXFLAGS)
if USE_GXX
run_unittests_CXXFLAGS += -Wno-unused-parameter -Wno-unused-private-field
endif
endif

noinst_PROGRAMS = $(TESTS)
