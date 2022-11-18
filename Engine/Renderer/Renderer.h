#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Matrix3x3.h"
#include "Math/MathUtils.h"
#include <glad/glad.h>
#include <SDL.h>

struct SDL_Renderer;
struct SDL_Window;

namespace c14
{
	class Texture;
	struct Transform;
	struct Rect;

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		void Initialize();
		void Shutdown();

		void CreateWindow(const char* name, int width, int height, bool fullscreen);
		void BeginFrame();
		void EndFrame();

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLine(const Vector2& v1, const Vector2& v2, const Color& color);
		void DrawPoint(float x, float y);
		void DrawPoint(const Vector2& v, const Color& color);

		void Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle = 0, const Vector2& scale = Vector2{ 1, 1 }, const Vector2& registration = Vector2{ 0.5f, 0.5f });
		void Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration = Vector2{ 0.5f, 0.5f });
		void Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& registration = Vector2{ 0.5f, 0.5f }, bool flipH = false);

		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }

		const glm::mat4& GetView() { return m_view; }
		void SetView(const glm::mat4& view) { m_view = view; }

		const glm::mat4& GetProjection() { return m_projection; }
		void SetProjection(const glm::mat4& projection) { m_projection = projection; }

		friend class Text;
		friend class Texture;
		friend class GUI;

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;
		SDL_GLContext m_context;

		glm::mat4 m_view{ 1 };
		glm::mat4 m_projection{ 1 };
		
	public:
		glm::vec3 clear_color{ 0, 0, 0 };
		glm::vec3 ambient_color{ 0, 0, 0 };
	};	
}