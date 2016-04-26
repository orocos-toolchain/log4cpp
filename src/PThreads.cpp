/*
 * Copyright 2002, Log4cpp Project. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include <log4cpp/threading/Threading.hh>

#if defined(LOG4CPP_HAVE_THREADING) && defined(LOG4CPP_USE_PTHREADS)

namespace log4cpp {
    namespace threading {

        char* getThreadId(char* buffer) {
            ::sprintf(buffer, "%lu", (long int)pthread_self());
            return buffer;
        }

        std::string getThreadId() {
            char buffer[16];
            ::sprintf(buffer, "%lu", pthread_self());	// thread id unsigned
            return std::string(buffer);     
        }

    }
}

#endif // LOG4CPP_HAVE_THREADING && LOG4CPP_USE_PTHREADS
