/*
 * DummyThreads.hh
 *
 * Copyright 2002, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2002, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_THREADING_DUMMYTHREADS_HH
#define _LOG4CPP_THREADING_DUMMYTHREADS_HH

#include <log4cpp/Portability.hh>
#include <stdio.h>
#include <string>

namespace log4cpp {
    namespace threading {
        std::string getThreadId();
	    /**
         * Return an identifier for the current thread. What these
         * identifiers look like is completely up to the underlying
         * thread library. OmniThreads returns the POSIX thread Id.
		 *
		 * @param buffer Character buffer of at least 16 in size
		 * @return buffer
		 */
	    char* getThreadId(char* buffer);

        /**
           Dummy type 'int' for Mutex. Yes, this adds a bit of overhead in
           the for of extra memory, but unfortunately 'void' is illegal.
        **/
        typedef int Mutex;

        /**
           Dummy type 'int' defintion of ScopedLock;
        **/
        typedef int ScopedLock;

        template<typename T> class ThreadLocalDataHolder {
            public:
            typedef T data_type;

            inline ThreadLocalDataHolder() {};
            inline ~ThreadLocalDataHolder() {
                if (_data) 
                    delete _data;
            };
            
            inline T* get() const {
                return _data;
            };

            inline T* operator->() const { return get(); };
            inline T& operator*() const { return *get(); };

            inline T* release() {
                T* result = _data;
                _data = NULL;

                return result;
            };

            inline void reset(T* p = NULL) {
                if (_data) 
                    delete _data;
                _data = p;
            };

            private:            
            T* _data;            
        };
    }
}
#endif
