/*
 * ConfiguratorSkeleton.cpp
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#include <log4cpp/Portability.hh>

#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <string>
#include <iostream>
#include <fstream>

#include <log4cpp/Category.hh>

// appenders
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Win32DebugAppender.hh>
#include <log4cpp/RemoteSyslogAppender.hh>
#ifdef LOG4CPP_HAVE_LIBIDSA
#include <log4cpp/IdsaAppender.hh>
#endif	// LOG4CPP_HAVE_LIBIDSA

// layout
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/PatternLayout.hh>

#include <log4cpp/Priority.hh>
#include <log4cpp/NDC.hh>

#include <log4cpp/ConfiguratorSkeleton.hh>

#include <list>
#include <vector>

namespace log4cpp {

    // allocate map
    PropertiesMap ConfiguratorSkeleton::_properties;

    ConfiguratorSkeleton::ConfiguratorSkeleton() {
    }

    ConfiguratorSkeleton::~ConfiguratorSkeleton() {
    }

    void ConfiguratorSkeleton::addAppenders(std::string& categoryName) throw (ConfigureFailure) {
        std::string::size_type length;
        std::string tempCatName;
        std::string leftString, rightString, priority;
        std::list<std::string> tokens;
        Category* category;

        // start by reading the "rootCategory" key
        tempCatName = 
            (categoryName == "rootCategory") ? categoryName : "category." + categoryName;

        PropertiesMap::iterator iter = _properties.find(tempCatName);

        if (iter == _properties.end())
            throw ConfigureFailure(std::string("Unable to find category: ") + tempCatName);

        // need to get the root instance of the category
        category = (categoryName == "rootCategory") ?
            &Category::getRoot() : &Category::getInstance(categoryName);

        // if string is not ", appender.." or "" then we only want to set priority ???
        length = (*iter).second.find(",");

        if (length == std::string::npos)
            // something seriously wrong, so bail
            throw ConfigureFailure(std::string("Invalid configuration file: see ") + tempCatName);

        rightString = (*iter).second;
        // store all of the tokens
        do {
            leftString = rightString.substr(0, length);
            rightString = rightString.substr(length + 1);
            tokens.push_back(leftString);
            length = rightString.find(",");
        } while (length != std::string::npos);

        // need to save the last token
        if (rightString.size() > 0)
            tokens.push_back(rightString);

        // made it this far, so we should delete what we have already
        category->removeAllAppenders();

        // loop through the list and either set the priority or add the appender
        for(std::list<std::string>::const_iterator list_iter = tokens.begin();
            list_iter != tokens.end(); list_iter++) {
            std::string name = trim(*list_iter);

            try {
                category->setPriority(Priority::getPriorityValue(name));
            } catch(std::invalid_argument& e) {
                // not a priority, so it must be an appender
                configAppender(name, *category);
            }
        }
    }

    void ConfiguratorSkeleton::configAppender(std::string& name, Category& category) {
        // we're given the appender name, so get the property associated with it
        PropertiesMap::iterator key = _properties.find(std::string("appender.") + name);

        if (key == _properties.end()) {
            // XXX bb: shouldn't we complain?
        } else {
            // instantiate the appender
            Appender* appender = instantiateAppender(name);
			
            // and set it to the category
            category.addAppender(appender);
        }
    }

    Appender* ConfiguratorSkeleton::instantiateAppender(const std::string& appenderName) {
        Appender* appender = NULL;

        // determine the type by the appenderName 
        PropertiesMap::iterator key = _properties.find(std::string("appender.") + appenderName);
        if (key == _properties.end())
            throw ConfigureFailure(std::string("Appender '") + appenderName + "' not defined");
		
        std::string::size_type length = (*key).second.find_last_of(".");
        std::string appenderType = (length == std::string::npos) ?
            (*key).second : (*key).second.substr(length+1);

        // and instantiate the appropriate object
        if (appenderType == "ConsoleAppender") {
            appender = new OstreamAppender(appenderName, &std::cout);
        }
        else if (appenderType == "FileAppender") {
            key = _properties.find(std::string("appender.") + appenderName + ".fileName");
            std::string fileName = (key == _properties.end()) ? "foobar" : (*key).second;

            appender = new FileAppender(appenderName, fileName);
        }
        else if (appenderType == "SyslogAppender") {
             // get syslog name, i.e. "ident"
            key = _properties.find(std::string("appender.") + appenderName + ".syslogName");
            std::string syslogName = (key == _properties.end()) ? "syslog" : (*key).second;

            // get syslog host
            key = _properties.find(std::string("appender.") + appenderName + ".syslogHost");
            std::string syslogHost = (key == _properties.end()) ? "localhost" : (*key).second;

            // get facility
            key = _properties.find(std::string("appender.") + appenderName + ".facility");
            int facility = (key == _properties.end()) ? -1 : atoi((*key).second.c_str());

            // get port number
            key = _properties.find(std::string("appender.") + appenderName + ".port");
            int portNumber = (key == _properties.end()) ? -1 : atoi((*key).second.c_str());

            appender = new RemoteSyslogAppender(appenderName, syslogName, 
                                                syslogHost, facility, portNumber);
        }
#ifdef LOG4CPP_HAVE_LIBIDSA
        else if (appenderType == "IdsaAppender") {
            key = _properties.find(std::string("appender.") + appenderName + ".idsaName");
            // default idsa name ???
            std::string idsaName = (key == _properties.end()) ? "foobar" : (*key).second;

            appender = new IdsaAppender(appenderName, idsaname);
        }
#endif	// LOG4CPP_HAVE_LIBIDSA

#ifdef WIN32
        // win32 debug appender
        else if (appenderType == "Win32DebugAppender") {
            appender = new Win32DebugAppender(appenderName);
        }
#endif	// WIN32
        else {
            throw ConfigureFailure(std::string("Appender '") + appenderName + 
                                   "' has unknown type '" + appenderType + "'");
        }

        if (appender->requiresLayout()) {
            setLayout(appender, appenderName);
        }

        return appender;
    }

    void ConfiguratorSkeleton::setLayout(Appender* appender, const std::string& appenderName) {
        // determine the type by appenderName
        std::string tempString;
        PropertiesMap::iterator key = 
            _properties.find(std::string("appender.") + appenderName + ".layout");

        if (key == _properties.end())
            throw ConfigureFailure(std::string("Missing layout property for appender '") + 
                                   appenderName + "'");
		
        std::string::size_type length = (*key).second.find_last_of(".");
        std::string layoutType = (length == std::string::npos) ? 
            (*key).second : (*key).second.substr(length+1);
 
        Layout* layout;
        // and instantiate the appropriate object
        if (layoutType == "BasicLayout") {
            layout = new BasicLayout();
        }
        else if (layoutType == "SimpleLayout") {
            layout = new SimpleLayout();
        }
        else if (layoutType == "PatternLayout") {
            // need to read the properties to configure this one
            PatternLayout* patternLayout = new PatternLayout();

            key = _properties.find(std::string("appender.") + appenderName + ".layout.ConversionPattern");
            if (key == _properties.end()) {
                // leave default pattern
            } else {
                // set pattern
                patternLayout->setConversionPattern((*key).second);
            }

            layout = patternLayout;
        }
        else {
            throw ConfigureFailure(std::string("Unknown layout type '" + layoutType +
                                               "' for appender '") + appenderName + "'");
        }

        appender->setLayout(layout);
    }

    /**
     * Get the categories contained within the map of properties.  Since
     * the category looks something like "category.xxxxx.yyy.zzz", we need
     * to search the entire map to figure out which properties are category
     * listings.  Seems like there might be a more elegant solution.
     */
    void ConfiguratorSkeleton::getCategories(std::vector<std::string>& catlist) throw (ConfigureFailure) {
        // add the root category first
        catlist.push_back(std::string("rootCategory"));

        // then look for "category."
        for (PropertiesMap::iterator iter = _properties.begin();
             iter != _properties.end(); iter++) {
            // get the property name and test against "category."
            std::string::size_type length = (*iter).first.find("category.");
            if (length != std::string::npos) {
                // found one, so add it to the list
                std::string catname =
                    (*iter).first.substr(length + std::string("category.").size());
                catlist.push_back(catname);
            }
        }
    }

    // Tool to remove the white space from both ends:
    std::string ConfiguratorSkeleton::trim(const std::string& s) {
        // test for null string
        if(s.empty())
            return s;

        // find first non-space character
        std::string::size_type b = s.find_first_not_of(" \t");
        if(b == std::string::npos) // No non-spaces
            return "";

        // find last non-space character
        std::string::size_type e = s.find_last_not_of(" \t");

        // return the remaining characters
        return std::string(s, b, e - b + 1);
    }

    PropertiesMap& ConfiguratorSkeleton::getProperties() {
        return _properties;
    }
}
