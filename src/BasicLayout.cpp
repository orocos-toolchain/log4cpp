/*
 * BasicLayout.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"
#include "log4cpp/OstringStream.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    BasicLayout::BasicLayout() {
    }
    
    BasicLayout::~BasicLayout() {
    }

    std::string BasicLayout::format(const LoggingEvent& event) {
        OstringStream message;

        const std::string& priorityName = Priority::getPriorityName(event.priority);
        message << event.timeStamp.getSeconds() << " " << priorityName << " " 
                << event.categoryName << " " << event.ndc << ": " 
                << event.message << std::endl;

        return message.str();
    }
}
