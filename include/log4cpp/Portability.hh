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

#endif
