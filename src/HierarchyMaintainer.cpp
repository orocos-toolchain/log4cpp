/*
 * HierarchyMaintainer.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
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
#include "log4cpp/HierarchyMaintainer.hh"
#include "log4cpp/FileAppender.hh"

namespace log4cpp {
#ifdef LOG4CPP_USE_CLEANUP
    Log4cppCleanup& HierarchyMaintainer::_fuckinDummy = Log4cppCleanup::_cleanup;
#endif

    HierarchyMaintainer* HierarchyMaintainer::_defaultMaintainer = NULL;

    HierarchyMaintainer& HierarchyMaintainer::getDefaultMaintainer() {
        if (!_defaultMaintainer)
            _defaultMaintainer = new HierarchyMaintainer();

        return *_defaultMaintainer;
    }

    HierarchyMaintainer::HierarchyMaintainer() {
    }

    HierarchyMaintainer::~HierarchyMaintainer() {
        shutdown();
        deleteAllCategories();
    }

    Category* HierarchyMaintainer::getExistingInstance(const std::string& name) {
	Category* result = NULL;
        CategoryMap::iterator i = _categoryMap.find(name);
        if (_categoryMap.end() != i) {
	    result = (*i).second;
	}

	return result;
    }

    Category& HierarchyMaintainer::getInstance(const std::string& name) {
	Category* result = getExistingInstance(name);

        if (NULL == result) {            
            if (name == "") {
		result = new Category(name, NULL, Priority::INFO);
                result->addAppender(new FileAppender("_", ::dup(fileno(stderr))));
            } else {
                std::string parentName;
                size_t dotIndex = name.find_last_of('.');
                if (name.length() <= dotIndex) {
                    parentName = "";
                } else {
                    parentName = name.substr(0, dotIndex);
                }
                Category& parent = getInstance(parentName);
                result = new Category(name, &parent, Priority::NOTSET);
            }	  
            _categoryMap[name] = result; 
	}

	return *result;
    }

    std::set<Category*>* HierarchyMaintainer::getCurrentCategories() const {
        std::set<Category*>* categories = new std::set<Category*>;

        for(CategoryMap::const_iterator i = _categoryMap.begin(); i != _categoryMap.end(); i++) {
            categories->insert((*i).second);
        }

        return categories;
    }

    void HierarchyMaintainer::shutdown() {
        for(CategoryMap::const_iterator i = _categoryMap.begin(); i != _categoryMap.end(); i++) {
            ((*i).second)->removeAllAppenders();
        }
    }

    void HierarchyMaintainer::deleteAllCategories() {
        for(CategoryMap::const_iterator i = _categoryMap.begin(); i != _categoryMap.end(); i++) {
            delete ((*i).second);
        }
    }

}
