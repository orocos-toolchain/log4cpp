/*
 * BasicLayout.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Hints.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    BasicLayout::BasicLayout() {
    }
    
    BasicLayout::~BasicLayout() {
    }

    char* BasicLayout::format(const LoggingEvent& event) {
        ostrstream message;

        const std::string& priorityName = Priority::getPriorityName(event.priority);
        message << event.timeStamp << " " << priorityName << " " 
                << event.categoryName << " " << event.ndc << ": " 
                << event.message << std::endl << '\0';

        return message.str();
    }
}
