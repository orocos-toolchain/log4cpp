/*
 * HierarchyMaintainer.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_HIERARCHYMAINTAINER_HH
#define _LOG4CPP_HIERARCHYMAINTAINER_HH

#include <string>
#include "log4cpp/Category.hh"

namespace log4cpp {
    
    class HierarchyMaintainer {
        public:
        typedef map<const string, Category*> CategoryMap;
  
        static HierarchyMaintainer& getDefaultMaintainer();

        HierarchyMaintainer();
        virtual ~HierarchyMaintainer();
        virtual Category& getInstance(const string& name);
        virtual set<Category*>* getCurrentCategories() const;

        protected:
        CategoryMap _categoryMap;
        
        private:
        static HierarchyMaintainer _defaultMaintainer;
    };        
}

#endif // _LOG4CPP_HIERARCHYMAINTAINER_HH
