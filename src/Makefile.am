lib_LTLIBRARIES = liblog4cpp.la

INCLUDES = -I../include

liblog4cpp_la_SOURCES = \
	Hints.cpp \
	Appender.cpp \
	FileAppender.cpp \
	OstreamAppender.cpp \
	SyslogAppender.cpp \
	SimpleLayout.cpp \
	BasicLayout.cpp \
	Category.cpp \
	HierarchyMaintainer.cpp \
	LoggingEvent.cpp \
	Priority.cpp \
	NDC.cpp


liblog4cpp_la_LDFLAGS = -version-info @LT_VERSION@
liblog4cppincludedir = $(includedir)/log4cpp
