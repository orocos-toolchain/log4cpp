/*
 * FileAppender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_FILEAPPENDER_HH
#define _LOG4CPP_FILEAPPENDER_HH

#include <string>
#include <stdarg.h>
#include "log4cpp/Appender.hh"

namespace log4cpp {

    class FileAppender : public Appender {
        public:
        FileAppender(const string& name, const string& fileName);
        FileAppender(const string& name, int fd);
        virtual ~FileAppender();
        
        virtual void doAppend(const LoggingEvent& event);
        virtual bool reopen();
        virtual void close();
        virtual bool requiresLayout() const;
        virtual void setLayout(Layout* layout);

        protected:
        const string _fileName;
        int _fd;
        Layout* _layout;
    };
}

#endif // _LOG4CPP_FILEAPPENDER_HH
