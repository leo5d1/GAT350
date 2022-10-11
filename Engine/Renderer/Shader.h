#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"

namespace c14
{
	class Shader : public Resource
	{
	public:
		~Shader();

		virtual bool Create(const std::string filename, ...) override;

	public:
		GLuint m_shader = 0;
	};
}