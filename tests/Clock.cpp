static const char rcsid[] = "$Id$";

/* 
 * See the COPYING file for the terms of usage and distribution.
 */

#include <sys/time.h>	// struct timeval

#include "Clock.hh"

const usec_t UsecPerSec = INT64_CONSTANT(1000000);

// -----------------------------------------------------------------------------
usec_t Clock::time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    return (usec_t) (tv.tv_sec * UsecPerSec + tv.tv_usec);
}

// -----------------------------------------------------------------------------
Clock::Clock(void)
    : _start(0),
      _elapsed(0),
      _active(true) 
{
    start();
}

// -----------------------------------------------------------------------------
Clock::~Clock(void)
{
    ;
}

// -----------------------------------------------------------------------------
usec_t Clock::start(void)
{
    _active = true;

    return (_start = time());
}

// -----------------------------------------------------------------------------
usec_t Clock::elapsed(void)
{
    if (!active())
	return _elapsed;

    return (_elapsed = time() - _start);
}

// -----------------------------------------------------------------------------
usec_t Clock::stop(void)
{
    elapsed();

    _active = false;

    return _elapsed;
}
