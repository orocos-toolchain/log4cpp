/*
 * NDC.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_NDC_HH
#define _LOG4CPP_NDC_HH

#include <string>
#include <vector>

namespace log4cpp {
    
    class NDC {
        public:

        struct DiagnosticContext {
            DiagnosticContext(const string& message);
            DiagnosticContext(const string& message, 
                              const DiagnosticContext& parent);

            string message;
            string fullMessage;
        };

        typedef vector<DiagnosticContext> ContextStack;

        static void clear();
        static ContextStack* cloneStack();
        static const string& get();
        static int getDepth();
        static void inherit(ContextStack* stack);
        static string pop();
        static void push(const string& message);
        static void setMaxDepth(int maxDepth);
        static NDC& getNDC();

        protected:
        NDC();
        virtual ~NDC();
        virtual void _clear();
        virtual ContextStack* _cloneStack();
        virtual const string& _get() const;
        virtual int _getDepth() const;
        virtual void _inherit(ContextStack* stack);
        virtual string _pop();
        virtual void _push(const string& message);
        virtual void _setMaxDepth(int maxDepth);

        ContextStack _stack;

        private:
        static NDC _nDC;

    };        
}

#endif // _LOG4CPP_NDC_HH
