#pragma once

#ifdef GZ_PLATFORM_WINDOWS

extern GloomZ::Application* GloomZ::CreateApplication();

int main(int argc, char** argv) {

	auto app = GloomZ::CreateApplication();
	app->Run();
	delete app;
};



#endif

