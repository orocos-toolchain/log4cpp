/*
 * CategoryStream.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_CATEGORYSTREAM_HH
#define _LOG4CPP_CATEGORYSTREAM_HH

#include "log4cpp/Portability.hh"
#include "log4cpp/Export.hh"
#include "log4cpp/OstringStream.hh"
#include "log4cpp/Priority.hh"

namespace log4cpp {

    class LOG4CPP_EXPORT Category;

    /**
     * This class enables streaming simple types and objects to a category.
     * Use category.errorStream(), etc. to obtain a CategoryStream class.
     **/
    class LOG4CPP_EXPORT CategoryStream {
        public:

        /**
         * Enumeration of special 'Separators'. Currently only contains the
         * 'ENDLINE' separator, which separates two log messages.
         **/
        typedef enum {
            ENDLINE
        } Separator;

        /**
         * Construct a CategoryStream for given Category with given priority.
         * @param category The category this stream will send log messages to.
         * @param priority The priority the log messages will get or 
         * Priority::NOTSET to silently discard any streamed in messages.
         **/
        CategoryStream(Category& category, Priority::Value priority);

        /**
         * Destructor for CategoryStream
         **/
        ~CategoryStream();
        
        /**
         * Returns the destination Category for this stream.
         * @returns The Category.
         **/
        inline Category& getCategory() const { return _category; };

        /**
         * Returns the priority for this stream.
         * @returns The priority.
         **/
        inline Priority::Value getPriority() const throw() { 
            return _priority; 
        };

        /**
         * Streams in a Separator. If the separator equals 
         * CategoryStream::ENDLINE it sends the contents of the stream buffer
         * to the Category with set priority and empties the buffer.
         * @param Separator The Separator
         * @returns A reference to itself.
         **/
        CategoryStream& operator<<(Separator separator);

        /**
         * Flush the contents of the stream buffer to the Category and
         * empties the buffer.
         **/
        void flush();

        /**
         * Stream in arbitrary types and objects.  
         * @param t The value or object to stream in.
         * @returns A reference to itself.
         **/
        template<typename T> CategoryStream& operator<<(const T& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_buffer) {
                    if (!(_buffer = new OstringStream)) {
                        // XXX help help help
                    }
                }
                (*_buffer) << t;
            }
            return *this;
        }
        
        private:
        Category& _category;
        Priority::Value _priority;
        OstringStream* _buffer;
    };

}
#endif // _LOG4CPP_CATEGORYSTREAM_HH
