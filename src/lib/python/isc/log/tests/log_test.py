# Copyright (C) 2011  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# This tests it can be loaded, nothing more yet
import isc.log
import unittest

class LogDict(unittest.TestCase):
    def setUp(self):
        # We work on a test dictionary now.
        isc.log.set_test_dictionary(True)
    def tearDown(self):
        # Return to the global dictionary
        isc.log.set_test_dictionary(False)

    def test_load_msgs(self):
        # Try loading a message and see it's there, but nothing more
        self.assertEqual(isc.log.create_message("ID", "Text"), "ID")
        self.assertEqual(isc.log.get_message("ID"), "Text")
        self.assertEqual(isc.log.get_message("no-ID"), None)

class Manager(unittest.TestCase):
    def tearDown(self):
        isc.log.reset()

    def test_init_debug(self):
        # We try calling it now only, as we don't have any other functions
        # to check the outcome by it. Once we add the logger class, we may
        # check more.
        isc.log.init("root", None, "DEBUG", 50)

    def test_init_defaults(self):
        # We try calling it now only, as we don't have any other functions
        # to check the outcome by it. Once we add the logger class, we may
        # check more.
        isc.log.init("root")

    def test_init_notfound(self):
        # This should not throw, because the C++ one doesn't. Should we really
        # ignore errors like missing file?
        isc.log.init("root", "/no/such/file");

class Logger(unittest.TestCase):
    def tearDown(self):
        isc.log.reset()

    def setUp(self):
        isc.log.init("root", None, "DEBUG", 50)

    # Checks defaults of the logger
    def defaults(self, logger):
        self.assertEqual(logger.get_effective_severity(), "DEBUG")
        self.assertEqual(logger.get_debug_level(), 0)

    # Because there's a bug in the C++ backend currently. When it's fixed,
    # it should no longer fail
    @unittest.expectedFailure
    def test_default_severity(self):
        logger = isc.log.Logger("child")
        self.defaults(logger)

    # Try changing the severities little bit
    def test_severity(self):
        logger = isc.log.Logger("child")
        logger.set_severity('DEBUG', 25)
        self.assertEqual(logger.get_effective_severity(), "DEBUG")
        self.assertEqual(logger.get_debug_level(), 25)
        for sev in ['INFO', 'WARN', 'ERROR', 'FATAL']:
            logger.set_severity(sev)
            self.assertEqual(logger.get_effective_severity(), sev)
            self.assertEqual(logger.get_debug_level(), 0)
        # Return to default
        logger.set_severity(None)
        # The same bug here
        #self.defaults(logger)

if __name__ == '__main__':
    unittest.main()
