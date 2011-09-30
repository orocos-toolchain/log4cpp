###########################################################
# LOG4CPP_HAVE_SSTREAM
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/strstream.cpp.in"
"#include <strstream>\n"
"int main()\n"
"{\n"
"	std::ostrstream	os;\n"
"	os.str();\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/strstream.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/strstream.cpp)
TRY_COMPILE(LOG4CPP_HAVE_SSTREAM ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/strstream.cpp OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_GETTIMEOFDAY
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/gettimeofday.c.in"
"#include <stdlib.h> // for NULL on Linux\n"
"#include <sys/time.h>\n"
"int main()\n"
"{\n"
"   struct timeval tv;\n"
"	(void)gettimeofday(&tv, NULL);\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/gettimeofday.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/gettimeofday.c)
TRY_COMPILE(LOG4CPP_HAVE_GETTIMEOFDAY ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/gettimeofday.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_STDINT_H
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/stdint_h.c.in"
"#include <stdint.h>\n"
"int main()\n"
"{\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/stdint_h.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/stdint_h.c)
TRY_COMPILE(LOG4CPP_HAVE_STDINT ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/stdint_h.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_UNISTD_H
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/unistd_h.c.in"
"#include <unistd.h>\n"
"int main()\n"
"{\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/unistd_h.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/unistd_h.c)
TRY_COMPILE(LOG4CPP_HAVE_UNISTD_H ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/unistd_h.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_IO_H
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/io_h.c.in"
"#include <io.h>\n"
"int main()\n"
"{\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/io_h.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/io_h.c)
TRY_COMPILE(LOG4CPP_HAVE_IO ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/io_h.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_SNPRINTF
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/snprintf.c.in"
"#include <stdio.h>\n"
"int main()\n"
"{\n"
"   char x[100];\n"
"   (void)snprintf(&x, sizeof(x), \"\");\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/snprintf.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/snprintf.c)
TRY_COMPILE(LOG4CPP_HAVE_SNPRINTF ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/snprintf.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_SYSLOG
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/syslog.c.in"
"#include <syslog.h>\n"
"int main()\n"
"{\n"
"   syslog(LOG_ERR, \"\");\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/syslog.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/syslog.c)
TRY_COMPILE(LOG4CPP_HAVE_SYSLOG ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/syslog.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_LOCALTIME_R
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/localtime_r.c.in"
"#include <time.h>\n"
"int main()\n"
"{\n"
"   time_t t;\n"
"   struct tm tm;\n"
"   (void)localtime_r(&t, &tm);\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/localtime_r.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/localtime_r.c)
TRY_COMPILE(LOG4CPP_HAVE_LOCALTIME_R ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/localtime_r.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_FTIME
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/ftime.c.in"
"#include <sys/timeb.h>\n"
"int main()\n"
"{\n"
"   struct timeb t;\n"
"   (void)ftime(&t);\n"
"	return 0;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/ftime.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/ftime.c)
TRY_COMPILE(LOG4CPP_HAVE_FTIME ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/ftime.c OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP_HAVE_INT64_T
###########################################################

IF (LOG4CPP_HAVE_STDINT)
  FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/int64_t.c.in"
	"#include <stdint.h>\n"
	"int main()\n"
	"{\n"
	"   volatile int64_t t;\n"
	"	return 0;\n"
	"}")
  CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/int64_t.c.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/int64_t.c)
  TRY_COMPILE(LOG4CPP_HAVE_INT64_T ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/int64_t.c OUTPUT_VARIABLE OUTPUT)
ENDIF (LOG4CPP_HAVE_STDINT)


###########################################################
# LOG4CPP_HAVE_NAMESPACES
###########################################################

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/namespaces.cpp.in"
"#include <stdint.h>\n"
"namespace test {\n"
" int x=1;\n"
"}\n"
"int main()\n"
"{\n"
"   return test::x;\n"
"}")
CONFIGURE_FILE(${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/namespaces.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/configure-tryouts/namespaces.cpp)
TRY_COMPILE(LOG4CPP_HAVE_NAMESPACES ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/configure-tryouts/namespaces.cpp OUTPUT_VARIABLE OUTPUT)

###########################################################
# LOG4CPP THREADING (only win32 or pthread supported)
###########################################################

find_package(Threads)

IF (CMAKE_THREAD_LIBS_INIT)

    IF(CMAKE_USE_WIN32_THREADS_INIT)
        SET(LOG4CPP_HAVE_THREADING TRUE)
        SET(LOG4CPP_USE_MSTHREADS TRUE)
        MESSAGE(STATUS "Log4cpp threading support enabled using win32 threads")
    ENDIF(CMAKE_USE_WIN32_THREADS_INIT)

    IF(CMAKE_USE_PTHREADS_INIT)
        SET(LOG4CPP_HAVE_THREADING TRUE)
        SET(LOG4CPP_USE_PTHREADS TRUE)
        MESSAGE(STATUS "Log4cpp threading support enabled using pthreads")
    ENDIF(CMAKE_USE_PTHREADS_INIT)

ENDIF (CMAKE_THREAD_LIBS_INIT)

# TODO
#LOG4CPP_HAVE_BOOST
#LOG4CPP_HAVE_DLFCN_H 
#LOG4CPP_HAVE_IN_ADDR_T 
#LOG4CPP_HAVE_LIBIDSA
#LOG4CPP_USE_ONMITHREADS

