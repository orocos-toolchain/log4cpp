/*
 * Log4cppConfigurator.cpp
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#include "log4cpp/Portability.hh"

#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <iostream>

#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#else
#error not backported yet
#endif
#include <string>
#include <fstream>

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"
#ifdef HAVE_PATTERN_LAYOUT
#include "log4cpp/PatternLayout.hh"
#endif

#include "log4cpp/SimpleConfigurator.hh"

namespace log4cpp {

    ConfigureFailure::ConfigureFailure(const std::string& reason) :
        std::runtime_error(reason) {
    }

    void SimpleConfigurator::configure(const std::string& initFileName) throw ConfigureFailure {
        std::ifstream initFile(initFileName);

        if (!initFile) {
            throw ConfigureFailure(std::string("File ") + initFileName + " does not exist");
        }

        std::string nextCommand;
        std::string categoryName;

        while (initFile >> nextCommand >> categoryName) {
            log4cpp::Category& category = 
                (categoryName.compare("root") == 0) ? 
                log4cpp::Category::getRoot() : 
                log4cpp::Category::getInstance(categoryName);

            if (nextCommand.compare("appender") == 0) {
                std::string layout;
                std::string appenderName;

                if (initFile >> layout >> appenderName) {
                    log4cpp::Appender* appender;
                    if (appenderName.compare("file") == 0) {
                    std::string logFileName;
                    if (!(initFile >> logFileName)) {
                        throw ConfigureFailure("Missing filename for log file logging configuration file for category: " + categoryName);
                    }
                    appender = new log4cpp::FileAppender(std::string("default"), logFileName);
                }
                else if (appenderName.compare("console") == 0) {
                    appender = 
                        new log4cpp::OstreamAppender("default", &std::cout);
                } else {
                    throw ConfigureFailure("Invalid appender name (" + 
                                           appenderName + 
                                           ") in logging configuration file for category: " + 
                                           categoryName);
                }
                if (layout.compare("basic") == 0)
                    appender->setLayout(new log4cpp::BasicLayout());
                else if (layout.compare("simple") == 0)
                    appender->setLayout(new log4cpp::SimpleLayout());
#ifdef HAVE_PATTERN_LAYOUT
                else if (layout.compare("pattern") == 0) {
                    log4cpp::PatternLayout *layout = 
                        new log4cpp::PatternLayout();
                    char pattern[1000];
                    initFile.getline(pattern, 1000);
                    layout->setConversionPattern(std::string(pattern));
                    appender->setLayout(layout);
                }
#endif
                else {
                    throw ConfigureFailure("Invalid layout (" + layout + 
                        ") in logging configuration file for category: " + 
                        categoryName);
                }
                category.setAppender(appender);
            }
        }
        else if (nextCommand.compare("priority") == 0) {
            std::string priority;
            if (!(initFile >> priority)) {
                throw ConfigureFailure("Missing priority in logging configuration file for category: " + categoryName);
            }
            if (priority.compare("info") == 0) {
                category.setPriority(log4cpp::Priority::INFO);
            }
            else if (priority.compare("debug") == 0) {
                category.setPriority(log4cpp::Priority::DEBUG);
            }
            else if (priority.compare("warn") == 0) {
                category.setPriority(log4cpp::Priority::WARN);
            }
            else if (priority.compare("error") == 0) {
                category.setPriority(log4cpp::Priority::ERROR);
            }
	    else if (priority.compare("fatal") == 0) {
                category.setPriority(log4cpp::Priority::FATAL);
            }
            else {
                throw ConfigureFailure("Invalid priority ("+priority+") in logging configuration file for category: "+categoryName);
            }
        }
        else if (nextCommand.compare("category") == 0) {
            // This command means we should "refer" to the category (in order to have it
            // created).
            // We've already done this in common setup code for all commands.
        }
        else {
            throw ConfigureFailure("Invalid format in logging configuration file. Command: " + nextCommand);
        }
    }
}
