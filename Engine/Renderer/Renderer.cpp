#include "Renderer.h" 
#include "Texture.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


namespace c14
{
	void Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();

		m_view = Matrix3x3::identity;
		m_viewport = Matrix3x3::identity;
	}
	
	void Renderer::Shutdown()
	{

		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		IMG_Quit();
		TTF_Quit();
	}
	
	void Renderer::CreateWindow(const char* name, int width, int height, bool fullscreen)
	{
		m_width = width;
		m_height = height;

		int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		m_window = SDL_CreateWindow(name, 100, 100, width, height, SDL_WINDOW_OPENGL | flags);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetSwapInterval(1);

		m_context = SDL_GL_CreateContext(m_window);
		gladLoadGL();

		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void Renderer::BeginFrame()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void Renderer::EndFrame()
	{
		SDL_GL_SwapWindow(m_window);
	}

	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawLine(const Vector2& v1, const Vector2& v2, const Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(m_renderer, v1.x, v1.y, v2.x, v2.y);
	}

	void Renderer::DrawPoint(float x, float y)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawPointF(m_renderer, x, y);
	}

	void Renderer::DrawPoint(const Vector2& v, const Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(m_renderer, v.x, v.y);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle, const Vector2& scale, const Vector2& registration)
	{
		Vector2 size = texture->GetSize();
		size = size * scale;

		Vector2 origin = size * registration;
		Vector2 tposition = position - origin;

		SDL_Rect dest;
		dest.x = (int)tposition.x;
		dest.y = (int)tposition.y;
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, angle, &center, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration)
	{
		Vector2 size = texture->GetSize();
		size = size * transform.scale;

		Vector2 origin = size * registration;
		Vector2 tposition = transform.position - origin;

		SDL_Rect dest;
		dest.x = (int)tposition.x;
		dest.y = (int)tposition.y;
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, transform.rotation, &center, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& registration, bool flipH)
	{
		Matrix3x3 mx = m_viewport * m_view * transform.matrix;

		Vector2 size = { source.w, source.h };
		size = size * mx.GetScale();

		Vector2 origin = size * registration;
		Vector2 tposition = mx.GetTranslation() - origin;

		SDL_Rect dest;
		dest.x = (int)tposition.x;
		dest.y = (int)tposition.y;
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Rect src;
		src.x = source.x;
		src.y = source.y;
		src.w = source.w;
		src.h = source.h;

		SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_RendererFlip flip = (flipH) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(m_renderer, texture->m_texture, &src, &dest, math::RadToDeg(mx.GetRotation()), &center, flip);
	}
}