/*
 * PatternLayout.hh
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_PATTERNLAYOUT_HH
#define _LOG4CPP_PATTERNLAYOUT_HH

#include "log4cpp/Portability.hh"
#include "log4cpp/Export.hh"
#include "log4cpp/Layout.hh"

namespace log4cpp {

#ifdef LOG4CPP_HAVE_INT64_T
    typedef int64_t QUITE_LONG;
#else
    typedef double QUITE_LONG;
#endif

    
    /**
     * BasicLayout is a simple fixed format Layout implementation. 
     **/
    class LOG4CPP_EXPORT PatternLayout : public Layout {
        public:
        PatternLayout();
        virtual ~PatternLayout();
        
        /**
         * Formats the LoggingEvent in the style set by
		 * the setConversionPattern call. By default, set
		 * to "%m%n"
         **/
        virtual std::string format(const LoggingEvent& event);

        /**
         * Sets the format of log lines handled by this
         * PatternLayout. By default, set to "%m%n".<br>
         * Format characters are as follows:<br>
         * <li><b>%%</b> - a single percent sign</li>
         * <li><b>%c</b> - the category</li>
         * <li><b>%d</b> - the date</li>
         * <li><b>%D</b> - seconds since 1970</li>
         * <li><b>%m</b> - the message</li>
         * <li><b>%n</b> - the platform specific line separator</li>
         * <li><b>%p</b> - the priority</li>
         * <li><b>%r</b> - milliseconds since this layout was created.</li>
         * <li><b>%R</b> - seconds since Jan 1, 1970</li>
         * <li><b>%u</b> - clock ticks since process start</li>
         * <li><b>%x</b> - the NDC</li>
         * @param conversionPattern the conversion pattern
         * @return true if conversionPattern is a valid
         * conversion pattern, false if it's invalid
         **/
        bool setConversionPattern(std::string conversionPattern);

        private:
        std::string convPatn;	// The conversion pattern set for this layout
        /**
         * Method to format with current conversion pattern, success
         * returned as false if invalid format string (and empty string
         * returned), success returned true and string returned containing
         * message converted according to conversion pattern.
         * The reason for this method is to avoid having to have 
         * "checkValidityOfConversionPattern" code and also
         * "convertUsingConversionPattern" code. With this method,
         * the "setConversionPattern" can call doFormat with a fake
         * LoggingEvent to see if the conversionPattern is valid.
         */
        std::string doFormat(const LoggingEvent& event, std::string conversionPattern, bool *success);
        
        // GetTickCount() (Windows) or milliseconds since 1970 (64 bit long systems) at construction time
        QUITE_LONG millisecondsAtCreation;

        /**
         * Returns the number of milliseconds elapsed since this layout
         * was created. On systems where <b>long</b> is only 32 bits (most),
         * this method will start to give "funny" values on systems
         * that are kept up for a long time
         * @return the milliseconds since layout creation time
         */
        QUITE_LONG millisecondsSinceCreation();

        /**
         * Facade method to hide details of how to get some get-time-call in
         * milliseconds resolution.
         * @return milliseconds according to some increasing clock
         */
        QUITE_LONG getMillisecondsTime();
    };        
}

#endif // _LOG4CPP_PATTERNLAYOUT_HH
