#include "Shader.h"
#include "Core/File.h"
#include "Core/Logger.h"

namespace c14
{
	Shader::~Shader()
	{
		if (!m_shader)
		{
			glDeleteShader(m_shader);
		}
	}

	bool Shader::Create(const std::string filename, ...)
	{
		// get shader source from file
		std::string source;
		bool success = ReadFile(filename, source);
		if (!success)
		{
			LOG("error reading shader file %s.", filename.c_str());
			return false;
		}

		// get shader type arguments
		va_list args;
		va_start(args, filename);
		GLuint shaderType = va_arg(args, GLuint);
		va_end(args);

		// create shader
		m_shader = glCreateShader(shaderType);

		// compile shader
		const char* source_c = source.c_str();
		glShaderSource(m_shader, 1, &source_c, NULL);
		glCompileShader(m_shader);

		// check shader compilation status
		GLint status;
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			// display shader error
			GLint length = 0;
			glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &length);

			if (length > 0)
			{
				std::string infoLog(length, ' ');
				glGetShaderInfoLog(m_shader, length, &length, &infoLog[0]);
				LOG("failed to compile shader %s.", filename.c_str());
				LOG("shader info: %s", infoLog.c_str());
			}

			// delete shader
			glDeleteShader(m_shader);
			m_shader = 0;
		}

		return true;
	}
}