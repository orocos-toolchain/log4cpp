/*
 * HierarchyMaintainer.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_HIERARCHYMAINTAINER_HH
#define _LOG4CPP_HIERARCHYMAINTAINER_HH

#include <string>
#include "log4cpp/Category.hh"
#include "log4cpp/Log4cppCleanup.hh"

namespace log4cpp {
    
    class HierarchyMaintainer {
        friend class Log4cppCleanup;

        public:
        typedef std::map<std::string, Category*> CategoryMap;
  
        static HierarchyMaintainer& getDefaultMaintainer();

        HierarchyMaintainer();
        virtual ~HierarchyMaintainer();
        virtual Category& getInstance(const std::string& name);
        virtual std::set<Category*>* getCurrentCategories() const;
        virtual void shutdown();
        virtual void deleteAllCategories();

        protected:
        CategoryMap _categoryMap;
        
        private:
        static HierarchyMaintainer* _defaultMaintainer;
        static Log4cppCleanup& _fuckinDummy;
    };        
}

#endif // _LOG4CPP_HIERARCHYMAINTAINER_HH
