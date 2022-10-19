#include "Material.h" 
#include "Engine.h" 

namespace c14
{
	bool Material::Create(std::string filename, ...)
	{
		// load program json document 
		rapidjson::Document document;
		bool success = c14::json::Load(filename, document);
		if (!success)
		{
			LOG("Could not load program file (%s).", filename.c_str());
			return false;
		}

		// read the program name 
		std::string program;
		READ_DATA(document, program);
		// get program resource 
		m_program = c14::g_resources.Get<c14::Program>(program);

		// read the texture name 
		std::string texture;
		READ_DATA(document, texture);
		if (!texture.empty())
		{
			// get texture resource 
			m_textures.push_back(c14::g_resources.Get<c14::Texture>(texture));
		}

		// read colors 
		READ_DATA(document, ambient);
		READ_DATA(document, diffuse);
		READ_DATA(document, specular);
		READ_DATA(document, shininess);

		return true;
	}

	void Material::Bind()
	{
		m_program->Use();
		for (auto& texture : m_textures)
		{
			texture->Bind();
		}
	}
}