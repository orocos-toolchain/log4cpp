/*
 * OstringStream.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"
#include <stdio.h>
#include "log4cpp/OstringStream.hh"

#if defined(_MSC_VER)
    #define VSNPRINTF _vsnprintf
#else
#ifdef LOG4CPP_HAVE_SNPRINTF
    #define VSNPRINTF vsnprintf
#else
/* use alternative snprintf() from http://www.ijs.si/software/snprintf/ */

#define HAVE_SNPRINTF
#define PREFER_PORTABLE_SNPRINTF

#include <stdlib.h>
#include <stdarg.h>

extern "C" {
#include "snprintf.c"
}

#define VSNPRINTF portable_vsnprintf

#endif // LOG4CPP_HAVE_SNPRINTF
#endif // _MSC_VER

namespace {

    std::string vstrprintf(const char* format, va_list args)
    {
	int         size   = 1024;
	char*       buffer = new char[size];
            
	while (1) {
	    int n = VSNPRINTF(buffer, size, format, args);
                
	    // If that worked, return a string.
	    if (n > -1 && n < size) {
		std::string s(buffer);
		delete [] buffer;
		return s;
	    }
                
	    // Else try again with more space.
	    if (n > -1)     size  = n+1;    // ISO/IEC 9899:1999
	    else            size *= 2;      // twice the old size
                
	    delete [] buffer;
	    buffer = new char[size];
	}
    }

}

namespace log4cpp {

#ifndef LOG4CPP_HAVE_SSTREAM
    std::string OstringStream::str() { 
        (*this) << '\0'; 
        std::string msg(ostrstream::str()); 
        ostrstream::freeze(false); //unfreeze stream 
        return msg; 
        
    } 
#endif

    void OstringStream::vform(const char* format, va_list args) {
	*this << vstrprintf(format, args);
    }

}

