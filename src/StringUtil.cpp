/*
 * StringUtil.cpp
 *
 * Copyright 2002, Log4cpp Project. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#include "StringUtil.hh"
#include <iterator>

namespace log4cpp {

    std::string StringUtil::trim(const std::string& s) {
        // test for null string
        if(s.empty())
            return s;

        // find first non-space character
        std::string::size_type b = s.find_first_not_of(" \t");
        if(b == std::string::npos) // No non-spaces
            return "";

        // find last non-space character
        std::string::size_type e = s.find_last_not_of(" \t");

        // return the remaining characters
        return std::string(s, b, e - b + 1);
    }

    void StringUtil::split(std::vector<std::string>& v, const std::string& s,
                           char delimiter, unsigned int maxSegments) {
        v.clear();
        std::back_insert_iterator<std::vector<std::string> > it(v);
        split(it, s, delimiter, maxSegments);
    }

}
