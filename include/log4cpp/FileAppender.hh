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
#include "log4cpp/Export.hh"
#include "log4cpp/LayoutAppender.hh"

namespace log4cpp {

    class LOG4CPP_EXPORT FileAppender : public LayoutAppender {
        public:
        FileAppender(const std::string& name, const std::string& fileName);
        FileAppender(const std::string& name, int fd);
        virtual ~FileAppender();
        
        virtual bool reopen();
        virtual void close();

        protected:
        virtual void _append(const LoggingEvent& event);

        const std::string _fileName;
        int _fd;
    };
}

#endif // _LOG4CPP_FILEAPPENDER_HH
