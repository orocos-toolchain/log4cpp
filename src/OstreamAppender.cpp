/*
 * OstreamAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log4cpp/OstreamAppender.hh"

namespace log4cpp {

    OstreamAppender::OstreamAppender(const string& name, ostream* stream) : 
        Appender(name),
        _stream(stream) {
    }
    
    OstreamAppender::~OstreamAppender() {
        close();
    }

    void OstreamAppender::close() {
        // empty
    }

    void OstreamAppender::doAppend(const LoggingEvent& event) {
        if (!_layout) {
            // XXX help! help!
            return;
        }

        char* message = _layout->format(event);
        (*_stream) << message;
        if (!_stream->good()) {
            // XXX help! help!
        }

        free(message);
    }

    bool OstreamAppender::reopen() {
        return true;
    }      

    bool OstreamAppender::requiresLayout() const {
        return true;
    }

    void OstreamAppender::setLayout(Layout* layout) {
        _layout = layout;
    }

}
