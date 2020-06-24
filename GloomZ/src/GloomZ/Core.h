#pragma once

#ifdef GZ_PLATFORM_WINDOWS
	#ifdef GZ_BUILD_DLL
		#define GLOOMZ_API __declspec(dllexport)
	#else
		#define GLOOMZ_API __declspec(dllimport)
	#endif
#else
	#error GloomZ: only windows is supported! 


#endif