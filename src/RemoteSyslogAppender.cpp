/*
 * RemoteSyslogAppender.cpp
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Walter Stroebel. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"
#include "log4cpp/OstringStream.hh"

#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log4cpp/RemoteSyslogAppender.hh"

namespace log4cpp {

    int RemoteSyslogAppender::toSyslogPriority(Priority::Value priority) {
        static int priorities[8] = { LOG_EMERG, LOG_ALERT, LOG_CRIT, LOG_ERR,
                                     LOG_WARNING, LOG_NOTICE, LOG_INFO, 
                                     LOG_DEBUG };
        int result;

        priority++;
        priority /= 100;

        if (priority < 0) {
            result = LOG_EMERG;
        } else if (priority > 7) {
            result = LOG_DEBUG;
        } else {
            result = priorities[priority];
        }

        return result;
    }
        

    RemoteSyslogAppender::RemoteSyslogAppender(const std::string& name, 
                                   const std::string& syslogName, 
				   const std::string& relayer,
                                   int facility,
				   int portNumber) : 
        AppenderSkeleton(name),
        _syslogName(syslogName),
	_relayer(relayer),
        _facility(facility),
	_portNumber (portNumber)
	_socket (0);
    {
        open();
    }
    
    RemoteSyslogAppender::~RemoteSyslogAppender() {
        close();
    }

    void RemoteSyslogAppender::open() {
    }

    void RemoteSyslogAppender::close() {
    }

    void RemoteSyslogAppender::_append(const LoggingEvent& event) {
        if (!_layout) {
            // XXX help! help!
            return;
        }

        const char* message = _layout->format(event).c_str();
        int priority = toSyslogPriority(event.priority);
    }

    bool RemoteSyslogAppender::reopen() {
        close();
        open();
        return true;
    }      

    bool RemoteSyslogAppender::requiresLayout() const {
        return true;
    }

    void RemoteSyslogAppender::setLayout(Layout* layout) {
        _layout = layout;
    }

}
