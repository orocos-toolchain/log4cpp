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

#include <string>
#include <stdarg.h>
#include "log4cpp/Export.hh"
#include "log4cpp/Portability.hh"

#ifdef LOG4CPP_HAVE_SSTREAM
#    include <sstream>
#else
#    include <strstream>
#endif

namespace log4cpp {

    /**
     * OstringStream is a portability class used to work around the 
     * unavailability of std::ostringstream on some platforms (most notably
     * g++ < 2.95.3). It also provides a vform() method.
     **/
#ifdef LOG4CPP_HAVE_SSTREAM
    class LOG4CPP_EXPORT OstringStream : public std::ostringstream
#else
    class LOG4CPP_EXPORT OstringStream : public std::ostrstream
#endif
    {
    public:
#ifndef LOG4CPP_HAVE_SSTREAM
        std::string str();
#endif
        /**
         * appends a string to the stream, built from a format specifier
         * and a va_list of arguments, analogously to vprintf(3).
         * @param format the format specifier.
         * @param args the va_list of arguments.
         **/
	void vform(const char* format, va_list args);
    };    

}

#endif // _LOG4CPP_HINTS_HH
