/*
 * Priority.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_PRIORITY_HH
#define _LOG4CPP_PRIORITY_HH

#include <string>

namespace log4cpp {

    class Priority {
        public:
        typedef enum {EMERG  = 0, 
                      ALERT  = 100,
                      CRIT   = 200,
                      ERROR  = 300, 
                      WARN   = 400,
                      NOTICE = 500,
                      INFO   = 600,
                      DEBUG  = 700,
                      NOTSET = 800
        } PriorityLevel;

        static const string& getPriorityName(int priority);        
    };
}

#endif // _LOG4CPP_PRIORITY_HH
