/*
 * SyslogAppender.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Walter Stroebel. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_REMOTESYSLOGAPPENDER_HH
#define _LOG4CPP_REMOTESYSLOGAPPENDER_HH

#include <string>
#include <stdarg.h>
#include "log4cpp/Export.hh"
#include "log4cpp/LayoutAppender.hh"
#include "log4cpp/AppenderSkeleton.hh"
#include "log4cpp/Priority.hh"

#ifdef LOG4CPP_HAVE_SYSLOG
#include <syslog.h>
#else
/// from syslog.h
typedef enum {
    LOG_EMERG   = 0,       ///< system is unusable
    LOG_ALERT   = 1,       ///< action must be taken immediately
    LOG_CRIT    = 2,       ///< critical conditions 
    LOG_ERR     = 3,       ///< error conditions
    LOG_WARNING = 4,       ///< warning conditions
    LOG_NOTICE  = 5,       ///< normal but significant condition
    LOG_INFO    = 6,       ///< informational
    LOG_DEBUG   = 7,       ///< debug-level messages
    LOG_USER    = (1<<3)     ///< random user-level messages
} SyslogLevel;
#endif

namespace log4cpp {

    /**
     * RemoteSyslogAppender sends LoggingEvents to a remote syslog system.
     *
     * Also see: draft-ietf-syslog-syslog-12.txt
     **/
    class LOG4CPP_EXPORT RemoteSyslogAppender : public AppenderSkeleton {
        public:

        /**
         * Translates a log4cpp priority to a syslog priority
         * @param priority The log4cpp priority.
         * @returns the syslog priority.
         **/
        static int toSyslogPriority(Priority::Value priority);

        /**
         * Instantiate a RemoteSyslogAppender with given name and name and
         * facility for syslog.
         * @param name The name of the Appender
         * @param syslogName The ident parameter in the openlog(3) call.
         * @param relayer The IP address or hostname of a standard syslog host.
         * @param facility The syslog facility to log to. Defaults to LOG_USER.
         * @param portNumber An alternative port number. Defaults to the 
         * standard syslog port number (514).
         **/         
        RemoteSyslogAppender(const std::string& name, 
                             const std::string& syslogName, 
                             const std::string& relayer, 
                             int facility = LOG_USER,
                             int portNumber = 514);
        virtual ~RemoteSyslogAppender();

        /**
         * Closes and reopens the socket.
         **/
        virtual bool reopen();

        /**
         * Closes the socket
         **/
        virtual void close();

        /**
         * The RemoteSyslogAppender requires a Layout.
         * @returns true
         **/
        virtual bool requiresLayout() const;

        virtual void setLayout(Layout* layout);

        protected:
        
        /**
         * Just creates the socket.
         **/
        virtual void open();

        /**
         * Sends a LoggingEvent to the remote syslog.
         * @param event the LoggingEvent to log.
         **/
        virtual void _append(const LoggingEvent& event);

        const std::string _syslogName;
        const std::string _relayer;
        int _facility;
        int _portNumber;
        int _socket;
        unsigned long _ipAddr;
        Layout* _layout;
        private:
        int _cludge;
    };
}

#endif // _LOG4CPP_REMOTESYSLOGAPPENDER_HH
