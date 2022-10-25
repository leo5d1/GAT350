#include "Engine.h"
#include <vector>
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

	// load scene 
	auto scene = std::make_unique<c14::Scene>();

	rapidjson::Document document;
	bool success = c14::json::Load("scenes/basic.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scenes/basic.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}

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

	auto ogre = c14::g_resources.Get<c14::Model>("models/ogre.obj");
	auto spot = c14::g_resources.Get<c14::Model>("models/spot.obj");

	// create material 
	//std::shared_ptr<c14::Material> material = c14::g_resources.Get<c14::Material>("materials/ogre.mtrl");
	std::shared_ptr<c14::Material> material = c14::g_resources.Get<c14::Material>("materials/spot.mtrl");
	material->Bind();

 	material->GetProgram()->SetUniform("scale", 0.5f);
	material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	
	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, c14::g_renderer.GetWidth() / (float)c14::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition{ 0, 0, 2 };
	float speed = 3;

	std::vector<c14::Transform> transforms;
	/*
	for (int i = 0; i < 100; i++)
	{
		transforms.push_back({ {c14::Randomf(-5, 5), c14::Randomf(-5, 5), c14::Randomf(-5, 5) }, {c14::Randomf(360), c14::Randomf(360), c14::Randomf(360)} });
	}
	*/

	transforms.push_back({ { 0, 0, 0}, {0, 180, 0} });

	/*c14::Transform transforms[] =
	{
		{ { 0, 0,  0}, {45, 90, 0} },
		{ { 1, 2,  0}, {0, 90, 45} },
		{ { 0, 4, -3}, {0, 90, 30} },
		{ {-2, 0,  3}, {90, 90, 0} },
	};*/

	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;
		
		// add input to move camera
		if (c14::g_inputSystem.GetKeyState(c14::key_d) == c14::InputSystem::State::Held) cameraPosition.x += speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_a) == c14::InputSystem::State::Held) cameraPosition.x -= speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_w) == c14::InputSystem::State::Held) cameraPosition.y += speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_s) == c14::InputSystem::State::Held) cameraPosition.y -= speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_LCtrl) == c14::InputSystem::State::Held) cameraPosition.z += speed * c14::g_time.deltaTime;
		if (c14::g_inputSystem.GetKeyState(c14::key_LShift) == c14::InputSystem::State::Held) cameraPosition.z -= speed * c14::g_time.deltaTime;


		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		scene->Update();

		c14::g_renderer.BeginFrame();

		scene->Draw(c14::g_renderer);

		c14::g_renderer.EndFrame();
	}

	scene->RemoveAll();
	c14::Engine::Instance().Shutdown();

	return 0;
}
