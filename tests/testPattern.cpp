// testLog4CPP.cpp : Derived from testCategory.cpp
//
#include "log4cpp/Portability.hh"
#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"
#include "log4cpp/PatternLayout.hh"

void test(std::string pattern, log4cpp::PatternLayout* layout, log4cpp::Category& cat)
{                                                                              
	if (! layout->setConversionPattern(pattern)) {
		std::cout << "bad pattern: \"" << pattern << '\"' << std::endl;
    }                                                                          
    cat.error("message");
}                                                                              

int main(int argc, char* argv[])
{
    log4cpp::Appender* appender = 
        new log4cpp::OstreamAppender("default", &std::cout);

    log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
    appender->setLayout(layout);

    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.removeAllAppenders();
    root.addAppender(appender);
       root.setPriority(log4cpp::Priority::ERROR);
    std::string pattern;
    
    test("%% %r %c:%d (%R / %r) [%p] %x %m %% (%u) %n", layout, root);

    // test date format
    test("%d{%d %b %Y %H:%M:%S.%l} %m %n", layout, root);
    test("%d{%d %b %Y %H:%M:%S.%l", layout, root);
    test("%d", layout, root);

    test("%m %d%n", layout, root);
    int i;
    for (i = 0; i < 1000; i++) {
        root.error("%d message", i);
    }
    test("%m %d{%d %b %Y %H:%M:%S.%l}%n", layout, root);
    for (i = 0; i < 1000; i++) {
        root.error("%d message", i);
    }

    log4cpp::Category::shutdown();

    return 0;
}

