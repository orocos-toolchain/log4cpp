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

#include "log4cpp/OstringStream.hh"

namespace log4cpp {

    /**
     * Log4cppCleanup is an internal janitor class, responsible for cleaning
     * up log4cpp objects upon exit. The current mechanism is imperfect:
     * it uses a static object, which seems to give problems with shared 
     * libraries on some platforms.
     **/
    class Log4cppCleanup {
        private:
        Log4cppCleanup();

        public:
        ~Log4cppCleanup();

        public:
#ifdef LOG4CPP_USE_CLEANUP
        static Log4cppCleanup _cleanup;
#endif        
    };
}

#endif // _LOG4CPP_LOG4CPPCLEANUP_HH
