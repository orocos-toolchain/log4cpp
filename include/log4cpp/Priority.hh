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

/*
 * Optionally work around rudeness in windows.h on Win32.
 */
#ifdef ERROR
#ifdef LOG4CPP_FIX_ERROR_COLLISION

namespace log4cpp {
    static const int _tmpERRORValue = ERROR;
}

#undef ERROR
    static const int ERROR = log4cpp::_tmpERRORValue;
#define ERROR ERROR

#else
#error Naming collision for 'ERROR' detected. Please read the FAQ for a \
       workaround. 
#endif // LOG4CPP_FIX_ERROR_COLLISION 

#endif // ERROR

namespace log4cpp {

    /**
     * The Priority class provides importance levels with which one
     * can categorize log messages.
     **/
    class Priority {
        public:

        /**
         * Predefined Levels of Priorities. These correspond to the
         * priority levels used by syslog(3).
         **/
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

        /**
         * The type of Priority Values
         **/
        typedef int Value;

        /**
         * Returns the name of the given priority value.
         * Currently, if the value is not one of the PriorityLevel values,
         * the method returns the name of the largest priority smaller 
         * the given value.
         * @param priority the numeric value of the priority.
         * @returns a string representing the name of the priority.
         **/
        static const std::string& getPriorityName(int priority) throw();
    };
}

#endif // _LOG4CPP_PRIORITY_HH
