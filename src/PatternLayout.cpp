/*
 * PatternLayout.cpp
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"

#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <string>

#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#else
#include <strstream>
#endif

#include <iomanip>
//#include <ios>

#include <time.h>
#ifdef LOG4CPP_HAVE_GETTIMEOFDAY
#include <sys/time.h>
#endif

#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/OstringStream.hh"
#include "log4cpp/NDC.hh"


namespace log4cpp {

    PatternLayout::PatternLayout() {
        convPatn = "%m%n";
        millisecondsAtCreation = getMillisecondsTime();
    }
    
    PatternLayout::~PatternLayout() {
    }

    std::string PatternLayout::format(const LoggingEvent& event) {
        bool success;
        return doFormat(event, convPatn, &success);
    }

    bool PatternLayout::setConversionPattern(std::string conversionPattern) {
        LoggingEvent garbageEvent("", "hi", NDC::get(), Priority::INFO);
        bool success;
        doFormat(garbageEvent, conversionPattern, &success);
        if (success)
            convPatn = conversionPattern;
        return success;
    }
    
    std::string PatternLayout::doFormat(const LoggingEvent& event, std::string conversionPattern, bool *success) {
        *success = true;
        
#ifdef LOG4CPP_HAVE_SSTREAM 
        std::istringstream conversionStream(conversionPattern);
#else
        std::istrstream conversionStream(conversionPattern.c_str());
#endif
        
        OstringStream message;
        
        char ch;
        while (conversionStream.get(ch)) {
            switch (ch) {
            case '%':
                {
                    if (!conversionStream.get(ch)) {
                        *success = false;
                        return "";
                    }
                    switch (ch) {
                    case '%':
                        message << '%';
                        break;
                    case 'm':
                        message << event.message;
                        break;
                    case 'n':
                        message << std::endl;
                        break;
                    case 'c':
                        message << event.categoryName;
                        break;
                    case 'd':
                        {
                            struct tm *currentTime;
                            time_t aclock;
                            time(&aclock);
                            currentTime = localtime(&aclock);
                            std::string currentTimeOnOneLine = asctime(currentTime);
                            currentTimeOnOneLine = currentTimeOnOneLine.substr(0, currentTimeOnOneLine.length()-1);
                            
                            message << currentTimeOnOneLine;
                        }
                        break;
                    case 'R':
                        message << event.timeStamp;
                        break;
                    case 'p':
                        {
                            const std::string& priorityName = 
                                Priority::getPriorityName(event.priority);
                            message << priorityName;
                        }
                        break;
                    case 'r':
#ifdef LOG4CPP_HAVE_INT64_T
                        message << millisecondsSinceCreation();
#else
                        message << std::setiosflags(std::ios::fixed) << std::setprecision(0) << millisecondsSinceCreation();
#endif
                        break;
                    case 'u':
                        message << clock();
                        break;
                    case 'x':
                        message << event.ndc;
                        break;
                    default:
                        *success = false;
                        return "";
                        break;
                    }
                };
                break;
            default:
                message << ch;
                break;
            }
        }
        
        return message.str();
        
        std::string convertedMessage;
        return convertedMessage;
    }

    QUITE_LONG PatternLayout::getMillisecondsTime()	{
#ifdef LOG4CPP_HAVE_GETTIMEOFDAY
        struct timeval tv;
        
        gettimeofday(&tv, NULL);
        return (((QUITE_LONG)tv.tv_sec)*1000000.0+(QUITE_LONG)tv.tv_usec)/1000.0;
#else
#ifdef _WIN32
        return GetTickCount();
#else
#error no gettimeofday or GetTickCount available on this platform
#endif
#endif
	}
    QUITE_LONG PatternLayout::millisecondsSinceCreation() {
        return getMillisecondsTime() - millisecondsAtCreation;
    }
}
