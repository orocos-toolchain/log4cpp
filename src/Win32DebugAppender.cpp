/*
 * FileAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifdef WIN32	// only available on Win32

#include "log4cpp/Portability.hh"
#ifdef LOG4CPP_HAVE_IO_H
#    include <io.h>
#endif
#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#include <windows.h>
#include <winbase.h>

#include <stdio.h>
#include "log4cpp/Category.hh"
#include "log4cpp/Win32DebugAppender.hh"

namespace log4cpp {

    Win32DebugAppender::Win32DebugAppender(const std::string& name) : 
            LayoutAppender(name) {
    }
    
    Win32DebugAppender::~Win32DebugAppender() {
        close();
    }

    void Win32DebugAppender::close() {
    }

    void Win32DebugAppender::_append(const LoggingEvent& event) {
        std::string message(_getLayout().format(event));
		::OutputDebugString(message.c_str());
    }
}

#endif	// WIN32
