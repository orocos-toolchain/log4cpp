/*
 * AppenderSkeleton.cpp
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/AppenderSkeleton.hh"

namespace log4cpp {

    AppenderSkeleton::AppenderSkeleton(const std::string& name) :
        Appender(name),
        _treshold(Priority::NOTSET),
        _filter(NULL) {
    }
    
    AppenderSkeleton::~AppenderSkeleton() {
        if (_filter)
            delete _filter;
    }
    
    bool AppenderSkeleton::reopen() {
        return true;
    }

    void AppenderSkeleton::doAppend(const LoggingEvent& event) {
        if ((Priority::NOTSET == _treshold) || (event.priority >= _treshold)) {
            if (!_filter || (_filter->decide(event) != Filter::DENY)) { 
                _append(event);
            }
        }
    }

    void AppenderSkeleton::setTreshold(Priority::Value priority) {
        _treshold = priority;
    }

    Priority::Value AppenderSkeleton::getTreshold() {
        return _treshold;
    }

    void AppenderSkeleton::setFilter(Filter* filter) {
        if (_filter != filter) {
            if (_filter)
                delete _filter;

            _filter = filter;
        }
    }

    Filter* AppenderSkeleton::getFilter() {
        return _filter;
    }

}
