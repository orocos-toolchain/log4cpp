/*
 * Priority.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_PRIORITY_HH
#define _LOG4CPP_PRIORITY_HH

#include <string>

namespace log4cpp {

    class Priority {
        public:

        /*
         * Work around rudeness in windows.h on Win32.
         */
#ifdef ERROR
#   define _LOG4CPP_TMP_ERROR_VALUE ERROR
#   undef ERROR
#endif // ERROR

        typedef enum {EMERG  = 0, 
		      FATAL  = 0,
                      ALERT  = 100,
                      CRIT   = 200,
                      ERROR  = 300, 
                      WARN   = 400,
                      NOTICE = 500,
                      INFO   = 600,
                      DEBUG  = 700,
                      NOTSET = 800
        } PriorityLevel;

#ifdef _LOG4CPP_TMP_ERROR_VALUE
#   define ERROR _LOG4CPP_TMP_ERROR_VALUE
#   undef _LOG4CPP_TMP_ERROR_VALUE
#endif // _LOG4CPP_TMP_ERROR_VALUE

        typedef int Value;

        static const std::string& getPriorityName(int priority) throw();
    };
}

#endif // _LOG4CPP_PRIORITY_HH
