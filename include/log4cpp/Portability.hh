/*
 * Portability.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_PORTABILITY_HH
#define _LOG4CPP_PORTABILITY_HH

#if defined (_MSC_VER) || defined(__BORLANDC__)
#    include <log4cpp/config-win32.h>
#else
#if defined(__OPENVMS__)
#    include <log4cpp/config-openvms.h>
#else
#    include <log4cpp/config.h>
#endif
#endif

#if defined(_MSC_VER)
#    pragma warning( disable : 4786 )
#endif

#ifndef LOG4CPP_HAVE_STRCASECMP
#ifdef LOG4CPP_HAVE_STRICMP

#include <string.h>
namespace log4cpp {
    inline int strcasecmp(const char *s1, const char *s2) {
	return stricmp(s1, s2);
    };
}

#else
#error no strcasecmp alternative for this platform implemented yet
#endif // LOG4CPP_HAVE_STRICMP
#endif // LOG4CPP_HAVE_STRCASECMP

#endif
