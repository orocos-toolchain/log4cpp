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

double calcPi()                                                                
{                                                                              
  double denominator = 3.0;                                                    
  double retVal = 4.0;                                                         
  long i;                                                                      
  for (i = 0; i < 50000000l; i++)                                              
    {                                                                          
      retVal = retVal - (4.0 / denominator);                                   
      denominator += 2.0;                                                      
      retVal = retVal + (4.0 /denominator);                                    
      denominator += 2.0;                                                      
    }                                                                          
  return retVal;                                                               
}                                                                              

int main(int argc, char* argv[])
{
    log4cpp::Appender* appender = 
        new log4cpp::OstreamAppender("default", &std::cout);

    log4cpp::Layout* layout = new log4cpp::PatternLayout();
	bool success = ((log4cpp::PatternLayout *)layout)->setConversionPattern("%% %r %c:%d (%R / %r) [%p] %x %m %% (%u) %n");
	if (!success)
	{
		std::cout << "Problem" << std::endl;
		return -1;
	}
    appender->setLayout(layout);

    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.addAppender(appender);
       root.setPriority(log4cpp::Priority::ERROR);
    
    log4cpp::Category& sub1 = 
        log4cpp::Category::getInstance(std::string("sub1"));

    log4cpp::Category& sub2 = 
        log4cpp::Category::getInstance(std::string("sub1.sub2"));

/*    std::cout << " root priority = " << root.getPriority() << std::endl;
    std::cout << " sub1 priority = " << sub1.getPriority() << std::endl;
    std::cout << " sub2 priority = " << sub2.getPriority() << std::endl;*/
    
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

    calcPi();

    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    
       sub1.setPriority(log4cpp::Priority::INFO);
    /*std::cout << " root priority = " << root.getPriority() << std::endl;
    std::cout << " sub1 priority = " << sub1.getPriority() << std::endl;
    std::cout << " sub2 priority = " << sub2.getPriority() << std::endl;*/
   
//    std::cout << "priority info" << std::endl;
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

#ifdef WIN32
	Sleep(3000);
#else
	sleep(3);
#endif

    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    sub2.error("%s %s %d", "test", "vform", 123);
    sub2.warnStream() << "streamed warn";

    sub2 << log4cpp::Priority::WARN << "warn2.." << "..warn3..value=" << 0 << 
        log4cpp::CategoryStream::ENDLINE << "..warn4";

    log4cpp::Category::shutdown();

    return 0;
}

