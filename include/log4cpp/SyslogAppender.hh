/*
 * SyslogAppender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_SYSLOGAPPENDER_HH
#define _LOG4CPP_SYSLOGAPPENDER_HH

#include <string>
#include <stdarg.h>
#include <syslog.h>
#include "log4cpp/Appender.hh"

namespace log4cpp {

    class SyslogAppender : public Appender {
        public:

        /**
         * Translates a log4cpp priority to a syslog priority
         * @param priority The log4cpp priority.
         * @returns the syslog priority.
         **/
        static int toSyslogPriority(int priority);

        /**
         * Instantiate a SyslogAppender with given name and name and facility
         * for syslog. Note that the C syslog API is process global, so 
         * instantion of a second SyslogAppender will 'overwrite' the 
         * syslog name of the first.
         * @param name The name of the Appender
         * @param syslogName The ident parameter in the openlog(3) call.
         * @param facility The syslog facility to log to. Defaults to LOG_USER.
         **/         
        SyslogAppender(const string& name, const string& syslogName, 
                       int facility = LOG_USER);
        virtual ~SyslogAppender();

        /**
         * Sends a LoggingEvent to syslog.
         * @param event the LoggingEvent to log.
         **/
        virtual void doAppend(const LoggingEvent& event);

        /**
         * Calls closelog(3) and openlog(3).
         **/
        virtual bool reopen();

        /**
         * Calls closelog(3) to close the syslog file descriptor.
         **/
        virtual void close();

        /**
         * The SyslogAppender requires a Layout.
         * @returns true
         **/
        virtual bool requiresLayout() const;

        virtual void setLayout(Layout* layout);

        protected:
        
        /**
         * Calls openlog(3).
         **/
        virtual void open();

        const string _syslogName;
        int _facility;
        Layout* _layout;
    };
}

#endif // _LOG4CPP_SYSLOGAPPENDER_HH
