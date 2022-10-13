#include "Engine.h"
#include <iostream>

float points[] = {
  -0.5f, -0.5f,  0.0f,
  -0.5f,  0.5f,  0.0f,
   0.5f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f,
   0.5f,  0.5f,  0.0f
};

glm::vec3 colors[] = {
	{0, 0, 1},
	{0, 1, 1},
	{1, 0, 1},
	{0, 1, 0},
	{1, 1, 0},
	{1, 0, 0}
};

int main(int argc, char** argv)
{
	c14::InitializeMemory();
	c14::SetFilePath("../Assets");

	c14::Engine::Instance().Initialize();
	c14::Engine::Instance().Register();

	c14::g_renderer.CreateWindow("Neumont", 800, 600, 0);

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	// creat color vertext buffer
	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	std::shared_ptr<c14::Shader> vs = c14::g_resources.Get<c14::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<c14::Shader> fs = c14::g_resources.Get<c14::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, vs->m_shader);
	glAttachShader(program, fs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);

	GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");

	glm::mat4 mx{ 1 };

	bool quit = false;
	while (!quit)
	{
		c14::Engine::Instance().Update();

		if (c14::g_inputSystem.GetKeyState(c14::key_escape) == c14::InputSystem::State::Pressed) quit = true;

		glUniform1f(uniform1, std::sin(c14::g_time.time));

		glUniform3f(uniform2, std::sin(c14::g_time.time * 5), std::sin(c14::g_time.time * 10), std::sin(c14::g_time.time * 20));

		mx = glm::eulerAngleXYZ(0.0f, 0.0f, c14::g_time.time);
		glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(mx));

		c14::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		c14::g_renderer.EndFrame();
	}

	c14::Engine::Instance().Shutdown();

	return 0;
}