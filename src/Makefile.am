lib_LTLIBRARIES = liblog4cpp.la

INCLUDES = -I$(top_srcdir)/include

noinst_HEADERS = snprintf.c

liblog4cpp_la_SOURCES = \
	Appender.cpp \
	AppenderSkeleton.cpp \
	LayoutAppender.cpp \
	FileAppender.cpp \
	FixedContextCategory.cpp \
	IdsaAppender.cpp \
	OstreamAppender.cpp \
	StringQueueAppender.cpp \
	SyslogAppender.cpp \
	RemoteSyslogAppender.cpp \
	SimpleLayout.cpp \
	BasicLayout.cpp \
	PatternLayout.cpp \
	Category.cpp \
	CategoryStream.cpp \
	HierarchyMaintainer.cpp \
	SimpleConfigurator.cpp \
	LoggingEvent.cpp \
	Priority.cpp \
	NDC.cpp \
	OstringStream.cpp \
	Filter.cpp \
	Log4cppCleanup.cpp \
	TimeStamp.cpp

liblog4cpp_la_LDFLAGS = -version-info @LT_VERSION@
