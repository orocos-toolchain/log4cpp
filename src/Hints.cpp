/*
 * Hints.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Hints.hh"

#ifdef __osf__
#include <stdarg.h>
#include <stddef.h>

extern int snprintf(char*, size_t, const char*, ...);
extern int vsnprintf(char*, size_t, const char*, va_list);

#else
#    include <stdio.h>
#endif

namespace log4cpp {

#ifdef LOG4CPP_USE_NEW_IOSTREAM

    char* ostrstream::str() { 
	return strdup(std::ostringstream::str().c_str()); 
    }


    void ostrstream::vform(const char* format, va_list args) {
	char buffer[512];
	int  err = vsnprintf(buffer, sizeof(buffer), format, args);
	
	*this << (err == -1 ? "message too long" : buffer);
    }

#endif // LOG4CPP_USE_NEW_IOSTREAM

}


#ifdef __osf__

extern int snprintf(char* s, size_t maxlen, const char* fmt, ...)
{
    int         len;
    va_list	args;

    va_start(args, fmt);
    len = vsnprintf(s, maxlen, fmt, args);
    va_end(args);

    return len;
}

extern int vsnprintf(char* s, size_t maxlen, const char* fmt, va_list args)
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
