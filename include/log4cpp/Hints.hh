/*
 * Hints.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_HINTS_HH
#define _LOG4CPP_HINTS_HH

#ifdef __GNUC__

#    if (__GNUC__ < 2) || (__GNUC__ == 2 && __GNUC_MINOR__ <= 95)
#        include <strstream>
#        define LOG4CPP_USE_OLD_IOSTREAM 1
#    else
#        include <sstream>
#        define LOG4CPP_USE_NEW_IOSTREAM 1
#    endif

#elif __DECCXX

#    if (defined (__STD_STRICT_ANSI) || defined (__STD_STRICT_ANSI_ERRORS))
#        include <sstream>
#	 define LOG4CPP_USE_NEW_IOSTREAM 1
#    else
#        include <strstream>
#        define LOG4CPP_USE_OLD_IOSTREAM 1
#    endif

#elif defined(_MSC_VER)

#    pragma warning( disable : 4786 )
#    include <strstream>
     using namespace std;
#    define LOG4CPP_USE_OLD_IOSTREAM 1
#    undef LOG4CPP_USE_NEW_IOSTREAM

#else

#    error "Unknown Compiler !!"

#endif


namespace log4cpp {

#ifdef LOG4CPP_USE_NEW_IOSTREAM

    class ostrstream: public std::ostringstream 
    {
    public:
	char*	str();
	void	vform(const char* format, va_list args);
    };

#endif // LOG4CPP_USE_NEW_IOSTREAM

}
#endif // _LOG4CPP_HINTS_HH
