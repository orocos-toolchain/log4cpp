/*
 * Log4cppCleanup.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_LOG4CPPCLEANUP_HH
#define _LOG4CPP_LOG4CPPCLEANUP_HH

#include "log4cpp/Hints.hh"

namespace log4cpp {
    class Log4cppCleanup {
        private:
        Log4cppCleanup();

        public:
        ~Log4cppCleanup();

        public:
        static Log4cppCleanup _cleanup;
    };
}

#endif // _LOG4CPP_LOG4CPPCLEANUP_HH
