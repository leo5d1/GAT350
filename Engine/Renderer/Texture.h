#pragma once 
#include "Math/MathUtils.h" 
#include "Resource/Resource.h" 
#include "Renderer.h" 
#include <string> 

// !! forward declaration for SDL pointers (SDL likes to use structs instead of classes)
struct SDL_Texture;
struct SDL_Surface;

namespace c14
{
	// !! forward declaration for Renderer 
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string filename, ...) override;
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);
		bool CreateTexture(int width, int height);
		bool CreateDepthTexture(int width, int height);

		bool Load(const std::string& filename);

		void SetActive(GLuint unit) { glActiveTexture(unit); }
		void Bind() { glBindTexture(m_target, m_texture); }

		static GLenum GetInternalFormat(GLuint format);

		glm::ivec2 GetSize() const;

		friend class Renderer;
		friend class Framebuffer;

	protected:
		void FlipSurface(SDL_Surface* surface);


	protected:
		GLuint m_texture = 0;
		GLenum m_target = GL_TEXTURE_2D;

		int m_width = 0;
		int m_height = 0;
	};
}