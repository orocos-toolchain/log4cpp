/*
 * PortabilityImpl.hh
 *
 * Copyright 2002, Log4cpp Project. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_PORTABILITYIMPL_HH
#define _LOG4CPP_PORTABILITYIMPL_HH

#include <log4cpp/Portability.hh>

#ifdef LOG4CPP_CSTDLIB_NOT_IN_STD
#include <cstdlib>
namespace std {
    static inline char *getenv(const char *name) { return ::getenv(name); };
    static inline int atoi(const char *nptr) { return ::atoi(nptr); };
    static inline unsigned long int
        strtoul(const char *nptr, char **endptr, int base) { 
        return ::strtol(nptr, endptr, base); 
    };
}
#endif
    
#ifdef LOG4CPP_CSTRING_NOT_IN_STD
#include <cstring>
namespace std {
    static inline void *memmove(void *dest, const void *src, size_t n) {
        return ::memmove(dest, src, n);
    };
}
#endif

#endif // _LOG4CPP_PORTABILITYIMPL_HH
