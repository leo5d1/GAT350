#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL.h>
#include <SDL_image.h>

namespace c14
{
	Texture::~Texture()
	{
		if (m_texture != NULL)
		{
			SDL_DestroyTexture(m_texture);
		}
	}

	bool Texture::Create(const std::string filename, ...)
	{
		// va_list - type to hold information about variable arguments 
		va_list args;

		// va_start - enables access to variadic function arguments 
		va_start(args, filename);

		// va_arg - accesses the next variadic function arguments 
		Renderer& renderer = va_arg(args, Renderer);

		// va_end - ends traversal of the variadic function arguments 
		va_end(args);

		return Create(renderer, filename);
	}

	bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
	{
		// destroy current texture if it exists
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}

		// create texture
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

		SDL_FreeSurface(surface);

		if (!m_texture)
		{
			LOG(SDL_GetError());
			return false;
		}

		return true;
	}

	bool Texture::Create(Renderer& renderer, const std::string& filename)
	{
		// load surface
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (surface == nullptr)
		{
			LOG(SDL_GetError());
			return false;
		}


		// create texture
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (m_texture == nullptr)
		{
			LOG(SDL_GetError());
			SDL_FreeSurface(surface);

			return false;
		}

		SDL_FreeSurface(surface);

		return true;
	}
	
	Vector2 Texture::GetSize() const
	{
		SDL_Point point;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

		return Vector2(point.x, point.y);
	}


}
