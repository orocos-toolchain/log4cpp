/*
 * RollingFileAppender.cpp
 *
 * Based on FileAppender by Bastiaan Bakker. All rights reserved. 
 * Copyright 2002, Alex Tapacoos. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "log4cpp/Portability.hh"
#include "log4cpp/OstringStream.hh"
#ifdef LOG4CPP_HAVE_IO_H
#    include <io.h>
#endif
#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/Category.hh"

namespace log4cpp {

	RollingFileAppender::RollingFileAppender(const std::string& name, const std::string& fileNameFormat,ROLLING_FILE_DURATION duration):
		LayoutAppender(name),_fileNameFormat(fileNameFormat),_duration(duration){
		time(&_startTime);
		time(&_endTime);
		_elapsedTime=0;

		_openLog();
        //_fd = ::open(_fileName.c_str(), O_CREAT | O_APPEND | O_WRONLY, 00644);
    }
    
    RollingFileAppender::RollingFileAppender(const std::string& name, int fd) :
	LayoutAppender(name),
        _fileName(""),
        _fd(fd) {
		time(&_startTime);
		time(&_endTime);
		_elapsedTime=0;

    }
    
    RollingFileAppender::~RollingFileAppender() {
        close();
    }

    bool RollingFileAppender::_openLog() {
		time(&_startTime);
		time(&_endTime);
		_generateLogFileName();
        _fd = ::open(_fileName.c_str(), O_CREAT | O_APPEND | O_WRONLY, 00644);
		if (_fd!=-1) return true;
			return false;
    }

    void RollingFileAppender::close() {
        ::close(_fd);
    }

    void RollingFileAppender::_append(const LoggingEvent& event) {
		if (_timeToChange())
		{
			reopen();
		}

        std::string message(_getLayout().format(event));
        if (!::write(_fd, message.data(), message.length())) {
            // XXX help! help!
        }
    }

    bool RollingFileAppender::reopen() {

		if (_timeToChange())
		{
			_startTime=_endTime;
			_generateLogFileName();
		}

        if (_fileName != "") {
            int fd = ::open(_fileName.c_str(), O_CREAT | O_APPEND | O_WRONLY, 00644);
            if (fd < 0)
                return false;
            else {
                int oldfd = _fd;
                _fd = fd;
                ::close(oldfd);
                return true;
            }
        } else {
            return true;
        }      
    }

	bool RollingFileAppender::_timeToChange(){
		time(&_endTime);
		tm tempStartTime;
		tm tempEndTime;
		_copyTime(&tempStartTime,&_startTime);
		_copyTime(&tempEndTime,&_endTime);

		//printf(" \n\n\n%s%s\n\n\n",asctime(&tempEndTime));

		switch (_duration)
		{
			case ROLLING_FILE_HOURLY:
				if (tempStartTime.tm_hour!=tempEndTime.tm_hour)
					return true;
			break;
			case ROLLING_FILE_DAILY:
				if (tempStartTime.tm_mday!=tempEndTime.tm_mday)
					return true;

			break;
			case ROLLING_FILE_WEEKLY:
				if (tempEndTime.tm_yday-tempStartTime.tm_yday>6)
					return true;
			break;
			case ROLLING_FILE_MONTHLY:
				if (tempStartTime.tm_mon!=tempEndTime.tm_mon)
					return true;
			break;

		}
		return false;
	}

	void RollingFileAppender::_generateLogFileName(){
		const size_t stringLength=255;
		char temp[stringLength];
		tm tempStartTime;
		_copyTime(&tempStartTime,&_startTime);
		strftime(temp,stringLength,_fileNameFormat.c_str(),&tempStartTime);
		_fileName=temp;
	}

	ROLLING_FILE_DURATION RollingFileAppender::getDuration(const std::string& duration){
		if (strcasecmp(duration.c_str(),"HOURLY")==0)
			return ROLLING_FILE_HOURLY;
		if (strcasecmp(duration.c_str(),"DAILY")==0)
			return ROLLING_FILE_DAILY;
		if (strcasecmp(duration.c_str(),"WEEKLY")==0)
			return ROLLING_FILE_WEEKLY;
		if (strcasecmp(duration.c_str(),"MONTHLY")==0)
			return ROLLING_FILE_MONTHLY;
		return ROLLING_FILE_DAILY; //default is daily
	}

	void RollingFileAppender::_copyTime(tm* theTime,time_t* theTimeSrc){
		struct tm* tempTm=localtime(theTimeSrc);
		theTime->tm_sec=(*tempTm).tm_sec;
		theTime->tm_min=(*tempTm).tm_min;
		theTime->tm_hour=(*tempTm).tm_hour;
		theTime->tm_mday=(*tempTm).tm_mday;
		theTime->tm_mon=(*tempTm).tm_mon;
		theTime->tm_year=(*tempTm).tm_year;
		theTime->tm_wday=(*tempTm).tm_wday;
		theTime->tm_yday=(*tempTm).tm_yday;
		theTime->tm_isdst=(*tempTm).tm_isdst;
	}

}
