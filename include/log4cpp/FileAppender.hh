/*
 * FileAppender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_FILEAPPENDER_HH
#define _LOG4CPP_FILEAPPENDER_HH

#include <string>
#include <stdarg.h>
#include "log4cpp/Appender.hh"

namespace log4cpp {

    class FileAppender : public Appender {
        public:
        FileAppender(const std::string& name, const std::string& fileName);
        FileAppender(const std::string& name, int fd);
        virtual ~FileAppender();
        
        virtual void doAppend(const LoggingEvent& event);
        virtual bool reopen();
        virtual void close();
        virtual bool requiresLayout() const;
        virtual void setLayout(Layout* layout);

        protected:
        const std::string _fileName;
        int _fd;
        Layout* _layout;
    };
}

#endif // _LOG4CPP_FILEAPPENDER_HH
