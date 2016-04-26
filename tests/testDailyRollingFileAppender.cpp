#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/DailyRollingFileAppender.hh>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>

#ifdef WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

using namespace log4cpp;
using namespace std;
static const char* const test_message = "message";
static const char* const daily_file_prefix = "dailyrolling_file.log";
static const char* const nestedDir = "nesteddir";
#ifndef WIN32 
#define PATHDELIMITER "/" 
#else 
#define PATHDELIMITER "\\"
#endif
const char* const nesteddirname = "nesteddir"PATHDELIMITER;


class DailyRollingTest {
	DailyRollingFileAppender* dailyApp, *nestedDirDailyApp;
public:
	bool remove_impl(const char* filename)
	{
	   int res = remove(filename);

	   if (res != 0 && errno != ENOENT)
		  cout << "Can't remove file '" << filename << "'.\n";

	   return res == 0 || (res != 0 && errno == ENOENT);
	}

	bool remove_files()
	{
//	   if (!remove_impl(daily_file_prefix))
//		  return false;

	   return true;
	}

	bool setup()
	{
	   if (!remove_files())
		  return false;

	   Category& root = Category::getRoot();
	   dailyApp = new DailyRollingFileAppender("daily-rolling-appender", daily_file_prefix, 1);
	   nestedDirDailyApp = new DailyRollingFileAppender("nesteddir-daily-rolling-appender", std::string(nesteddirname).append(daily_file_prefix), 1);
	   root.addAppender(dailyApp);
	   root.addAppender(nestedDirDailyApp);
	   root.setPriority(Priority::DEBUG);

	   return true;
	}

	void make_log_files()
	{
	   Category::getRoot().debugStream() << test_message << 1;
	   Category::getRoot().debugStream() << test_message << 2;
	   Category::getRoot().debugStream() << test_message << 3;
	   Category::getRoot().debugStream() << "The message before rolling over attempt";
	   dailyApp->rollOver();
	   nestedDirDailyApp->rollOver();
	   Category::getRoot().debugStream() << "The message after rolling over attempt";
	   Category::getRoot().debugStream() << test_message << 4;
	   Category::getRoot().debugStream() << test_message << 5;
	}

	bool exists(const char* filename)
	{
	   FILE* f = fopen(filename, "r");
	   if (f == NULL)
	   {
		  cout << "File '" << filename << "' doesn't exists.\n";
		  return false;
	   }

	   fclose(f);

	   return true;
	}

	bool check_log_files()
	{
	   bool result = exists(daily_file_prefix);

	   Category::shutdown();
	   return result && remove_files();
	}
};

int testOnlyDailyRollingFileAppender() {
	DailyRollingTest dailyTest;
	   if (!dailyTest.setup())
	   {
	      cout << "Setup has failed. Check for permissions on files " << daily_file_prefix << "*'.\n";
	      return -1;
	   }

	   dailyTest.make_log_files();

	   if (dailyTest.check_log_files())
	      return 0;
	   else
	      return -1;
}

int testConfigDailyRollingFileAppender()
{
		/* looking for the init file in $srcdir is a requirement of
		   automake's distcheck target.
		*/
		const char* srcdir = getenv("srcdir");
		std::string initFileName;
	   try {
#if defined(WIN32)
        initFileName = "./testConfig.log4cpp.dailyroll.nt.properties";
#else
        initFileName = "./testConfig.log4cpp.dailyroll.properties";
#endif
			if (srcdir != NULL) {
	            initFileName = std::string(srcdir) + PATHDELIMITER + initFileName;
	        }

	        log4cpp::PropertyConfigurator::configure(initFileName);
	    } catch(log4cpp::ConfigureFailure& f) {
	        std::cout << "Configure Problem " << f.what() << "($srcdir=" << ((srcdir != NULL)?srcdir:"NULL") << ")" << std::endl;
	        return -1;
	    }

	    log4cpp::Category& root = log4cpp::Category::getRoot();

	    log4cpp::Category& sub1 =
	        log4cpp::Category::getInstance(std::string("sub1"));

	    root.error("root error");
	    root.warn("root warn");
	    sub1.error("sub1 error");
	    sub1.warn("sub1 warn");

	    log4cpp::Category::shutdown();
	    return 0;
}

int main()
{
	int res = testOnlyDailyRollingFileAppender();
	if (!res)
		res = testConfigDailyRollingFileAppender();

	return res;
}
