/*
 * StreamUtil.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/StreamUtil.hh"

#ifdef __osf__
#include <stddef.h>

extern int snprintf(char*, size_t, const char*, ...);
extern int vsnprintf(char*, size_t, const char*, va_list);

#else
#    include <stdio.h>
#endif // __osf__

namespace log4cpp {

    void StreamUtil::vform(ostringstream& s,const char* format, va_list args) {
#ifdef HAVE_STRSTREAM_VFORM
        s.vform(format, args);
#else
	// FIXME: max message size is 512
	char buffer[512];
	int  err = vsnprintf(buffer, sizeof(buffer), format, args);
	
	s << (err == -1 ? "message too long" : buffer);
#endif // HAVE_STRSTREAM_VFORM     
    }

}
