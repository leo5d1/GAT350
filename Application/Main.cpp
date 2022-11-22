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

	// create framebuffer texture
	auto texture = std::make_shared<c14::Texture>();
	texture->CreateTexture(512, 512);
	c14::g_resources.Add<c14::Texture>("fb_texture", texture);

	// create framebuffer
	auto framebuffer = c14::g_resources.Get<c14::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();


	// load scene 
	auto scene = c14::g_resources.Get<c14::Scene>("Scenes/rtt.scn");

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 rot{ 0, 0, 0 };

	float ri = 1.0f;
	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();
		c14::g_gui.BeginFrame(c14::g_renderer);

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Model");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave
			//actor->m_transform.position = pos;
		}

		auto program = c14::g_resources.Get<c14::Program>("shaders/fx/refraction.prog");

		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}

		ImGui::Begin("Controls");
		//ImGui::SliderFloat3("Position", &pos[0], -5.0f, 5.0f);
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		//render pass 1 (render to framebuffer)
		glViewport(0, 0, 512, 512);
		framebuffer->Bind();
		c14::g_renderer.BeginFrame();
		scene->PreRender(c14::g_renderer);
		scene->Render(c14::g_renderer);
		framebuffer->Unbind();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(true);
			}
		}

		// render pass 2 (render to screen)
		glViewport(0, 0, 800, 600);
		c14::g_renderer.BeginFrame();
		scene->PreRender(c14::g_renderer);
		scene->Render(c14::g_renderer);

		c14::g_gui.Draw();

		c14::g_renderer.EndFrame();
		c14::g_gui.EndFrame();
	}

	scene->RemoveAll();
	c14::Engine::Instance().Shutdown();

	return 0;
}
