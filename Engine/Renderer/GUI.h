#pragma once
#include "Renderer.h"
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>

namespace c14
{
	class GUI
	{
	public:
		GUI() = default;
		~GUI() = default;

		void Initialize(Renderer& renderer);
		void Shutdown();

		void BeginFrame(Renderer& renderer);
		void EndFrame();
		void Draw();

		void Update(SDL_Event& event);
	};
}
