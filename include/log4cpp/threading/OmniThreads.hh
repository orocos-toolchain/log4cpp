/*
 * Category.hh
 *
 * Copyright 2002, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2002, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_THREADING_OMNITHREADS_HH
#define _LOG4CPP_THREADING_OMNITHREADS_HH

#include <log4cpp/Portability.hh>
#include <omnithread.h>
#include <stdio.h>
#include <string>

namespace log4cpp {
    namespace threading {
        std::string getThreadId() {
            char buffer[16];
            sprintf(buffer, "%d", ::omni_thread::self()->id());
            return std::string(buffer);
        };
        
        typedef omni_mutex Mutex;
        typedef omni_mutex_lock ScopedLock;

        template<typename T> class ThreadLocalDataHolder {
            public:
            typedef T data_type;

            inline ThreadLocalDataHolder() :
                _key(omni_thread::allocate_key()) {};

            inline ~ThreadLocalDataHolder() {};
            
            inline T* get() const {
                Holder* holder = dynamic_cast<Holder*>(
                    ::omni_thread::self()->get_value(_key));
                return (holder) ? holder->data : NULL;
            };

            inline T* operator->() const { return get(); };
            inline T& operator*() const { return *get(); };

            inline T* release() {
                T* result = NULL;
                Holder* holder = dynamic_cast<Holder*>(
                    ::omni_thread::self()->get_value(_key));
              
                if (holder) {
                    result = holder->data;
                    holder->data = NULL;
                }

                return result;
            };

            inline void reset(T* p = NULL) {
                Holder* holder = dynamic_cast<Holder*>(
                    ::omni_thread::self()->get_value(_key));
                if (holder) {
                    if (holder->data)
                        delete holder->data;

                    holder->data = p;
                } else {
                    holder = new Holder(p);
                    ::omni_thread::self()->set_value(_key, holder);
                }
            };

            private:            
            class Holder : public omni_thread::value_t {
                public:
                Holder(data_type* data) : data(data) {};
                virtual ~Holder() { if (data) delete (data); };
                data_type* data;
                private:
                Holder(const Holder& other);
                Holder& operator=(const Holder& other);
            };

            omni_thread::key_t _key;            
        };
    }
}
#endif
