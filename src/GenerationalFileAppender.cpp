/*
 * GenerationalFileAppender.cpp
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#ifdef LOG4CPP_HAVE_IO_H
#    include <io.h>
#endif
#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <log4cpp/GenerationalFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/FactoryParams.hh>
#include <memory>
#include <stdio.h>

#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#endif

namespace log4cpp {

    GenerationalFileAppender::GenerationalFileAppender(const std::string& name,
                                             const std::string& fileName,
                                             bool append,
                                             mode_t mode) :
        FileAppender(name, fileName+".0", append, mode),
		_originalFileName(fileName),
		_generation(0) {
    }

    void GenerationalFileAppender::advanceGeneration() {
		++_generation;
		std::ostringstream str;
		str << _originalFileName << "." << _generation << std::ends;
        int new_fd = ::open(str.str().c_str(), _flags, _mode);
		if (-1 != new_fd)
		{
			// avoid race-conditions as much as possible (w/o locks)
			int old_fd = _fd;
			_fd = new_fd;
			::close(old_fd);
		}
		/// \todo else produce error on stderr?
    }

   std::auto_ptr<Appender> create_generation_file_appender(const FactoryParams& params)
   {
      std::string name, filename;
      bool append = true;
      mode_t mode = 664;
      params.get_for("rool file appender").required("name", name)("filename", filename)
                                          .optional("append", append)("mode", mode);

      return std::auto_ptr<Appender>(new GenerationalFileAppender(name, filename, append, mode));
   }
}
