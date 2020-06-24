#include <GloomZ.h>

class Sandbox : public GloomZ::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}

};

GloomZ::Application* GloomZ::CreateApplication() {
	return new Sandbox();
}