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
#include <time.h>

#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#else
#include <strstream>
#endif

#include <iomanip>
//#include <ios>


#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/OstringStream.hh"
#include "log4cpp/NDC.hh"
#include "log4cpp/TimeStamp.hh"

#ifdef LOG4CPP_MISSING_INT64_OSTREAM_OP
/* workaround suggested at:
   http://support.microsoft.com/default.aspx?scid=kb;EN-US;q168440
*/

#include <stdio.h>

std::ostream& operator<<(std::ostream& os, int64_t i) {
    char buf[20];
    ::sprintf(buf,"%I64d", i);
    return os << buf;
}
#endif

namespace log4cpp {

    PatternLayout::PatternLayout() {
        convPatn = "%m%n";
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
                            time_t t = event.timeStamp.getSeconds();
                            currentTime = localtime(&t);
                            std::string currentTimeOnOneLine = asctime(currentTime);
                            currentTimeOnOneLine = currentTimeOnOneLine.substr(0, currentTimeOnOneLine.length()-1);
                            
                            message << currentTimeOnOneLine;
                        }
                        break;
                    case 'R':
                        message << event.timeStamp.getSeconds();
                        break;
                    case 'p':
                        {
                            const std::string& priorityName = 
                                Priority::getPriorityName(event.priority);
                            message << priorityName;
                        }
                        break;
                    case 'r':
                        {
#ifdef LOG4CPP_HAVE_INT64_T
                            int64_t t = event.timeStamp.getSeconds() -
                                TimeStamp::getStartTime().getSeconds();
                            t *= 1000;
                            t += event.timeStamp.getMilliSeconds() -
                                TimeStamp::getStartTime().getMilliSeconds();
                            
                            message << t;
#else
                            double t = event.timeStamp.getSeconds() -
                                TimeStamp::getStartTime().getSeconds();
                            t *= 1000;
                            t += event.timeStamp.getMilliSeconds() -
                                TimeStamp::getStartTime().getMilliSeconds();
                            
                            message << std::setiosflags(std::ios::fixed) << std::setprecision(0) << t;
#endif
                        }
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
    }
}
