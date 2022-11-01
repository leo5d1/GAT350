#pragma once
#include "Renderer.h" 
#include "VertexBuffer.h" 
#include "Math/MathUtils.h" 

#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h> 

namespace c14
{
	class Model : public Resource
	{
	public:
		struct vertex_t
		{
			glm::vec3 position;
			glm::vec2 texcoord;
			glm::vec3 normal;
		};

	public:
		bool Create(std::string filename, ...) override;

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	public:
		VertexBuffer m_vertexBuffer;
	};
}