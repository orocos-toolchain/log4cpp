/*
 * Layout.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_LAYOUT_HH
#define _LOG4CPP_LAYOUT_HH

#include "log4cpp/LoggingEvent.hh"

namespace log4cpp {
    
    class Layout {
        public:
        virtual ~Layout() { };
        virtual char* format(const LoggingEvent& event) = 0;
    };        
}

#endif // _LOG4CPP_LAYOUT_HH
