/*
 * SimpleConfigurator.hh
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#ifndef _LOG4CPP_PROPERTYCONFIGURATOR_HH
#define _LOG4CPP_PROPERTYCONFIGURATOR_HH

#include <log4cpp/Portability.hh>
#include <log4cpp/Export.hh>

#include <string>
#include <stdexcept>
#include <log4cpp/Configurator.hh>	// configure exceptions
#include <log4cpp/ConfiguratorSkeleton.hh>	// base class

#include <iostream>
#include <fstream>

namespace log4cpp {

    /**
     * Property configurator will read a config file using the same (or similar)
     * format to the config file used by log4j.  This file is in a standard Java
     * "properties" file format.
     */
    class LOG4CPP_EXPORT PropertyConfigurator : ConfiguratorSkeleton {
        public:
        PropertyConfigurator();
        ~PropertyConfigurator();
        static void configure(const std::string& initFileName) throw (ConfigureFailure);

	private:
        static void parseConfig(std::ifstream& init) throw (ConfigureFailure);
    };
}

#endif // _LOG4CPP_PROPERTYCONFIGURATOR_HH
