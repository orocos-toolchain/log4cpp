/*
 * LoggingEvent.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include <time.h>
#include "log4cpp/LoggingEvent.hh"

namespace log4cpp {
    
    LoggingEvent::LoggingEvent(const string& categoryName, 
                               const string& message,
                               const string& ndc, int priority) :
        categoryName(categoryName),
        message(message),
        ndc(ndc),
        priority(priority),
        threadName("thread1"),
        timeStamp(::time(NULL)) {
    }
}
