/*
 * BoostThreads.hh
 *
 * Copyright 2002, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2002, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_THREADING_BOOSTTHREADS_HH
#define _LOG4CPP_THREADING_BOOSTTHREADS_HH

#include <log4cpp/Portability.hh>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/tss.hpp>
#include <stdio.h>
#include <string>

namespace log4cpp {
    namespace threading {
        static std::string getThreadId() {
            char buffer[16];
            sprintf(buffer, "not implemented");
            return std::string(buffer);
        };
        
        typedef boost::mutex Mutex;
        typedef boost::scoped_lock<Mutex> ScopedLock;

        typedef template<typename T> class boost::thread_specific_ptr
            ThreadLocalDataHolder;
    }
}
#endif
