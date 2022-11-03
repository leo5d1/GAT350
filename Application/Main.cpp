#include "Engine.h"
#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
	LOG("Application Started...");

	c14::InitializeMemory();
	c14::SetFilePath("../Assets");

	c14::Engine::Instance().Initialize();
	c14::Engine::Instance().Register();

	LOG("Engine Initialized...");

	c14::g_renderer.CreateWindow("Gamer", 800, 600, 0);

	LOG("Window Initialized...");

	// load scene 
	auto scene = c14::g_resources.Get<c14::Scene>("Scenes/texture.scn");

	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			//actor->m_transform.rotation.x += c14::g_time.deltaTime * 45.0f;
			//actor->m_transform.rotation.y += c14::g_time.deltaTime * 45.0f;
		}

		auto light = scene->GetActorFromName("Light");
		if (light)
		{
			//light->m_transform.rotation.y += c14::g_time.deltaTime * 90.0f;
		}

		auto material = c14::g_resources.Get<c14::Material>("Materials/multi.mtrl");
		if (material)
		{
			//material->uv_offset.x += c14::g_time.deltaTime;
		}

		scene->Update();

		c14::g_renderer.BeginFrame();

		scene->Draw(c14::g_renderer);

		c14::g_renderer.EndFrame();
	}

	scene->RemoveAll();
	c14::Engine::Instance().Shutdown();

	return 0;
}
