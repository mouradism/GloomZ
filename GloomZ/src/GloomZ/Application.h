#pragma once
#include "Core.h"

namespace GloomZ {

	class GLOOMZ_API Application{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};


	//to be defined in the application side not the engine side
	Application* CreateApplication();
}


