#ifndef _LOG4CPP_EXPORT_HH
#define _LOG4CPP_EXPORT_HH

#ifdef LOG4CPP_HAS_DLL
#	ifdef LOG4CPP_BUILD_DLL
#		define LOG4CPP_EXPORT __declspec(dllexport)
#	else
#		define LOG4CPP_EXPORT __declspec(dllimport)
#	endif
#else
#	define LOG4CPP_EXPORT 
#endif

#endif // _LOG4CPP_EXPORT_HH

