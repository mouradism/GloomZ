#include <GloomZ.h>

class Sandbox : public GloomZ::Application {
public:
	Sandbox() {
		GL_CORE_WARN(" --- new Sandbox App created // constuctor call ----:");
		//std::cout << "new Sandbox App created // constuctor call" << std::endl;
	}

	~Sandbox() {

	}

};

GloomZ::Application* GloomZ::CreateApplication() {
	return new Sandbox();
}