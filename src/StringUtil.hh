/*
 * StringUtil.hh
 *
 * Copyright 2002, Log4cpp Project. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_STRINGUTIL_HH
#define _LOG4CPP_STRINGUTIL_HH

#include <log4cpp/Portability.hh>
#include <string>

namespace log4cpp {

    /**
       Returns a string identical to the given string but without leading or
       trailing HTABs or spaces.
    **/
    class StringUtil {
        public:
        static std::string trim(const std::string& s);
    };
}

#endif // _LOG4CPP_STRINGUTIL_HH

