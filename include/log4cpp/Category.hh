/*
 * Category.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_CATEGORY_HH
#define _LOG4CPP_CATEGORY_HH

#include <string>
#include <map>
#include <set>
#include <stdarg.h>
#include "log4cpp/Appender.hh"
#include "log4cpp/HierarchyMaintainer.hh"
#include "log4cpp/LoggingEvent.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    class Category {
        friend class HierarchyMaintainer;

        public:
        
        static Category& getRoot();
        static void setRootPriority(int priority);
        static int getRootPriority();
        static Category& getInstance(const string& name);
        static const set<Category*>* getCurrentCategories();
 
        virtual ~Category();
        
        inline const string& getName() const { return _name; };
        
        void setPriority(int priority);
        int getPriority() const;
        int getChainedPriority() const;
        bool isPriorityEnabled(int priority) const;
        
        void setAppender(Appender* appender);
        void setAppender(Appender& appender);
        Appender* getAppender() const;
        bool ownsAppender() const;
        void callAppenders(const LoggingEvent& event);

        void setAdditivity(bool additivity);
        inline bool getAdditivity() const { return _isAdditive; };

        void logUnconditionally(int priority, const char* format, 
                                va_list arguments);
        void logUnconditionally2(int priority, const string& message);

        void log(int priority, const char* stringFormat, ...);
        void log(int priority, const string& message);
        
        void debug(const char* stringFormat, ...);
        void debug(const string& message);
        inline bool isDebugEnabled() const { 
            return isPriorityEnabled(Priority::DEBUG); 
        };
        
        void info(const char* stringFormat, ...);
        void info(const string& message);
        inline bool isInfoEnabled() const { 
            return isPriorityEnabled(Priority::INFO); 
        };
        
        void warn(const char* stringFormat, ...);
        void warn(const string& message);
        inline bool isWarnEnabled() const { 
            return isPriorityEnabled(Priority::WARN); 
        };
        
        void error(const char* stringFormat, ...);
        void error(const string& message);
        inline bool isErrorEnabled() const { 
            return isPriorityEnabled(Priority::ERROR); 
        };
        
        protected:
        inline Category* getParent() { return _parent; };
        inline const Category* getParent() const { return _parent; };

        private:
        Category(const string& name, Category* parent, int priority = Priority::INFO);
        
        const string _name;
        Category* _parent;
        int _priority;
        Appender* _appender;
        bool _ownsAppender;
        bool _isAdditive;
    };    
}

#endif // _LOG4CPP_CATEGORY_HH
