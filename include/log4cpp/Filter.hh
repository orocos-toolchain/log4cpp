/*
 * Filter.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_FILTER_HH
#define _LOG4CPP_FILTER_HH

#include "log4cpp/LoggingEvent.hh"

namespace log4cpp {

    class Filter {
        public:
        
        typedef enum { DENY = -1,
                       NEUTRAL = 0,
                       ACCEPT = 1
        } Decision;

        Filter();
        virtual ~Filter();

        virtual void setChainedFilter(Filter* filter);
        virtual Filter* getChainedFilter();
        virtual Filter* getEndOfChain();
        virtual void appendChainedFilter(Filter* filter);

        virtual Decision decide(const LoggingEvent& event) = 0;

        protected:
        virtual Decision _decide(const LoggingEvent& event) = 0;

        private:
        Filter* _chainedFilter;

    }; 

}

#endif // _LOG4CPP_FILTER_HH
