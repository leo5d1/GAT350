#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"

namespace c14
{
	class Texture;

	class Framebuffer : public Resource
	{
	public:
		~Framebuffer();

		bool Create(std::string filename, ...) override;
		bool CreateFramebuffer();
		bool CreateDepthbuffer(int width, int height);

		void Bind();
		void Unbind();

	protected:
		GLuint m_fbo = 0;
		std::shared_ptr<Texture> m_texture;
	};
}