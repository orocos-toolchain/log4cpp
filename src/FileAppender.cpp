/*
 * FileAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Hints.hh"

#ifdef _MSC_VER
#    include <io.h>
#else
#    include <unistd.h>
#endif // _MSC_VER

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
            Appender(name),
            _fileName(fileName) {
        _fd = ::open(_fileName.c_str(), O_CREAT | O_APPEND | O_WRONLY, 00644);
    }
    
    FileAppender::FileAppender(const std::string& name, int fd) :
        Appender(name),
        _fileName(""),
        _fd(fd) {
    }
    
    FileAppender::~FileAppender() {
        close();
    }

    void FileAppender::close() {
        ::close(_fd);
    }

    void FileAppender::doAppend(const LoggingEvent& event) {
        if (!_layout) {
            // XXX help! help!
            return;
        }

        char* message = _layout->format(event);
        if (!::write(_fd, message, strlen(message))) {
            // XXX help! help!
        }

        free(message);
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

    bool FileAppender::requiresLayout() const {
        return true;
    }

    void FileAppender::setLayout(Layout* layout) {
        _layout = layout;
    }

}
