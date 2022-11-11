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

	c14::g_gui.Initialize(c14::g_renderer);

	// load scene 
	auto scene = c14::g_resources.Get<c14::Scene>("Scenes/texture.scn");

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 rot{ 0, 0, 0 };

	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();
		c14::g_gui.BeginFrame(c14::g_renderer);

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation = rot;
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave
			actor->m_transform.position = pos;
		}

		ImGui::Begin("Controls");
		ImGui::Button("Press Me!");
		ImGui::SliderFloat3("Position", &pos.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Rotation", &rot.x, -180.0f, 180.0f);
		ImGui::End();

		scene->Update();

		c14::g_renderer.BeginFrame();

		scene->Draw(c14::g_renderer);
		c14::g_gui.Draw();

		c14::g_renderer.EndFrame();
		c14::g_gui.EndFrame();
	}

	scene->RemoveAll();
	c14::Engine::Instance().Shutdown();

	return 0;
}
