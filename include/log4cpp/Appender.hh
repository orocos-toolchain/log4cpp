/*
 * Appender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_APPENDER_HH
#define _LOG4CPP_APPENDER_HH

#include <string>
#include <map>
#include <stdarg.h>
#include "log4cpp/Layout.hh"
#include "log4cpp/LoggingEvent.hh"

namespace log4cpp {
    class Category;

    class Appender {
        public:
        typedef map<string, Appender*> AppenderMap;
        
        // statics
        static Appender* getAppender(const string& name);
        static bool reopenAll();

        // constructors
        Appender(const string& name);
        virtual ~Appender();
        
        // methods
        virtual void doAppend(const LoggingEvent& event) = 0;
        virtual bool reopen();
        virtual void close() = 0;
        virtual bool requiresLayout() const = 0;
        virtual void setLayout(Layout* layout) = 0;
        inline const string& getName() const { return _name; };
        
        
        private:
        static AppenderMap _allAppenders;
        static void _addAppender(Appender* appender);
        static void _removeAppender(Appender* appender);
        
        const string _name;
    };
}

#endif // _LOG4CPP_APPENDER_HH
