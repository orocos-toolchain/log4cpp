/*
 * SimpleLayout.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Hints.hh"
#include "log4cpp/SimpleLayout.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    SimpleLayout::SimpleLayout() {
    }
    
    SimpleLayout::~SimpleLayout() {
    }

    std::string SimpleLayout::format(const LoggingEvent& event) {
        ostringstream message;

        const std::string& priorityName = Priority::getPriorityName(event.priority);
        message << priorityName << " - " << event.message << std::endl;

        message.str();
    }
}
