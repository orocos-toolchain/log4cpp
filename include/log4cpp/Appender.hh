/*
 * Appender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_APPENDER_HH
#define _LOG4CPP_APPENDER_HH

#include "log4cpp/Hints.hh"
#include <string>
#include <map>
#include <stdarg.h>
#include "log4cpp/Layout.hh"
#include "log4cpp/LoggingEvent.hh"

namespace log4cpp {
    class Category;

    /**
     *  Implement this interface for your own strategies for printing log
     *  statements. 
     **/
    class Appender {
        public:

        /**
         * Get a pointer to an exitsing Appender.
         * @param name The name of the Appender to return.
         * @returns a pointer to an existing Appender, or NULL if no appender
         * with the specfied name exists.
         **/
        static Appender* getAppender(const std::string& name);

        /**
         * Call reopen() on all existing Appenders.
         * @returns true if all Appenders returned true on their reopen() call.
         **/
        static bool reopenAll();

        protected:
        /**
         * Constructor for Appender. Will only be used in getAppender() (and 
         * in derived classes of course).
         * @param name The name of this Appender.
         **/
        Appender(const std::string& name);

        public:
        /**
         * Destructor for Appender.
         **/
        virtual ~Appender();
        
        /**
         * Log in Appender specific way. 
         * @param event  The LoggingEvent to log. 
         **/
        virtual void doAppend(const LoggingEvent& event) = 0;

        /**
         * Reopens the output destination of this Appender, e.g. the logfile 
         * or TCP socket.
         * @returns false if an error occured during reopening, true otherwise.
         **/
        virtual bool reopen();

        /**
         * Release any resources allocated within the appender such as file
         * handles, network connections, etc.
         **/
        virtual void close() = 0;

        /**
         * Check if the appender uses a layout.
         * 
         * <p>If the appender implementation admits a layout but can also
         *  work without it, then it should return <code>true</code>.
         **/
        virtual bool requiresLayout() const = 0;

        /**
         * Set the Layout for this appender.
         * @param layout The layout to use.
         **/
        virtual void setLayout(Layout* layout) = 0;

        /**
         * Get the name of this appender. The name identifies the appender.
         * @returns the name of the appender.
         **/
        inline const std::string& getName() const { return _name; };
        
        
        private:
        typedef std::map<std::string, Appender*> AppenderMap;

        static AppenderMap _allAppenders;
        static void _addAppender(Appender* appender);
        static void _removeAppender(Appender* appender);
        
        const std::string _name;
    };
}

#endif // _LOG4CPP_APPENDER_HH
