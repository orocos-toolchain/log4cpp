check_PROGRAMS = testmain testCategory testFixedContextCategory testNDC testbench

INCLUDES = -I$(top_srcdir)/include

testmain_SOURCES = testmain.cpp
testmain_LDADD = $(top_builddir)/src/liblog4cpp.la

testCategory_SOURCES = testCategory.cpp
testCategory_LDADD = $(top_builddir)/src/liblog4cpp.la

testFixedContextCategory_SOURCES = testFixedContextCategory.cpp
testFixedContextCategory_LDADD = $(top_builddir)/src/liblog4cpp.la

testNDC_SOURCES = testNDC.cpp
testNDC_LDADD = $(top_builddir)//src/liblog4cpp.la

testbench_SOURCES = Clock.cpp Clock.hh testbench.cpp 
testbench_LDADD = $(top_builddir)/src/liblog4cpp.la
