/*
 * SimpleConfigurator.hh
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#ifndef _LOG4CPP_SIMPLECONFIGURATOR_HH
#define _LOG4CPP_SIMPLECONFIGURATOR_HH

#include "log4cpp/Portability.hh"
#include "log4cpp/Export.hh"
#include <string>
#include <stdexcept>

namespace log4cpp {

    class LOG4CPP_EXPORT ConfigureFailure : public std::runtime_error {
    public:
        ConfigureFailure(const std::string& reason);
    };

    class LOG4CPP_EXPORT SimpleConfigurator {
    public:
        static void configure(const std::string& initFileName) throw (ConfigureFailure);
    };
}

#endif
