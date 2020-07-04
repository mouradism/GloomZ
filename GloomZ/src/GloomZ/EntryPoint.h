#pragma once

#ifdef GL_PLATFORM_WINDOWS

extern GloomZ::Application* GloomZ::CreateApplication();

int main(int argc, char** argv) {

	//----log system------
	GloomZ::Log::Init();

	GL_CORE_WARN("testing log core  : --------- : ");
	GL_CLNT_INFO("testing log client: --------- : ");

	//----  THE APP  ------
	auto app = GloomZ::CreateApplication();
	app->Run();
	delete app;

};

#endif

