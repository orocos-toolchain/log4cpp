#include <stdio.h>
#include <unistd.h>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"

int main(int argc, char** argv) {    
    log4cpp::FileAppender* appender;

    if (argc < 2) {
        appender = new log4cpp::FileAppender("default", dup(STDERR_FILENO));
    } else {
        appender = new log4cpp::FileAppender("default", argv[1]);
    }
    log4cpp::Layout* layout = new log4cpp::BasicLayout();
    appender->setLayout(layout);

    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.setAppender(appender);
    root.setPriority(log4cpp::Priority::ERROR);
    
    log4cpp::Category& sub1 = log4cpp::Category::getInstance("sub1");
    log4cpp::Category& sub2 = log4cpp::Category::getInstance("sub1.sub2");

    log4cpp::NDC::push("ndc1");

    cout << " root prio = " << root.getPriority() << endl;
    cout << " sub1 prio = " << sub1.getPriority() << endl;
    cout << " sub2 prio = " << sub2.getPriority() << endl;
    
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    
    sub1.setPriority(log4cpp::Priority::INFO);
    cout << " root prio = " << root.getPriority() << endl;
    cout << " sub1 prio = " << sub1.getPriority() << endl;
    cout << " sub2 prio = " << sub2.getPriority() << endl;
   
    cout << "priority info" << endl;
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    
    {
        for(int i = 0; i < 10000; i++) {
            char ndc2[20];
            sprintf(ndc2, "i=%d", i);
            log4cpp::NDC::push(ndc2);
            sub1.info("%s%d", "i = ", i);
            if ((i % 10) == 0) {
                sub1.log(log4cpp::Priority::NOTICE, "reopen log");
                if (log4cpp::Appender::reopenAll()) {
                    sub1.info("log reopened");
                } else {
                    sub1.warn("could not reopen log");
                }
            }
            sleep(1);
            log4cpp::NDC::pop();
        }
    }
}
