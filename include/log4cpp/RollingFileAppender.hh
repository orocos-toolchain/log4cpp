/*
 * RollingFileAppender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Based on FileAppender by Bastiaan Bakker. All rights reserved. 
 * Copyright 2002, Alex Tapacoos. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 *  
 * NOTES ON USE
 * 1. fileNameFormat uses the strftime method and therefor thats methods formatting
 * 2. Log file change will occur on point of logging. This means that time check 
 *    will occur at that point even if time between log entries is greater than that 
 *    specified. Alternative method would be to use a timer but that would involve threads.
 *    
 */



#ifndef _LOG4CPP_ROLLINGFILEAPPENDER_HH
#define _LOG4CPP_ROLLINGFILEAPPENDER_HH

#include <string>
#include <stdarg.h>
#include "log4cpp/Export.hh"
#include "log4cpp/LayoutAppender.hh"
#include <time.h>

namespace log4cpp {

	enum ROLLING_FILE_DURATION {ROLLING_FILE_HOURLY,ROLLING_FILE_DAILY,ROLLING_FILE_WEEKLY,ROLLING_FILE_MONTHLY};
    class LOG4CPP_EXPORT RollingFileAppender : public LayoutAppender {
        public:
        RollingFileAppender(const std::string& name, const std::string& fileNameFormat,ROLLING_FILE_DURATION duration);
        RollingFileAppender(const std::string& name, int fd);
        virtual ~RollingFileAppender();
        
        virtual bool reopen();
        virtual void close();
		static ROLLING_FILE_DURATION getDuration(const std::string& duration);
        protected:
		virtual bool _timeToChange();
		virtual bool _openLog();
		virtual void _generateLogFileName();
        virtual void _append(const LoggingEvent& event);
		virtual void _copyTime(tm* theTime,time_t* theTimeSrc);
        std::string _fileName;
		const std::string _fileNameFormat;
        int _fd;
		time_t _startTime,_endTime;
		double _elapsedTime;
		ROLLING_FILE_DURATION _duration;
    };
}

#endif // _LOG4CPP_ROLLINGFILEAPPENDER_HH
