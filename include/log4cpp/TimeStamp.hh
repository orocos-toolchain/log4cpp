/*
 * TimeStamp.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_TIMESTAMP_HH
#define _LOG4CPP_TIMESTAMP_HH

#include "log4cpp/Portability.hh"
#include "log4cpp/Export.hh"

namespace log4cpp {

    /**
     * A simple TimeStamp abstraction
     **/
    class LOG4CPP_EXPORT TimeStamp {
        public:
        /**
           Constructs a TimeStamp representing 'now'.
        **/
        TimeStamp();

        /**
           Constructs a TimeStamp representing the given offset since the
           epoch ( 00:00:00 1970/1/1 UTC).
        **/
        TimeStamp(unsigned int seconds, unsigned int microSeconds = 0);

        inline int getSeconds() const {
            return _seconds;
        };

        inline int getMilliSeconds() const {
            return _microSeconds / 1000;
        };

        inline int getMicroSeconds() const {
            return _microSeconds;
        };

        static inline const TimeStamp& getStartTime() {
            return _startStamp;
        };

        protected:
        static TimeStamp _startStamp;

        int _seconds;
        int _microSeconds;
    };
}

#endif // _LOG4CPP_TIMESTAMP_HH

