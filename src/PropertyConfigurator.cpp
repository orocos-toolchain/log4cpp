/*
 * PropertyConfigurator.cpp
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#include <log4cpp/Portability.hh>

#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef LOG4CPP_HAVE_IO_H
#    include <io.h>
#endif
#include <iostream>

#include <string>
#include <fstream>

#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/NDC.hh>
#include <log4cpp/PatternLayout.hh>

#include <log4cpp/PropertyConfigurator.hh>

namespace log4cpp {

    PropertyConfigurator::PropertyConfigurator() {
    }

    PropertyConfigurator::~PropertyConfigurator() {
    }

    void PropertyConfigurator::configure(const std::string& initFileName) throw (ConfigureFailure) {
        std::ifstream initFile(initFileName.c_str());

        if (!initFile) {
            throw ConfigureFailure(std::string("File ") + initFileName + " does not exist");
        }

        // parse the file to get all of the configuration
        parseConfig(initFile);

        // get categories
        std::vector<std::string> catList;
        getCategories(catList);

        // add appenders for each category
        for(std::vector<std::string>::iterator iter = catList.begin();
            iter != catList.end(); ++iter) {
            addAppenders(*iter);
        }
    }

    void PropertyConfigurator::parseConfig(std::ifstream& config) throw (ConfigureFailure) {
        std::string fullLine, command;
        std::string leftSide, rightSide;
        char line[256];
        int length;

        while (config.getline(line, 256)) {
            fullLine = line;

            /* if the line contains a # then it is a comment
               if we find it anywhere other than the beginning, then we assume 
               there is a command on that line, and it we don't find it at all
               we assume there is a command on the line (we test for valid command later)
               if neither is true, we continue with the next line
            */
            length = fullLine.find('#');
            if (length > 0) {
                command = fullLine.substr(0, length);
            } else if (length == std::string::npos) {
                command = fullLine;
            } else {
                continue;
            }

            // check the command and handle it
            length = command.find('=');
            if (length != std::string::npos) {
                leftSide = command.substr(0, length);
                rightSide = command.substr(length + 1, command.size() - length);
            } else {
                continue;
            }

            /* handle the command by determining what object the left side refers to
               and setting the value given on the right
               ASSUMPTIONS:  
               1. first object given  on left side is "log4j" or "log4cpp"
               2. all class names on right side are ignored because we
               probably cannot resolve them anyway.
            */

            // strip off the "log4j" or "log4cpp"
            length = leftSide.find('.');
            if (leftSide.substr(0, length) == "log4j" || leftSide.substr(0, length) == "log4cpp")
                leftSide = leftSide.substr(length + 1);

            // add to the map of properties
            getProperties().insert(PropertiesMap::value_type(leftSide, rightSide));
        };
    }
}
