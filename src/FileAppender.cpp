/*
 * FileAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"
#include "log4cpp/OstringStream.hh"
#ifdef LOG4CPP_HAVE_IO_H
#    include <io.h>
#endif
#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Category.hh"

namespace log4cpp {

    FileAppender::FileAppender(const std::string& name, 
                               const std::string& fileName) : 
            LayoutAppender(name),
            _fileName(fileName) {
        _fd = ::open(_fileName.c_str(), O_CREAT | O_APPEND | O_WRONLY, 00644);
    }
    
    FileAppender::FileAppender(const std::string& name, int fd) :
        LayoutAppender(name),
        _fileName(""),
        _fd(fd) {
    }
    
    FileAppender::~FileAppender() {
        close();
    }

    void FileAppender::close() {
        ::close(_fd);
    }

    void FileAppender::_append(const LoggingEvent& event) {
        std::string message(_getLayout().format(event));
        if (!::write(_fd, message.data(), message.length())) {
            // XXX help! help!
        }
    }

    bool FileAppender::reopen() {
        if (_fileName != "") {
            int fd = ::open(_fileName.c_str(), O_CREAT | O_APPEND | O_WRONLY, 00644);
            if (fd < 0)
                return false;
            else {
                int oldfd = _fd;
                _fd = fd;
                ::close(oldfd);
                return true;
            }
        } else {
            return true;
        }      
    }
}
