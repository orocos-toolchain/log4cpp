/*
 * OstreamAppender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_OSTREAMAPPENDER_HH
#define _LOG4CPP_OSTREAMAPPENDER_HH

#include <string>
#include <iostream>
#include "log4cpp/LayoutAppender.hh"

namespace log4cpp {

    class OstreamAppender : public LayoutAppender {
        public:
        OstreamAppender(const std::string& name, std::ostream* stream);
        virtual ~OstreamAppender();
        
        virtual void doAppend(const LoggingEvent& event);
        virtual bool reopen();
        virtual void close();

        protected:
        std::ostream* _stream;
    };
}

#endif // _LOG4CPP_OSTREAMAPPENDER_HH
