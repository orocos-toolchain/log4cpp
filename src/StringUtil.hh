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
#include <vector>
#include <climits>

namespace log4cpp {

    class StringUtil {
        public:
        /**
           Returns a string identical to the given string but without leading
           or trailing HTABs or spaces.
        **/
        static std::string trim(const std::string& s);

        /**
           splits a string into a vector of string segments based on the
           given delimiter.
           @param v The vector in which the segments will be stored. The vector
           will be emptied before storing the segments
           @param s The string to split into segments.
           @param delimiter The delimiter character
           @param maxSegments the maximum number of segments. Upon return
           v.size() <= maxSegments.  The string is scanned from left to right
           so v[maxSegments - 1] may contain a string containing the delimiter
           character.
        **/
        static void split(std::vector<std::string>& v, const std::string& s,
                          char delimiter, unsigned int maxSegments = INT_MAX);
    };
}

#endif // _LOG4CPP_STRINGUTIL_HH

