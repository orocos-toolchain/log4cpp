/*
 * OstringStream.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_OSTRINGSTREAM_HH
#define _LOG4CPP_OSTRINGSTREAM_HH

#include "log4cpp/Config.hh"
#include <string>
#include <stdarg.h>

#ifdef LOG4CPP_HAVE_STDIOSTREAM
#    include <sstream>
#else
#    include <strstream>
#endif

namespace log4cpp {

#ifdef LOG4CPP_HAVE_STDIOSTREAM
    class OstringStream : public std::ostringstream
#else
    class OstringStream : public ostrstream
#endif
    {
    public:
#ifndef LOG4CPP_HAVE_STDIOSTREAM
        std::string str();
#endif
	void vform(const char* format, va_list args);
    };    

}

#endif // _LOG4CPP_HINTS_HH
