/*
 * OstreamAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _MSC_VER
#    include <unistd.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log4cpp/OstreamAppender.hh"

namespace log4cpp {

    OstreamAppender::OstreamAppender(const std::string& name, std::ostream* stream) : 
        Appender(name),
        _stream(stream),
        _layout(&_defaultLayout) {
    }
    
    OstreamAppender::~OstreamAppender() {
        close();
    }

    void OstreamAppender::close() {
        // empty
    }

    void OstreamAppender::doAppend(const LoggingEvent& event) {
        (*_stream) << _layout->format(event);
        if (!_stream->good()) {
            // XXX help! help!
        }
    }

    bool OstreamAppender::reopen() {
        return true;
    }      

    bool OstreamAppender::requiresLayout() const {
        return true;
    }

    void OstreamAppender::setLayout(Layout* layout) {
        _layout = (layout == NULL) ? &_defaultLayout : layout;
    }

}
