/*
 * Hints.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Hints.hh"

#if defined(_MSC_VER)
#    include <windows.h>
#endif // _MSC_VER

namespace log4cpp {

#ifndef LOG4CPP_HAVE_STDIOSTREAM
    std::string ostringstream::str() {
        (*this) << '\0';
        return std::string(ostrstream::str());
    }
#endif

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
