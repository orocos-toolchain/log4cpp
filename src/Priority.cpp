/*
 * Priority.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Priority.hh"

namespace log4cpp {

    const string& Priority::getPriorityName(int priority) {
        static string names[9] = {"PANIC", "ALERT", "ERROR", "WARN", "NOTICE",
                                  "INFO", "DEBUG", "NOTSET", "UNKOWN" };
        
        priority++;
        priority /= 100;
        return ((priority < 1) || (priority > 8)) ?
            names[8] :
            names[priority - 1];
    }
}
