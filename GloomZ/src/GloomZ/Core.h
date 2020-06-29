#pragma once

#ifdef GL_PLATFORM_WINDOWS
	#ifdef GL_BUILD_DLL
		#define GLOOMZ_API __declspec(dllexport)
	#else
		#define GLOOMZ_API __declspec(dllimport)
	#endif
#else
	#error GloomZ: only windows is supported! 


#endif