#include "GUI.h"

namespace c14
{
	void GUI::Initialize(Renderer& renderer)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplSDL2_InitForOpenGL(renderer.m_window, renderer.m_context);
		const char* glsl_version = "#version 430";
		ImGui_ImplOpenGL3_Init(glsl_version);

		ImGui::StyleColorsDark();
	}

	void GUI::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void GUI::BeginFrame(Renderer& renderer)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		//ImGui_ImplSDL2_NewFrame(renderer.m_window);
		ImGui::NewFrame();
	}

	void GUI::EndFrame()
	{
		ImGui::EndFrame();
	}

	void GUI::Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::Update(SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}
}