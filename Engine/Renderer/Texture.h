#pragma once
#include "Math/Vector2.h"
#include "Resource/Resource.h"
#include "Renderer.h"
#include <string>

struct SDL_Texture;
struct SDL_Surface;

namespace c14
{
	class Renderer;
	
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(const std::string filename, ...) override;
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);
		bool Create(Renderer& renderer, const std::string& filename);

		void Bind() { glBindTexture(m_target, m_texture); }

		Vector2 GetSize() const;

		friend class Renderer;

	private:
		GLuint m_texture = 0;
		GLenum m_target = GL_TEXTURE_2D;
		GLuint m_unit = GL_TEXTURE0;
	};
}