/*
 * NTEventLogAppender.hh
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_NTEVENTLOGAPPENDER_HH
#define _LOG4CPP_NTEVENTLOGAPPENDER_HH

#ifdef WIN32	// only available on Win32

#include <log4cpp/Portability.hh>
#include <log4cpp/AppenderSkeleton.hh>

namespace log4cpp {

    /**
     * NTEventLogAppender is an Appender that sends LoggingEvents to the 
     * Windows event log.
     * Building log4cpp.dsp/log4cppDLL.dsp creates the resource DLL NTEventLogAppender.dll.
     * Do not forget to place this DLL in a directory that is on the PATH 
     * of the Windows system. Otherwise, the category and message will not display 
     * correctly in Event Viewer.<BR>
     * <B>NB:</B> This class is only available on Win32 platforms.
     **/
    class LOG4CPP_EXPORT NTEventLogAppender : public AppenderSkeleton {
    public:

        /**
         * Instantiate an NTEventLogAppender with given name and source.
         * @param name The name of the Appender
         * @param sourceName The source name to log
         **/         
        NTEventLogAppender(const std::string& name, const std::string& sourceName);
        virtual ~NTEventLogAppender();

        /**
         * Calls open() and close()
         **/
        virtual bool reopen();

        virtual void close();

        /**
         * The NTEventLogAppender does its own Layout.
         * @returns false
         **/
        virtual bool requiresLayout() const;

        virtual void setLayout(Layout* layout);

    protected:
        
        WORD getCategory(Priority::Value priority);
        WORD getType(Priority::Value priority);
        HKEY regGetKey(TCHAR *subkey, DWORD *disposition);
        void regSetString(HKEY hkey, TCHAR *name, TCHAR *value);
        void regSetDword(HKEY hkey, TCHAR *name, DWORD value);
        void addRegistryInfo(const char *source);

        virtual void open();

        /**
         * Sends a LoggingEvent to NT Event log.
         * @param event the LoggingEvent to log.
         **/
        virtual void _append(const LoggingEvent& event);

    	HANDLE _hEventSource;
        std::string _strSourceName;
    };
}

#else // WIN32
#error NTEventLoggAppender is not available on on Win32 platforms
#endif	// WIN32

#endif // _LOG4CPP_NTEVENTLOGAPPENDER_HH

