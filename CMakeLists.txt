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

INCLUDE_DIRECTORIES ( ${CMAKE_CURRENT_SOURCE_DIR}/include )
INCLUDE_DIRECTORIES ( ${CMAKE_CURRENT_SOURCE_DIR}/. )

# for pkgconfig
SET(LOG4CPP_CFLAGS)
SET(LOG4CPP_LIBS)

IF (WIN32)
  SET (CMAKE_DEBUG_POSTFIX "d")
  LIST(APPEND LOG4CPP_CFLAGS -D_CRT_SECURE_NO_WARNINGS -DLOG4CPP_HAS_DLL -DLOG4CPP_BUILD_DLL )
ELSE (WIN32)
  IF (APPLE)
#	LIST(APPEND LOG4CPP_CFLAGS -DLOG4CPP_HAVE_SSTREAM)
  ELSE (APPLE)
	LIST(APPEND LOG4CPP_CFLAGS -pthread)
  ENDIF (APPLE)
ENDIF (WIN32)

SET ( LOG4CPP_LIBRARY_NAME "orocos-log4cpp" )

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
  src/DailyRollingFileAppender.cpp
  src/RollingFileAppender.cpp
  src/GenerationalFileAppender.cpp
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

SET(VERSION "2.9.0")
SET(SOVERSION "2.9")
SET_TARGET_PROPERTIES(${LOG4CPP_LIBRARY_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})

# Ensure that the full path+lib name is used in dynamic library dependencies
# in dependent libraries/executables. Without this, CMake drops the path and
# the dependency becomes just the lib name (which requires working DYLD_xxx)
SET_TARGET_PROPERTIES(${LOG4CPP_LIBRARY_NAME} PROPERTIES
                      INSTALL_RPATH_USE_LINK_PATH ON)
# Set INSTALL_NAME_DIR for MacOS X to tell users of this library how to find it:
if(APPLE)
    if (CMAKE_VERSION VERSION_LESS "3.0.0")
        SET_TARGET_PROPERTIES( ${LOG4CPP_LIBRARY_NAME} PROPERTIES
            INSTALL_NAME_DIR "@rpath"
        )
    else()
        # cope with CMake 3.x
        SET_TARGET_PROPERTIES( ${LOG4CPP_LIBRARY_NAME} PROPERTIES
            MACOSX_RPATH ON)
    endif()
endif()

ADD_DEFINITIONS(${LOG4CPP_CFLAGS})

###########################################################
# CONFIGURE
###########################################################

# determine what system supports (equivalent of autotools' "./configure")
INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/Configure.cmake")

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/config-cmake.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/log4cpp/config.h)
# BEFORE the source dir, so as not to accidentally pick up a configure'd file
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/include)

###########################################################
# INSTALL TARGETS
###########################################################

STRING(TOLOWER "${PROJECT_NAME}" PACKAGE)
SET(prefix "${CMAKE_INSTALL_PREFIX}")
SET(exec_prefix "\${prefix}")
SET(log4cpp_cflags "")
SET(log4cpp_libs "${LOG4CPP_LIBS}")
SET(includedir "\${prefix}/include/orocos")
SET(libdir "\${prefix}/lib")
CONFIGURE_FILE(log4cpp.pc.in ${CMAKE_CURRENT_BINARY_DIR}/orocos-log4cpp.pc @ONLY)

INSTALL(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/orocos-log4cpp.pc
  DESTINATION lib/pkgconfig
  )

INSTALL (
  DIRECTORY include/log4cpp
  DESTINATION include/orocos
  PATTERN "config.h.in" EXCLUDE
  PATTERN ".svn" EXCLUDE
  PATTERN "*.am" EXCLUDE
  PATTERN "*.in" EXCLUDE
  PATTERN "*~" EXCLUDE
  )

INSTALL (
  FILES ${CMAKE_CURRENT_BINARY_DIR}/include/log4cpp/config.h
  DESTINATION include/orocos/log4cpp
  )

INSTALL(TARGETS ${LOG4CPP_LIBRARY_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION lib)

INSTALL(FILES package.xml DESTINATION share/log4cpp)

###########################################################
# DOCUMENTATION
###########################################################

find_package( Doxygen )
IF ( DOXYGEN_EXECUTABLE )
  SET(PACKAGE_NAME "${PROJECT_NAME}")
  SET(PACKAGE_VERSION "${VERSION}")
  SET(enable_latex_docs "NO")
  SET(enable_html_docs "YES")
  SET(top_srcdir "${CMAKE_SOURCE_DIR}")
  SET(enable_dot "${DOT_EXECUTABLE}")
  CONFIGURE_FILE(doc/Doxyfile.in Doxyfile @ONLY)
  ADD_CUSTOM_TARGET(docs ${DOXYGEN_EXECUTABLE} "Doxyfile")
ENDIF ( DOXYGEN_EXECUTABLE )

###########################################################
# TESTS
###########################################################

add_subdirectory(tests)
