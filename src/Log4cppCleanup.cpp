/*
 * Log4cppCleanup.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Log4cppCleanup.hh"
#include "log4cpp/HierarchyMaintainer.hh"
#include "log4cpp/Appender.hh"
#include <cassert>
#include <iostream>

namespace log4cpp {
    Log4cppCleanup Log4cppCleanup::_cleanup;

    Log4cppCleanup::Log4cppCleanup() {
        std::cerr << "Log4cppCleanup construct" << std::endl;
    }

    Log4cppCleanup::~Log4cppCleanup() {
        std::cerr << "Log4cppCleanup destruct" << std::endl;
    
        if (HierarchyMaintainer::_defaultMaintainer)
            delete HierarchyMaintainer::_defaultMaintainer;
        if (Appender::_allAppenders) {
            Appender::_deleteAllAppenders();
            delete Appender::_allAppenders;
        }            
    }
}
