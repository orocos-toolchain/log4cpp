/*
 * BasicLayout.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_BASICLAYOUT_HH
#define _LOG4CPP_BASICLAYOUT_HH

#include "log4cpp/Layout.hh"

namespace log4cpp {
    
    class BasicLayout : public Layout {
        public:
        BasicLayout();
        virtual ~BasicLayout();
        virtual char* format(const LoggingEvent& event);
    };        
}

#endif // _LOG4CPP_BASICLAYOUT_HH
