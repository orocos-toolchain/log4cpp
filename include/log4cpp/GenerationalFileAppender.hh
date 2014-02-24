/*
 * GenerationalFileAppender.hh
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_GENERATIONALFILEAPPENDER_HH
#define _LOG4CPP_GENERATIONALFILEAPPENDER_HH

#include <log4cpp/Portability.hh>
#include <log4cpp/FileAppender.hh>
#include <string>
#include <stdarg.h>

namespace log4cpp {

    /**
       A FileAppender that rolls over logfile generations when instructed.
	   @param name the name of the Appender.
	   @param fileName the name of the file to which the Appender has
	   to log (the actual filename will be "filename" for the first logfile,
	   and "filename.0" after rollOver(), then "filename.1", etc.)
	   @param append whether the Appender has to truncate the file or
	   just append to it if it already exists. Defaults to 'true'.
	   @param mode file mode to open the logfile with. Defaults to 00644.
       @since 6.0.0
    **/
    class LOG4CPP_EXPORT GenerationalFileAppender : public FileAppender {
        public:
		/// Open "filename.0" and set _generation=0
        GenerationalFileAppender(const std::string& name,
								 const std::string& fileName,
								 bool append = true,
								 mode_t mode = 00644);

		/** Advance to next logfile generation
			\post if could open the next file then all subsequent events
			are logged to the new logfile ("filename._generation"),
			otherwise all subsequent events continue to be logged to the
			currently open logfile
		*/
        virtual void advanceGeneration();

        protected:

		/// Filename given to the constructor, _before_ an extension is applied
		std::string _originalFileName;
		/// The current generation (initializes to 0)
		unsigned int _generation;
    };
}

#endif // _LOG4CPP_GENERATIONALFILEAPPENDER_HH
