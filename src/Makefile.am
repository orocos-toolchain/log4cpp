lib_LTLIBRARIES = liblog4cpp.la

INCLUDES = -I$(top_srcdir)/include

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
	SimpleLayout.cpp \
	BasicLayout.cpp \
	Category.cpp \
	HierarchyMaintainer.cpp \
	LoggingEvent.cpp \
	Priority.cpp \
	NDC.cpp \
	OstringStream.cpp \
	Filter.cpp \
	Log4cppCleanup.cpp

liblog4cpp_la_LDFLAGS = -version-info @LT_VERSION@
