#include "Engine.h"
#include <iostream>

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc, char** argv)
{
	LOG("Application Started...");

	c14::InitializeMemory();
	c14::SetFilePath("../Assets");

	c14::Engine::Instance().Initialize();
	c14::Engine::Instance().Register();

	LOG("Engine Initialized...");

	c14::g_renderer.CreateWindow("c14", 800, 600, 0);

	LOG("Window Initialized...");


	// create vertex buffer
	std::shared_ptr<c14::VertexBuffer> vb = c14::g_resources.Get<c14::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	// create program
	std::shared_ptr<c14::Program> program = c14::g_resources.Get<c14::Program>("Shaders/basic.prog", GL_PROGRAM);
	program->Link();
	program->Use();

	// create material 
	std::shared_ptr<c14::Material> material = c14::g_resources.Get<c14::Material>("materials/box.mtrl");
	material->Bind();

 	material->GetProgram()->SetUniform("scale", 0.5f);
	material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, c14::g_renderer.GetWidth() / (float)c14::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition{ 0, 0, 1 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;

		// add input to move camera
		if (c14::g_inputSystem.GetKeyState(c14::key_a) == c14::InputSystem::State::Held) cameraPosition.x -= speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_d) == c14::InputSystem::State::Held) cameraPosition.x += speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_w) == c14::InputSystem::State::Held) cameraPosition.y += speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_s) == c14::InputSystem::State::Held) cameraPosition.y -= speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_LShift) == c14::InputSystem::State::Held) cameraPosition.z -= speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_LCtrl) == c14::InputSystem::State::Held) cameraPosition.z += speed * c14::g_time.deltaTime;


		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		model = glm::eulerAngleXYZ(0.0f, c14::g_time.time, 0.0f);
		glm::mat4 mvp = projection * view * model;
		material->GetProgram()->SetUniform("mvp", mvp);

		c14::g_renderer.BeginFrame();

		vb->Draw();

		c14::g_renderer.EndFrame();
	}

	c14::Engine::Instance().Shutdown();

	return 0;
}
