#include "Engine.h"
#include <iostream>

//testing stuff

int main(int argc, char** argv)
{
	c14::InitializeMemory();

	c14::Engine::Instance().Initialize();
	c14::Engine::Instance().Register();

	c14::g_renderer.CreateWindow("Neumont", 800, 600, 0);

	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;

		c14::g_renderer.BeginFrame();

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();

		c14::g_renderer.EndFrame();
	}

	c14::Engine::Instance().Shutdown();

	return 0;
}