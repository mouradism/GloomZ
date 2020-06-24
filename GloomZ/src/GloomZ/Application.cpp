#include "Application.h"
#include <cstdio>

namespace GloomZ {
	Application::~Application() {

	}

	Application::Application() {

	}

	void Application::Run() {
		printf("  ----> GLOOMZ ENGINE  \n\n");
		bool x = true;
		while (x) {
			for (int i = 1; i < 10; i++) {
				printf("---------********gloommmmmz is running*******------ \n");
			}
				
			x = false;
		};
	}
}
