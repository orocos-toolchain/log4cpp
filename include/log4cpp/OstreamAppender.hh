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
#include "log4cpp/Appender.hh"

namespace log4cpp {

    class OstreamAppender : public Appender {
        public:
        OstreamAppender(const string& name, ostream* stream);
        virtual ~OstreamAppender();
        
        virtual void doAppend(const LoggingEvent& event);
        virtual bool reopen();
        virtual void close();
        virtual bool requiresLayout() const;
        virtual void setLayout(Layout* layout);

        protected:
        ostream* _stream;
        Layout* _layout;
    };
}

#endif // _LOG4CPP_OSTREAMAPPENDER_HH
