/*
 * Category.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_CATEGORY_HH
#define _LOG4CPP_CATEGORY_HH

#include "log4cpp/OstringStream.hh"
#include <map>
#include <set>
#include <stdarg.h>
#include "log4cpp/Appender.hh"
#include "log4cpp/LoggingEvent.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    class Category;

    /**
     * This class enables streaming simple types and objects to a category.
     * Use category.errorStream(), etc. to obtain a CategoryStream class.
     **/
    class CategoryStream {
        public:

        /**
         * Enumeration of special 'Separators'. Currently only contains the
         * 'ENDLINE' separator, which separates two log messages.
         **/
        typedef enum {
            ENDLINE
        } Separator;

        /**
         * Construct a CategoryStream for given Category with given priority.
         * @param category The category this stream will send log messages to.
         * @param priority The priority the log messages will get or 
         * Priority::NOTSET to silently discard any streamed in messages.
         **/
        CategoryStream(Category& category, Priority::Value priority);

        /**
         * Destructor for CategoryStream
         **/
        ~CategoryStream();
        
        /**
         * Returns the destination Category for this stream.
         * @returns The Category.
         **/
        inline Category& getCategory() const { return _category; };

        /**
         * Returns the priority for this stream.
         * @returns The priority.
         **/
        inline Priority::Value getPriority() const { return _priority; };

        /**
         * Streams in a Separator. If the separator equals 
         * CategoryStream::ENDLINE it sends the contents of the stream buffer
         * to the Category with set priority and empties the buffer.
         * @param Separator The Separator
         * @returns A reference to itself.
         **/
        CategoryStream& operator<<(Separator separator);

        /**
         * Flush the contents of the stream buffer to the Category and
         * empties the buffer.
         **/
        void flush();

        /**
         * Stream in arbitrary types and objects.  
         * @param t The value or object to stream in.
         * @returns A reference to itself.
         **/
        template<typename T> CategoryStream& operator<<(const T& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_buffer) {
                    if (!(_buffer = new OstringStream)) {
                        // XXX help help help
                    }
                }
                (*_buffer) << t;
            }
            return *this;
        }
        
        private:
        Category& _category;
        Priority::Value _priority;
        OstringStream* _buffer;
    };

    /**
     * This is the central class in the log4j package. One of the distintive
     * features of log4j (and hence log4cpp) are hierarchal categories and 
     * their evaluation.
     **/   
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
        static void setRootPriority(Priority::Value priority);

        /** 
         * Get the priority of the <code>root</code> Category.
         * @returns the priority of the root category
         **/
        static Priority::Value getRootPriority();

        /**
         * Instantiate a Category with name <code>name</code>. This
         * method does not set priority of the category which is by
         * default <code>Priority::NOTSET</code>.
         * 
         * @param name The name of the category to retrieve.
         **/
        static Category& getInstance(const std::string& name);

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
        static std::set<Category*>* getCurrentCategories();

        /**
         * This method will remove all Appenders from Categories.XXX
         **/
        static void shutdown();

        /**
         * Destructor for Category.
         **/
        virtual ~Category();
        
        /**
         * Return the category name.
         * @returns The category name.
        */       
        inline const std::string& getName() const { return _name; };
        
        /**
         * Set the priority of this Category.
         * @param priority The priority to set. Use Priority::NOTSET to let 
         * the category use its parents priority as effective priority.
         **/
        virtual void setPriority(Priority::Value priority);

        /**
         * Returns the assigned Priority, if any, for this Category.
         * @return Priority - the assigned Priority, can be Priority::NOTSET
         **/
        virtual Priority::Value getPriority() const;

        /**
         * Starting from this Category, search the category hierarchy for a
         * set priority and return it. Otherwise, return the priority 
         *  of the root category.
         * 
         * <p>The Category class is designed so that this method executes as
         * quickly as possible.
         **/
        virtual Priority::Value getChainedPriority() const;

        /** 
         * Returns true if the chained priority of the Category is equal to
         * or higher than given priority.
         * @param priority The priority to compare with.
         * @returns whether logging is enable for this priority.
         **/
        virtual bool isPriorityEnabled(Priority::Value priority) const;
        
        /**
         * Sets an Appender for this Category.
         * This method passes ownership from the caller to the Category.
         * @param appender The Appender this category has to log to.
         **/
        virtual void setAppender(Appender* appender);

        /**
         * Sets an Appender for this Category.
         * This method does not pass ownership from the caller to the Category.
         * @param appender The Appender this category has to log to.
         **/
        virtual void setAppender(Appender& appender);

        /**
         * Returns the Appender for this Category, or NULL if no Appender has
         * been set.
         * @returns The Appender.
         **/
        virtual Appender* getAppender() const;

        /**
         * Removes all appenders set for this Category. Currently a Category
         * can have only one appender, but this may change in the future.
         **/
        virtual void removeAllAppenders();

        /**
         * Returns true if the Category owns the Appender. In that case the
         * Category destructor will delete the Appender.
         **/
        virtual bool ownsAppender() const;

        /**
         * Call the appenders in the hierarchy starting at
         *  <code>this</code>.  If no appenders could be found, emit a
         * warning.
         * 
         * <p>This method always calls all the appenders inherited form the
         * hierracy circumventing any evaluation of whether to log or not to
         * log the particular log request.
         * 
         * @param LoggingEvent the event to log.
         **/
        virtual void callAppenders(const LoggingEvent& event);
        
        /**
         * Set the additivity flag for this Category instance.
         **/
        virtual void setAdditivity(bool additivity);

        /**
         * Returns the additivity flag for this Category instance.
         **/        
        virtual bool getAdditivity() const;

        /**
         * Returns the parent category of this category, or NULL
         * if the category is the root category.
         * @return the parent category.
         **/
        virtual Category* getParent();

        /**
         * Returns the parent category of this category, or NULL
         * if the category is the root category.
         * @return the parent category.
         **/
        virtual const Category* getParent() const;

        /** 
         * Log a message with the specified priority.
         * @param priority The priority of this log message.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        virtual void log(Priority::Value priority, const char* stringFormat,
                         ...);

        /** 
         * Log a message with the specified priority.
         * @param priority The priority of this log message.
         * @param message string to write in the log file
         **/  
        virtual void log(Priority::Value priority, const std::string& message);
        
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
        void debug(const std::string& message);

        /**
         * Return true if the Category will log messages with priority DEBUG.
         * @returns Whether the Category will log.
         **/ 
        inline bool isDebugEnabled() const { 
            return isPriorityEnabled(Priority::DEBUG); 
        };

        /**
         * Return a CategoryStream with priority DEBUG.
         * @returns The CategoryStream.
         **/
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
        void info(const std::string& message);

        /**
         * Return true if the Category will log messages with priority INFO.
         * @returns Whether the Category will log.
         **/ 
        inline bool isInfoEnabled() const { 
            return isPriorityEnabled(Priority::INFO); 
        };

        /**
         * Return a CategoryStream with priority INFO.
         * @returns The CategoryStream.
         **/
        inline CategoryStream infoStream() {
            return getStream(Priority::INFO);
        }
        
        /** 
         * Log a message with notice priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void notice(const char* stringFormat, ...);

        /** 
         * Log a message with notice priority.
         * @param message string to write in the log file
         **/  
        void notice(const std::string& message);

        /**
         * Return true if the Category will log messages with priority NOTICE.
         * @returns Whether the Category will log.
         **/ 
        inline bool isNoticeEnabled() const { 
            return isPriorityEnabled(Priority::NOTICE); 
        };

        /**
         * Return a CategoryStream with priority NOTICE.
         * @returns The CategoryStream.
         **/
        inline CategoryStream noticeStream() {
            return getStream(Priority::NOTICE);
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
        void warn(const std::string& message);

        /**
         * Return true if the Category will log messages with priority WARN.
         * @returns Whether the Category will log.
         **/ 
        inline bool isWarnEnabled() const { 
            return isPriorityEnabled(Priority::WARN); 
        };

        /**
         * Return a CategoryStream with priority WARN.
         * @returns The CategoryStream.
         **/
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
        void error(const std::string& message);

        /**
         * Return true if the Category will log messages with priority ERROR.
         * @returns Whether the Category will log.
         **/ 
        inline bool isErrorEnabled() const { 
            return isPriorityEnabled(Priority::ERROR); 
        };
        
        /**
         * Return a CategoryStream with priority ERROR.
         * @returns The CategoryStream.
         **/
        inline CategoryStream errorStream() {
            return getStream(Priority::ERROR);
        }

        /** 
         * Log a message with crit priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void crit(const char* stringFormat, ...);

        /** 
         * Log a message with crit priority.
         * @param message string to write in the log file
         **/  
        void crit(const std::string& message);

        /**
         * Return true if the Category will log messages with priority CRIT.
         * @returns Whether the Category will log.
         **/ 
        inline bool isCritEnabled() const { 
            return isPriorityEnabled(Priority::CRIT); 
        };
        
        /**
         * Return a CategoryStream with priority CRIT.
         * @returns The CategoryStream.
         **/
        inline CategoryStream critStream() {
            return getStream(Priority::CRIT);
        }

        /** 
         * Log a message with alert priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void alert(const char* stringFormat, ...);

        /** 
         * Log a message with alert priority.
         * @param message string to write in the log file
         **/  
        void alert(const std::string& message);

        /**
         * Return true if the Category will log messages with priority ALERT.
         * @returns Whether the Category will log.
         **/ 
        inline bool isAlertEnabled() const { 
            return isPriorityEnabled(Priority::ALERT); 
        };
        
        /**
         * Return a CategoryStream with priority ALERT.
         * @returns The CategoryStream.
         **/
        inline CategoryStream alertStream() {
            return getStream(Priority::ALERT);
        }

        /** 
         * Log a message with emerg priority.
         * @param stringFormat Format specifier for the string to write 
         * in the log file.
         * @param ... The arguments for stringFormat 
         **/  
        void emerg(const char* stringFormat, ...);

        /** 
         * Log a message with emerg priority.
         * @param message string to write in the log file
         **/  
        void emerg(const std::string& message);

        /**
         * Return true if the Category will log messages with priority EMERG.
         * @returns Whether the Category will log.
         **/ 
        inline bool isEmergEnabled() const { 
            return isPriorityEnabled(Priority::EMERG); 
        };
        
        /**
         * Return a CategoryStream with priority EMERG.
         * @returns The CategoryStream.
         **/
        inline CategoryStream emergStream() {
            return getStream(Priority::EMERG);
        }

        /**
         * Return a CategoryStream with given Priority.
         * @param priority The Priority of the CategoryStream.
         * @returns The requested CategoryStream.
         **/
        virtual CategoryStream getStream(Priority::Value priority);

        /**
         * Return a CategoryStream with given Priority.
         * @param priority The Priority of the CategoryStream.
         * @returns The requested CategoryStream.
         **/
        virtual CategoryStream operator<<(Priority::Value priority);

        protected:

        /**
         * Constructor 
         * @param name the fully qualified name of this Category
         * @param parent the parent of this parent, or NULL for the root 
         * Category
         * @param priority the priority for this Category. Defaults to
         * Priority::NOTSET
         **/
        Category(const std::string& name, Category* parent, 
                 Priority::Value priority = Priority::NOTSET);
        
        virtual void _logUnconditionally(Priority::Value priority, 
                                         const char* format, 
                                         va_list arguments);
        
        /** 
         * Unconditionally log a message with the specified priority.
         * @param priority The priority of this log message.
         * @param message string to write in the log file
         **/  
        virtual void _logUnconditionally2(Priority::Value priority, 
                                          const std::string& message);

        private:

        /** The name of this category. */
        const std::string _name;

        /**
         * The parent of this category. All categories have al least one
         * ancestor which is the root category. 
         **/
        Category* _parent;

        /**
         *  The assigned priority of this category. 
         **/
        Priority::Value _priority;

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
