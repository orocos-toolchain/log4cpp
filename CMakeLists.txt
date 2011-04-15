#
# Nicholas Yue nicholas_yue@users.sourceforge.net
# S Roderick (kiwi.net@mac.com)
#
# Note:
# - configures using CMake. Only a minimal set of configuration items are
# tested (checked on Mac OS X Snow Leopard and Ubuntu 10.04 Lucid Lynx)
# - build with "mkdir build; cd build; cmake ..; make"
# - set install path with "cmake -DCMAKE_INSTALL_PREFIX=/path/to/install .." in the above
# - install with "make install"

PROJECT ( LOG4CPP )
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE_DIRECTORIES ( ${CMAKE_SOURCE_DIR}/include )
INCLUDE_DIRECTORIES ( ${CMAKE_SOURCE_DIR}/. )

# for pkgconfig
SET(LOG4CPP_CFLAGS)
SET(LOG4CPP_LIBS)

SET (CMAKE_DEBUG_POSTFIX "d")

IF (WIN32)
  LIST(APPEND LOG4CPP_CFLAGS -D_CRT_SECURE_NO_WARNINGS -DLOG4CPP_HAS_DLL -DLOG4CPP_BUILD_DLL )
ELSE (WIN32)
  IF (APPLE)
#	LIST(APPEND LOG4CPP_CFLAGS -DLOG4CPP_HAVE_SSTREAM)
  ELSE (APPLE)
	LIST(APPEND LOG4CPP_CFLAGS -pthread)
  ENDIF (APPLE)
ENDIF (WIN32)

#IF ( CMAKE_BUILD_TYPE MATCHES "Debug" )
#  SET ( LOG4CPP_LIBRARY_NAME "log4cppD" )
#ELSE ( CMAKE_BUILD_TYPE MATCHES "Debug" )
  SET ( LOG4CPP_LIBRARY_NAME "log4cpp" )
#ENDIF ( CMAKE_BUILD_TYPE MATCHES "Debug" )

ADD_LIBRARY ( ${LOG4CPP_LIBRARY_NAME} SHARED
  src/Appender.cpp
  src/AppenderSkeleton.cpp
  src/AppendersFactory.cpp
  src/BufferingAppender.cpp
  src/FactoryParams.cpp
  src/LayoutsFactory.cpp
  src/LevelEvaluator.cpp
  src/Localtime.cpp
  src/PassThroughLayout.cpp
  src/TriggeringEventEvaluatorFactory.cpp
  src/LayoutAppender.cpp
  src/FileAppender.cpp
  src/RollingFileAppender.cpp
  src/FixedContextCategory.cpp
  src/IdsaAppender.cpp
  src/OstreamAppender.cpp
  src/StringQueueAppender.cpp
  src/SyslogAppender.cpp
  src/RemoteSyslogAppender.cpp
  src/SimpleLayout.cpp
  src/BasicLayout.cpp
  src/PatternLayout.cpp
  src/Category.cpp
  src/CategoryStream.cpp
  src/HierarchyMaintainer.cpp
  src/Configurator.cpp
  src/BasicConfigurator.cpp
  src/SimpleConfigurator.cpp
  src/PropertyConfigurator.cpp
  src/PropertyConfiguratorImpl.cpp
  src/LoggingEvent.cpp
  src/Priority.cpp
  src/NDC.cpp
  src/Filter.cpp
  src/TimeStamp.cpp
  src/StringUtil.cpp
  src/Properties.cpp
  src/Win32DebugAppender.cpp
  src/NTEventLogAppender.cpp
  src/DllMain.cpp
  src/DummyThreads.cpp
  src/MSThreads.cpp
  src/OmniThreads.cpp
  src/PThreads.cpp
  src/PortabilityImpl.cpp
  src/AbortAppender.cpp
)

IF (WIN32)
  TARGET_LINK_LIBRARIES (${LOG4CPP_LIBRARY_NAME} kernel32 user32 ws2_32 advapi32 )
#  SET_TARGET_PROPERTIES(${LOG4CPP_LIBRARY_NAME} PROPERTIES LINK_FLAGS /NODEFAULTLIB:msvcrt)
ENDIF (WIN32)

# Note: this so-version is required by OCL, such that it can distinguish 'regular' log4cpp
# from 'rtt' log4cpp.
SET(VERSION "6.0.0")
SET(SOVERSION "6.0")
SET_TARGET_PROPERTIES(${LOG4CPP_LIBRARY_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})

ADD_DEFINITIONS(${LOG4CPP_CFLAGS})

###########################################################
# CONFIGURE
###########################################################

# determine what system supports (equivalent of autotools' "./configure")
INCLUDE("${CMAKE_SOURCE_DIR}/Configure.cmake")

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/include/config-cmake.h.in ${CMAKE_BINARY_DIR}/include/log4cpp/config.h)
# BEFORE the source dir, so as not to accidentally pick up a configure'd file
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_BINARY_DIR}/include)

###########################################################
# INSTALL TARGETS
###########################################################

STRING(TOLOWER "${PROJECT_NAME}" PACKAGE)
SET(prefix "${CMAKE_INSTALL_PREFIX}")
SET(exec_prefix "\${prefix}")
SET(log4cpp_cflags "")
SET(log4cpp_libs "${LOG4CPP_LIBS}")
SET(includedir "\${prefix}/include")
SET(libdir "\${prefix}/lib")
CONFIGURE_FILE(log4cpp.pc.in ${CMAKE_BINARY_DIR}/log4cpp.pc @ONLY)

INSTALL(
  FILES ${CMAKE_BINARY_DIR}/log4cpp.pc
  DESTINATION lib/pkgconfig
  )

INSTALL (
  DIRECTORY include/log4cpp
  DESTINATION include
  PATTERN "config.h.in" EXCLUDE
  PATTERN ".svn" EXCLUDE
  PATTERN "*.am" EXCLUDE
  PATTERN "*.in" EXCLUDE
  )

INSTALL (
  FILES ${CMAKE_BINARY_DIR}/include/log4cpp/config.h
  DESTINATION include/log4cpp
  )

INSTALL(TARGETS ${LOG4CPP_LIBRARY_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION lib)
