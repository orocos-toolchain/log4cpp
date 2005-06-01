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

#include <log4cpp/Portability.hh>
#include <log4cpp/Priority.hh>
#include <ios>
#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#endif
#include <log4cpp/Manipulator.hh>

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
            ENDLINE = 0,
			EOL		= 0
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
         * @param separator The Separator
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
                    if (!(_buffer = new std::ostringstream)) {
                        // XXX help help help
                    }
                }
                (*_buffer) << t;
            }
            return *this;
        }
		template<typename T> CategoryStream& operator<<(const std::string& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_buffer) {
                    if (!(_buffer = new std::ostringstream)) {
                        // XXX help help help
                    }
                }
                (*_buffer) << t;
            }
            return *this;
        }
		template<typename T> CategoryStream& operator<<(const std::wstring& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_wbuffer) {
                    if (!(_wbuffer = new std::wostringstream)) {
                        // XXX help help help
                    }
                }
                (*_wbuffer) << t;
            }
            return *this;
        }

        /**
         * Set the width output on CategoryStream
         **/
		std::streamsize width(std::streamsize wide );


        private:
        Category& _category;
        Priority::Value _priority;
		union {
			std::ostringstream* _buffer;
			std::wostringstream* _wbuffer;
		};

		public:
		typedef CategoryStream& (*cspf) (CategoryStream&);

		CategoryStream& operator<< (cspf);

        /**
         * eol manipulator
         **/
friend  LOG4CPP_EXPORT CategoryStream& eol (CategoryStream& os);

        /**
         * left manipulator
         **/
friend  LOG4CPP_EXPORT CategoryStream& left (CategoryStream& os);
   };
}
#endif // _LOG4CPP_CATEGORYSTREAM_HH
