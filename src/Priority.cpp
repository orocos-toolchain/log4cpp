/*
 * Priority.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    const std::string& Priority::getPriorityName(int priority) throw() {
        static std::string names[10] = {
            "FATAL", "ALERT", "CRIT", "ERROR", "WARN",
            "NOTICE", "INFO", "DEBUG", "NOTSET", "UNKNOWN" 
        };
        
        priority++;
        priority /= 100;
        return ((priority < 0) || (priority > 8)) ?
            names[8] :
            names[priority - 1];
    }
}
