/*
 * CategoryStream.cpp
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"

#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#include "log4cpp/CategoryStream.hh"
#include "log4cpp/Category.hh"

namespace log4cpp {

    CategoryStream::CategoryStream(Category& category, Priority::Value priority) :
        _category(category),
        _priority(priority),
        _buffer(NULL) {
    }

    CategoryStream::~CategoryStream() { 
        flush();
    }

    CategoryStream& CategoryStream::operator<<(CategoryStream::Separator separator) {
        flush();
        return *this;
    }

    void CategoryStream::flush() {
        if (_buffer) {
            getCategory().log(getPriority(), _buffer->str());
            delete _buffer;
            _buffer = NULL;
        }
    }
}
