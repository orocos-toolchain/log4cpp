#include <stdio.h>
#include <iostream>

#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/BasicLayout.hh"

#include "Clock.hh"


// -----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    int    count  = argc > 1 ? atoi(argv[1]) : 100;
    size_t size   = argc > 2 ? atoi(argv[2]) : 128;    

    std::cout << "  count: " << count << std::endl
	      << "   size: " << size  << " bytes" << std::endl
	      << std::endl;

    log4cpp::Category&	root	 = log4cpp::Category::getRoot();
    log4cpp::Layout*	layout	 = new log4cpp::BasicLayout();
    log4cpp::Appender*	appender = 
        new log4cpp::OstreamAppender("cerr", &std::cerr);
    log4cpp::Appender*	fileAppender = 
        new log4cpp::FileAppender("stderr", fileno(stderr));
    appender->setLayout(layout);
    fileAppender->setLayout(layout);
    root.setAppender(appender);
    root.setPriority(log4cpp::Priority::ERROR);    

    Clock  clock;
    char*  buffer = new char[size];
    
    memset(buffer, 'X', size);
    buffer[size - 1] = '\0';

    {	
	clock.start();
	for (int i = 0; i < count; i++) root.error("%s", buffer);    
	clock.stop();
	std::cout << "buffer ostream: " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }
    
    {
	std::string str(size, 'X');
	
	clock.start();
	for (int i = 0; i < count; i++) root.error(str);
	clock.stop();
	std::cout << "string ostream: " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	std::string str(size, 'X');
        root.setAppender(fileAppender);

	clock.start();
	for (int i = 0; i < count; i++) root.error(str);
	clock.stop();
	std::cout << "string file:    " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	clock.start();
	for (int i = 0; i < count; i++) fprintf(stderr, "%d ERROR  : %s\n", ::time(NULL), buffer);
	clock.stop();
	std::cout << "fprintf:        " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    log4cpp::Category::shutdown();

    return 0;
}
