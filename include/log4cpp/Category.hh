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
#include <strstream>
#include <map>
#include <set>
#include <stdarg.h>
#include "log4cpp/Appender.hh"
#include "log4cpp/HierarchyMaintainer.hh"
#include "log4cpp/LoggingEvent.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {
/**
 * This is the central class in the log4j package. One of the distintive
 * features of log4j (and hence log4cpp) are hierarchal categories and 
 * their evaluation.
 **/

    class Category;

    class CategoryStream {
        public:
        CategoryStream(Category& category, int priority) :
            _category(category),
            _priority(priority) {
        }
        
        ~CategoryStream() { };
        
        inline Category& getCategory() const { return _category; };
        inline int getPriority() const { return _priority; };
        
        private:
        Category& _category;
        int _priority;    

        public:
        template<class T> CategoryStream& operator<<(/*CategoryStream& stream,*/ 
                                                     const T& t) {
        if (getPriority() != Priority::NOTSET) {
            ostrstream buffer;
            buffer << t << '\0';
            getCategory().log(getPriority(), 
                              string(buffer.str()));
        }
        return *this;
        };
    };

    class Category {
        friend class HierarchyMaintainer;

        public:
        
        /**
         * Return the root of the Category hierarchy.
         * 
         * <p>The root category is always instantiated and available. It's
         * name is the empty string.
           
         * <p>Unlike in log4j, calling <code>Category.getInstance("")</code>
         * <em>does</em> retrieve the root category 
         * and not a category just under root named "".
         * @returns The root category
         **/
        static Category& getRoot();

        /** 
         * Set the priority of the root Category.
         * @param priority The new priority for the root Category 
         **/
        static void setRootPriority(int priority);

        /** 
         * Get the priority of the <code>root</code> Category.
         * @returns the priority of the root category
         **/
        static int getRootPriority();

        /**
         * Instantiate a Category with name <code>name</code>. This
         * method does not set priority of the category which is by
         * default <code>Priority::NOTSET</code>.
         * 
         * @param name The name of the category to retrieve.
         **/
        static Category& getInstance(const string& name);

        /**
         * Returns all the currently defined categories as a set of
         * Category pointers. Note: this function does not pass ownership
         * of the categories in the set to the caller, only the ownership
         * of the set. However set<Category&>* is not legal C++, so we can't
         * follow the default ownership conventions.
         *
         * <p>Unlike in log4j, the root category <em>is</em> included 
         * in the returned set.
         **/
        static set<Category*>* getCurrentCategories();
 
        virtual ~Category();
        
        /**
         * Return the category name.
         * @returns The category name.
        */       
        inline const string& getName() const { return _name; };
        
        /**
         * Set the priority of this Category.
         * @param priority The priority to set. Use Priority::NOTSET to let 
         * the category use its parents priority as effective priority.
         **/
        void setPriority(int priority);

        /**
         * Returns the assigned Priority, if any, for this Category.
         * @return Priority - the assigned Priority, can be Priority::NOTSET
         **/
        int getPriority() const;

        /**
         * Starting from this Category, search the category hierarchy for a
         * set priority and return it. Otherwise, return the priority 
         *  of the root category.
         * 
         * <p>The Category class is designed so that this method executes as
         * quickly as possible.
         **/
        int getChainedPriority() const;

        /** 
         * Returns true if the Category has set a priority.
         * @returns whether a priority has been set.
         **/
        bool isPriorityEnabled(int priority) const;
        
        /**
         * Sets an Appender for this Category.
         * This method passes ownership from the caller to the Category.
         * @param appender The Appender this category has to log to.
         **/
        void setAppender(Appender* appender);

        /**
         * Sets an Appender for this Category.
         * This method does not pass ownership from the caller to the Category.
         * @param appender The Appender this category has to log to.
         **/
        void setAppender(Appender& appender);

        /**
         * Returns the Appender for this Category, or NULL if no Appender has
         * been set.
         * @returns The Appender.
         **/
        Appender* getAppender() const;

        /**
         * Returns true if the Category owns the Appender. In that case the
         * Category destructor will delete the Appender.
         **/
        bool ownsAppender() const;

        /**
         * Call the appenders in the hierrachy starting at
         *  <code>this</code>.  If no appenders could be found, emit a
         * warning.
         * 
         * <p>This method always calls all the appenders inherited form the
         * hierracy circumventing any evaluation of whether to log or not to
         * log the particular log request.
         * 
         * @param LoggingEvent the event to log.
         **/
        void callAppenders(const LoggingEvent& event);
        
        /**
         * Set the additivity flag for this Category instance.
         **/
        void setAdditivity(bool additivity);

        /**
         * Returns the additivity flag for this Category instance.
         **/        
        inline bool getAdditivity() const { return _isAdditive; };

        /** 
         * Log a message with the specified priority.
         * @param priority The priority of this log message.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void log(int priority, const char* stringFormat, ...);

        /** 
         * Log a message with the specified priority.
         * @param priority The priority of this log message.
         * @param message string to write in the log file
         **/  
        void log(int priority, const string& message);
        
        /** 
         * Log a message with debug priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void debug(const char* stringFormat, ...);

        /** 
         * Log a message with debug priority.
         * @param message string to write in the log file
         **/  
        void debug(const string& message);
        inline bool isDebugEnabled() const { 
            return isPriorityEnabled(Priority::DEBUG); 
        };

        inline CategoryStream debugStream() {
            return getStream(Priority::DEBUG);
        }

        /** 
         * Log a message with info priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void info(const char* stringFormat, ...);

        /** 
         * Log a message with info priority.
         * @param message string to write in the log file
         **/  
        void info(const string& message);
        inline bool isInfoEnabled() const { 
            return isPriorityEnabled(Priority::INFO); 
        };

        inline CategoryStream infoStream() {
            return getStream(Priority::INFO);
        }
        
        /** 
         * Log a message with warn priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void warn(const char* stringFormat, ...);

        /** 
         * Log a message with warn priority.
         * @param message string to write in the log file
         **/  
        void warn(const string& message);
        inline bool isWarnEnabled() const { 
            return isPriorityEnabled(Priority::WARN); 
        };

        inline CategoryStream warnStream() {
            return getStream(Priority::WARN);
        }
        
        /** 
         * Log a message with error priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void error(const char* stringFormat, ...);

        /** 
         * Log a message with error priority.
         * @param message string to write in the log file
         **/  
        void error(const string& message);
        inline bool isErrorEnabled() const { 
            return isPriorityEnabled(Priority::ERROR); 
        };
        
        inline CategoryStream errorStream() {
            return getStream(Priority::ERROR);
        }

        CategoryStream getStream(int priority);

        CategoryStream operator<<(int priority);

        protected:

        /**
         * Returns the parent category of this category, or NULL
         * if the category is the root category.
         * @return the parent category.
         **/
        inline Category* getParent() { return _parent; };

        /**
         * Returns the parent category of this category, or NULL
         * if the category is the root category.
         * @return the parent category.
         **/
        inline const Category* getParent() const { return _parent; };

        void _logUnconditionally(int priority, const char* format, 
                                va_list arguments);
        
        /** 
         * Unconditionally log a message with the specified priority.
         * @param priority The priority of this log message.
         * @param message string to write in the log file
         **/  
        void _logUnconditionally2(int priority, const string& message);


        private:
        Category(const string& name, Category* parent, int priority = Priority::NOTSET);
        
        /** The name of this category. */
        const string _name;

        /**
         * The parent of this category. All categories have al least one
         * ancestor which is the root category. 
         **/
        Category* _parent;

        /**
         *  The assigned priority of this category. 
         **/
        int _priority;

        /**
         * The appender of this category. Unlike log4j, log4cpp does not
         * support multiple appenders per category, yet.
         * The value of this variable may be <code>null</code>. 
         **/
        Appender* _appender;


        /**
         * Whether the category holds the ownership of the appender. If so,
         * it deletes the appender in its destructor.
         **/
        bool _ownsAppender;

        /** 
         * Additivity is set to true by default, i.e. a child inherits its
         * ancestor's appenders by default. 
         */
        bool _isAdditive;

    };


}
#endif // _LOG4CPP_CATEGORY_HH
