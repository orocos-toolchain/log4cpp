/*
 * LoggingEvent.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_LOGGINGEVENT_HH
#define _LOG4CPP_LOGGINGEVENT_HH

#include <string>

namespace log4cpp {

    struct LoggingEvent {
    public:
        LoggingEvent(const string& categoryName, const string& message, 
                     const string& ndc, int priority);

        const string& categoryName;
        const string& message;
        const string& ndc;
        int priority;
        const string& threadName;
        time_t timeStamp;
    };
}

#endif // _LOG4CPP_LOGGINGEVENT_HH

