/*
 * NDC.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_NDC_HH
#define _LOG4CPP_NDC_HH

#include <string>
#include <vector>

namespace log4cpp {
    
    class NDC {
        public:

        struct DiagnosticContext {
            DiagnosticContext(const std::string& message);
            DiagnosticContext(const std::string& message, 
                              const DiagnosticContext& parent);

            std::string message;
            std::string fullMessage;
        };

        typedef vector<DiagnosticContext> ContextStack;

        static void clear();
        static ContextStack* cloneStack();
        static const std::string& get();
        static int getDepth();
        static void inherit(ContextStack* stack);
        static std::string pop();
        static void push(const std::string& message);
        static void setMaxDepth(int maxDepth);
        static NDC& getNDC();

        protected:
        NDC();

#if defined(__GNUG__) && (__GNUC__ == 2) && (__GNUC_MINOR__ <= 95)
        public:
        virtual ~NDC();
#else
        protected: 
        virtual ~NDC();
#endif
        protected:
        virtual void _clear();
        virtual ContextStack* _cloneStack();
        virtual const std::string& _get() const;
        virtual int _getDepth() const;
        virtual void _inherit(ContextStack* stack);
        virtual std::string _pop();
        virtual void _push(const std::string& message);
        virtual void _setMaxDepth(int maxDepth);

        ContextStack _stack;

        private:
        static NDC _nDC;

    };        
}

#endif // _LOG4CPP_NDC_HH
