/*
 * OstringStream.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include <stdio.h>
#include "log4cpp/OstringStream.hh"

// FIXME: is this useful ??
#if defined(_MSC_VER)
#    include <windows.h>
#endif // _MSC_VER

namespace {

#ifdef __osf__

    int snprintf(char* s, size_t maxlen, const char* fmt, ...)
    {
	int         len;
	va_list	args;

	va_start(args, fmt);
	len = vsnprintf(s, maxlen, fmt, args);
	va_end(args);

	return len;
    }

    int vsnprintf(char* s, size_t maxlen, const char* fmt, va_list args)
    {
	int  len;
	FILE f;

	if (maxlen == 0)
	    return 0;

	memset(&f, 0, sizeof(f));

	f._flag    = _IOWRT + _IOSTRG;

	f._bufsiz  = f._cnt = maxlen - 1;
	f._base    = f._ptr = (unsigned char*) s;
	f._bufendp = f._base + f._bufsiz;

	len = vfprintf(&f, fmt, args);
	*f._ptr = '\0';

	return len;
    }

#endif // __osf__

    std::string strprintf(const char* format, ...)
    {
	va_list     ap;
	int         size   = 1024;
	char*       buffer = new char[size];
            
	while (1) {
	    va_start(ap, format);
	    int n = vsnprintf(buffer, size, format, ap);
	    va_end(ap);
                
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

#ifndef LOG4CPP_HAVE_STDIOSTREAM
    std::string OstringStream::str() {
        (*this) << '\0';
        return std::string(ostrstream::str());
    }
#endif

    void OstringStream::vform(const char* format, va_list args) {
	*this << strprintf(format, args);
    }

}

