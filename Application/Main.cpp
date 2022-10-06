#include "Engine.h"
#include <iostream>

int main(int argc, char** argv)
{
	c14::InitializeMemory();

	c14::Engine::Instance().Initialize();
	c14::Engine::Instance().Register();

	c14::g_renderer.CreateWindow("Neumont", 800, 800, 0);

	float angle = 0;

	c14::Vector2 position;

	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;

		c14::g_renderer.BeginFrame();


		if (c14::g_inputSystem.GetKeyState(c14::key_left) == c14::InputSystem::State::Held) position.x -= c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_right) == c14::InputSystem::State::Held) position.x += c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_up) == c14::InputSystem::State::Held) position.y += c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_down) == c14::InputSystem::State::Held) position.y -= c14::g_time.deltaTime;

		angle += 90.0f * c14::g_time.deltaTime;

		glPushMatrix();

		glScalef(0.5f, 0.5f, 0.5f);
		//glRotatef(angle, 0, 0, 1);
		glTranslatef(position.x, position.y, 0);

		glBegin(GL_TRIANGLES);


		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);

		glEnd();

		glPopMatrix();

		c14::g_renderer.EndFrame();
	}

	c14::Engine::Instance().Shutdown();

	return 0;
}