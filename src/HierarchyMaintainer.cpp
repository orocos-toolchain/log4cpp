/*
 * HierarchyMaintainer.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include <unistd.h>
#include "log4cpp/HierarchyMaintainer.hh"
#include "log4cpp/FileAppender.hh"

namespace log4cpp {

    HierarchyMaintainer HierarchyMaintainer::_defaultMaintainer;

    HierarchyMaintainer& HierarchyMaintainer::getDefaultMaintainer() {
        return _defaultMaintainer;
    }

    HierarchyMaintainer::HierarchyMaintainer() {
    }

    HierarchyMaintainer::~HierarchyMaintainer() {
    }

    Category& HierarchyMaintainer::getInstance(const std::string& name) {
        CategoryMap::iterator i = _categoryMap.find(name);
        if (_categoryMap.end() == i) {
            Category* result;
            
            if (name == "") {
                result = new Category(name, NULL, Priority::INFO);
                result->setAppender(new FileAppender("_", ::dup(STDERR_FILENO)));
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
            return *result;
        } else {
            return *((*i).second);
        }
    }

    set<Category*>* HierarchyMaintainer::getCurrentCategories() const {
        set<Category*>* categories = new set<Category*>;

        for(CategoryMap::const_iterator i = _categoryMap.begin(); i != _categoryMap.end(); i++) {
            categories->insert((*i).second);
        }

        return categories;
    }
}
