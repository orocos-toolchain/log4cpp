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
        int length;
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
        if (categoryName.compare("rootCategory") == 0) {
            category = &Category::getRoot();
        } else {
            category = &Category::getInstance(categoryName);
        }

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
        std::list<std::string>::iterator list_iter = tokens.begin();

        for (; list_iter != tokens.end(); list_iter++) {
            std::string name = trim(*list_iter);

            if (!setPriority(name, *category)) {
                // not a priority, so it must be an appender
                configAppender(name, *category);
            }
        }

    }

    void ConfiguratorSkeleton::configAppender(std::string& name, Category& category) {
        std::string appender_type, tempString;
        PropertiesMap::iterator iter = _properties.begin();
		
        // we're given the appender name, so get the property associated with it
        tempString = std::string("appender.") + name;
        PropertiesMap::iterator key = _properties.find(tempString);

        if (key != _properties.end()) {

            // instantiate the appender
            Appender* appender = instantiateAppender(name);
			
            // and set it to the category
            category.setAppender(appender);
        }
    }

    Appender* ConfiguratorSkeleton::instantiateAppender(const std::string& name) {
        Appender* appender = NULL;

        // determine the type by the name 
        std::string tempString = std::string("appender.") + name;
        std::string appender_type, objectname;
        PropertiesMap::iterator key = _properties.find(tempString);

        if (key == _properties.end())
            throw ConfigureFailure(std::string("Invalid appender name: see") + name);
		
        int length = (*key).second.find_last_of(".");

        if (length != std::string::npos)
            appender_type = (*key).second.substr(length+1);
        else
            appender_type = (*key).second;

        // and instantiate the appropriate object
        if (appender_type.compare("ConsoleAppender") == 0) {
            tempString = std::string("appender.") + name + std::string(".name");
            PropertiesMap::iterator key = _properties.find(tempString);

            if (key == _properties.end())
                objectname = "default";
            else
                objectname = (*key).second;

            // create the appender
            appender = new OstreamAppender(objectname, &std::cout);

            // set layout
            setLayout(appender, name);
        }

        if (appender_type.compare("FileAppender") == 0) {
            std::string filename;
            tempString = std::string("appender.") + name + std::string(".name");
            PropertiesMap::iterator key = _properties.find(tempString);

            if (key == _properties.end())
                objectname = "default";
            else
                objectname = (*key).second;

            tempString = std::string("appender.") + name + std::string(".Filename");
            key = _properties.find(tempString);

            if (key == _properties.end())
                filename = "foobar";	// default file name
            else
                filename = (*key).second;

            appender = new FileAppender(objectname, filename);

            // set layout
            setLayout(appender, name);
        }

        if (appender_type.compare("SyslogAppender") == 0) {
            std::string sysloghost, syslogname;
            int facility, portnumber;

            // start with object name
            tempString = std::string("appender.") + name + std::string(".name");
            PropertiesMap::iterator key = _properties.find(tempString);

            if (key == _properties.end())
                objectname = "default";
            else
                objectname = (*key).second;

            // get syslog name, i.e. "ident"
            tempString = std::string("appender.") + name + std::string(".SyslogName");
            key = _properties.find(tempString);

            if (key == _properties.end())
                syslogname = "syslog";
            else
                syslogname = (*key).second;

            // get syslog host
            tempString = std::string("appender.") + name + std::string(".SyslogHost");
            key = _properties.find(tempString);

            if (key == _properties.end())
                sysloghost = "localhost";
            else
                sysloghost = (*key).second;

            // get facility
            tempString = std::string("appender.") + name + std::string(".Facility");
            key = _properties.find(tempString);

            if (key == _properties.end())
                facility = -1;
            else
                facility = atoi((*key).second.c_str());

            // get port number
            tempString = std::string("appender.") + name + std::string(".Port");
            key = _properties.find(tempString);

            if (key == _properties.end())
                portnumber = -1;
            else
                portnumber = atoi((*key).second.c_str());

            // see which parameters we have
            if (facility != -1 && portnumber != -1)
                appender = new RemoteSyslogAppender(objectname, syslogname, 
                                                             sysloghost, facility, portnumber);
            else if (facility != -1 && portnumber == -1)
                appender = new RemoteSyslogAppender(objectname, syslogname,
                                                             sysloghost, facility);
            else if (facility == -1 && portnumber != -1)
                appender = new RemoteSyslogAppender(objectname, syslogname, 
                                                             sysloghost, LOG_USER, portnumber);
            else
                appender = new RemoteSyslogAppender(objectname, syslogname, 
                                                             sysloghost);

            // set the layout
            setLayout(appender, name);
        }

#ifdef LOG4CPP_HAVE_LIBIDSA
        if (appender_type.compare("IdsaAppender") == 0) {
            std::string idsaname;
            tempString = std::string("appender.") + name + std::string(".name");
            PropertiesMap::iterator key = _properties.find(tempString);

            if (key == _properties.end())
                objectname = "default";
            else
                objectname = (*key).second;

            tempString = std::string("appender.") + name + std::string(".Idsaname");
            key = _properties.find(tempString);

            if (key == _properties.end())
                idsaname = "foobar";	// default idsa name ???
            else
                idsaname = (*key).second;

            appender = new IdsaAppender(objectname, idsaname);

            // set layout
            setLayout(appender, name);
        }
#endif	// LOG4CPP_HAVE_LIBIDSA

#ifdef WIN32
        // win32 debug appender
        if (appender_type.compare("Win32DebugAppender") == 0) {
            // check for name
            tempString = std::string("appender.") + name + std::string(".name");
            PropertiesMap::iterator key = _properties.find(tempString);
            if (key == _properties.end())
                objectname = "default";
            else
                objectname = (*key).second;

            appender = new Win32DebugAppender(objectname);

            // set layout
            setLayout(appender, name);
        }
#endif	// WIN32

        // if we made it this far without creating an appender, then something is wrong
        // otherwise return what we have
        if (appender)
            return appender;
        else
            throw ConfigureFailure(std::string("Invalid appender type: see ") + name);
    }

    void ConfiguratorSkeleton::setLayout(Appender* appender, const std::string& name) {
        // determine the type by name
        std::string layout_type;
        std::string tempString = std::string("appender.") + name + std::string(".layout");
        PropertiesMap::iterator key = _properties.find(tempString);

        if (key == _properties.end())
            throw ConfigureFailure(std::string("Invalid appender name in setLayout: see") + name);
		
        int length = (*key).second.find_last_of(".");

        if (length != std::string::npos)
            layout_type = (*key).second.substr(length+1);
        else
            layout_type = (*key).second;

        // and instantiate the appropriate object
        if (layout_type.compare("BasicLayout") == 0) {
            // not much to do here			
            appender->setLayout(new BasicLayout());
        }
        else if (layout_type.compare("SimpleLayout") == 0) {
            // not much here either
            appender->setLayout(new SimpleLayout());
        }
        else if (layout_type.compare("PatternLayout") == 0) {
            // need to read the properties to configure this one
            tempString = std::string("appender.") + name + std::string(".layout.ConversionPattern");
            key = _properties.find(tempString);

            PatternLayout* layout = new PatternLayout();

            // if we found the conversion pattern, set it otherwise use default
            if (key != _properties.end()) {
                layout->setConversionPattern((*key).second);
            }

            appender->setLayout(layout);
        }
        else {
            // if we haven't set a layout, and the appender requires one, we should probably 
            // at least set the basic layout
            if (appender->requiresLayout())
                appender->setLayout(new BasicLayout());
        }

    }

    bool ConfiguratorSkeleton::setPriority(std::string& name, Category& category) {
        bool ret = false;

        // test for priority name and set priority
        if (name.compare("DEBUG") == 0) {
            category.setPriority(Priority::DEBUG);
            ret = true;
        } else if (name.compare("INFO") == 0) {
            category.setPriority(Priority::INFO);
            ret = true;
        } else if (name.compare("WARN") == 0) {
            category.setPriority(Priority::WARN);
            ret = true;
        } else if (name.compare("ERROR") == 0) {
            category.setPriority(Priority::ERROR);
            ret = true;
        } else if (name.compare("FATAL") == 0) {
            category.setPriority(Priority::FATAL);
            ret = true;
        }

        return ret;
    }

    /**
     * Get the categories contained within the map of properties.  Since
     * the category looks something like "category.xxxxx.yyy.zzz", we need
     * to search the entire map to figure out which properties are category
     * listings.  Seems like there might be a more elegant solution.
     */
    void ConfiguratorSkeleton::getCategories(std::vector<std::string>& catlist) throw (ConfigureFailure) {
        int length;
        std::string catname;
        PropertiesMap::iterator iter = _properties.begin();
		
        // add the root category first
        catlist.push_back(std::string("rootCategory"));

        // then look for "category."
        for (;iter != _properties.end(); iter++) {
            // get the property name and test against "category."
            length = (*iter).first.find("category.");
            if (length != std::string::npos) {
                // found one, so add it to the list
                catname = (*iter).first.substr(length + std::string("category.").size());
                catlist.push_back(catname);
            }
        }
    }

    // Tool to remove the white space from both ends:
    std::string ConfiguratorSkeleton::trim(const std::string& s) {
        // test for null string
        if(s.length() == 0)
            return s;

        // find first non-space character
        int b = s.find_first_not_of(" \t");

        // find last non-space character
        int e = s.find_last_not_of(" \t");

        if(b == -1) // No non-spaces
            return "";

        // return the remaining characters
        return std::string(s, b, e - b + 1);
    }

    PropertiesMap& ConfiguratorSkeleton::getProperties() {
        return _properties;
    }
}
