/*
 * SimpleLayout.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_SIMPLELAYOUT_HH
#define _LOG4CPP_SIMPLELAYOUT_HH

#include "log4cpp/Export.hh"
#include "log4cpp/Layout.hh"

namespace log4cpp {
    
    class LOG4CPP_EXPORT SimpleLayout : public Layout {
        public:
        SimpleLayout();
        virtual ~SimpleLayout();
        virtual std::string format(const LoggingEvent& event);
    };        
}

#endif // _LOG4CPP_SIMPLELAYOUT_HH
