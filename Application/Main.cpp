#include "Engine.h"
#include <vector>
#include <iostream>

#define POST_PROCESS

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
	texture->CreateTexture(1024, 1024);
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

		/*auto program = c14::g_resources.Get<c14::Program>("shaders/postprocess/postprocess.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("offset", c14::g_time.time);
		}*/

		ImGui::Begin("Controls");
		//ImGui::SliderFloat3("Position", &pos[0], -5.0f, 5.0f);
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS 
		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		c14::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		c14::g_renderer.BeginFrame();
		scene->PreRender(c14::g_renderer);
		scene->Render(c14::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		c14::g_renderer.RestoreViewport();
		c14::g_renderer.BeginFrame();
		scene->PreRender(c14::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(c14::g_renderer);
			}
		}
#else 
		c14::g_renderer.BeginFrame();
		scene->PreRender(c14::g_renderer);
		scene->Render(c14::g_renderer);
#endif // POST_PROCESS 

		c14::g_gui.Draw();

		c14::g_renderer.EndFrame();
		c14::g_gui.EndFrame();
	}

	scene->RemoveAll();
	c14::Engine::Instance().Shutdown();

	return 0;
}
