/*
 * Hints.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_STREAMUTIL_HH
#define _LOG4CPP_STREAMUTIL_HH

#include "log4cpp/Hints.hh"

namespace log4cpp {

    class StreamUtil {
        public:
	static void vform(ostringstream& s, const char* format, va_list args);
    };

}
#endif _LOG4CPP_STREAMUTIL_HH
