/*
 * RemoteSyslogAppender.cpp
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Walter Stroebel. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"

#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log4cpp/RemoteSyslogAppender.hh"
#ifdef WIN32
#include <winsock2.h>
#endif

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
	_portNumber (portNumber),
	_socket (0),
	_ipAddr (0),
	_cludge (0)
    {
        open();
    }
    
    RemoteSyslogAppender::~RemoteSyslogAppender() {
        close();
#ifdef WIN32
	if (_cludge) {
	    // we started it, we end it.
	    WSACleanup ();
	}
#endif
    }

    void RemoteSyslogAppender::open() {
	if (!_ipAddr) {
	    struct hostent *pent = gethostbyname (_relayer.c_str ());
	    if (pent == NULL) {
#ifdef WIN32
		if (WSAGetLastError () == WSANOTINITIALISED) {
		    WSADATA wsaData;
		    int err;
 
		    err = WSAStartup (0x101, &wsaData );
		    if (err) abort ();
		    pent = gethostbyname (_relayer.c_str ());
		    _cludge = 1;
		} else {
		    abort ();
		}
#endif
	    }
	    if (pent == NULL) {
		unsigned long ip = (unsigned long) inet_addr (_relayer.c_str ());
		pent = gethostbyaddr ((const char *) &ip, 4, AF_INET);
	    }
	    if (pent == NULL) {
		abort ();
	    }
	    _ipAddr = *((unsigned long *) pent->h_addr);
	}
	// Get a datagram socket.
	
	if ((_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
	    abort ();
	} else {
	    sockaddr_in sain;
	    sain.sin_family = AF_INET;
	    sain.sin_port   = htons (_portNumber);
	    sain.sin_addr.s_addr = htonl (_ipAddr);
	    if (connect (_socket, (struct sockaddr *) &sain, sizeof (sain)) < 0) {
		abort ();
	    }
	}
    }

    void RemoteSyslogAppender::close() {
	if (_socket) {
#if WIN32
	    closesocket (_socket);
#else
	    close (_socket);
#endif
	    _socket = 0;
	}
    }

    void RemoteSyslogAppender::_append(const LoggingEvent& event) {
        if (!_layout) {
            // XXX help! help!
            return;
        }

        const char* message = _layout->format(event).c_str();
	int len = strlen (message) + 16;
	char *buf = new char [len];
        int priority = toSyslogPriority(event.priority);
	sprintf (buf, "<%d>", priority);
	memcpy (buf + strlen (buf), message, len - 16);
	sockaddr_in sain;
	sain.sin_family = AF_INET;
	sain.sin_port   = htons (_portNumber);
        sain.sin_addr.s_addr = htonl (_ipAddr);
	int r = sendto (_socket, buf, (int) len, 0, (struct sockaddr *) &sain, sizeof (sain));
	printf ("sendto: %d\n", r);
	delete buf;
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
