/*
 * Log4cppCleanup.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"
#include "log4cpp/Log4cppCleanup.hh"
#include "log4cpp/HierarchyMaintainer.hh"
#include "log4cpp/Appender.hh"
#include <iostream>

namespace log4cpp {
#ifdef LOG4CPP_USE_CLEANUP
    Log4cppCleanup Log4cppCleanup::_cleanup;
#endif

    Log4cppCleanup::Log4cppCleanup() {
#ifdef LOG4CPP_DEBUGCLEANUP
        std::cerr << "Log4cppCleanup construct" << std::endl;
#endif
    }

    Log4cppCleanup::~Log4cppCleanup() {
#ifdef LOG4CPP_DEBUGCLEANUP
        std::cerr << "Log4cppCleanup destruct" << std::endl;
#endif
    
        if (HierarchyMaintainer::_defaultMaintainer)
            delete HierarchyMaintainer::_defaultMaintainer;
        if (Appender::_allAppenders) {
            Appender::_deleteAllAppenders();
            delete Appender::_allAppenders;
        }            
    }
}
