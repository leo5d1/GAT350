#include "FrameBuffer.h"
#include "Engine.h"

namespace c14
{
	Framebuffer::~Framebuffer()
	{
		if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
	}

	bool Framebuffer::Create(std::string filename, ...)
	{
		// va_list - type to hold information about variable arguments
		va_list args;

		// va_start - enables access to variadic function arguments
		va_start(args, filename);

		// va_arg - accesses the next variadic function arguments
		const char* textureName = va_arg(args, const char*);

		// va_end - ends traversal of the variadic function arguments
		va_end(args);

		// get texture resource
		m_texture = g_resources.Get<Texture>(textureName);
		m_texture->Bind();

		m_width = m_texture->m_width;
		m_height = m_texture->m_height;

		return CreateFramebuffer();
	}

	bool Framebuffer::CreateFramebuffer()
	{
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		// create the depth buffer (bind)
		CreateDepthbuffer(m_texture->GetSize().x, m_texture->GetSize().y);

		// bind the texture to the FBO
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->m_texture, 0);

		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (result != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG("Error creating frame buffer.");
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

	bool Framebuffer::CreateDepthbuffer(int width, int height)
	{
		GLuint depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (result != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG("Error creating depth buffer.");
			return false;
		}

		return true;
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void Framebuffer::Unbind()
	{
		glFlush();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}