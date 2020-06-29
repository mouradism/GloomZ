#pragma once

#ifdef GZ_PLATFORM_WINDOWS

extern GloomZ::Application* GloomZ::CreateApplication();

int main(int argc, char** argv) {
	GloomZ::Log::Init();
	int a = 10;
	GL_CORE_WARN("Initialized core  : --------- : Var={0}",a);
	GL_CLNT_INFO("Initialized client: --------- : ");

	auto app = GloomZ::CreateApplication();
	app->Run();
	delete app;
};



#endif

