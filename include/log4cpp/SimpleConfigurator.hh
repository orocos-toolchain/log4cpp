/*
 * SimpleConfigurator.hh
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#ifndef _LOG4CPP_SIMPLECONFIGURATOR_HH
#define _LOG4CPP_SIMPLECONFIGURATOR_HH

#include <log4cpp/Portability.hh>
#include <iostream>
#include <string>
#include <log4cpp/Configurator.hh>

namespace log4cpp {

    /**
     * This class implements a simple Configurator for log4cpp.
     * It is a temporary hack with an undocumented configuration format.
     * It should be superseded with a PropertyConfigurator and XMLConfigurator
     * class in newer versions of log4cpp.
     **/
    class LOG4CPP_EXPORT SimpleConfigurator {
    public:

        /**
         * Configure log4cpp with the configuration in the given file.
         * NB. The configuration file format is undocumented and may change
         * without notice.
         * @since 0.2.6
         * @param initFileName name of the configuration file
         * @exception ConfigureFailure if the method encountered a read or 
         * syntax error.
         **/
        static void configure(const std::string& initFileName) throw (ConfigureFailure);

        /**
         * Configure log4cpp with the configuration in the given file.
         * NB. The configuration file format is undocumented and may change
         * without notice.
         * @since 0.3.1
         * @param initFile an input stream to the configuration file
         * @exception ConfigureFailure if the method encountered a read or 
         * syntax error.
         **/
        static void configure(std::istream& initFile) throw (ConfigureFailure);    };
}

#endif
