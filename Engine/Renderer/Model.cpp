#include "Model.h" 
#include "Core/Logger.h" 

namespace c14
{
    bool Model::Create(std::string filename, ...)
    {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            LOG("error loading assimp file %s", importer.GetErrorString());
            return false;
        }

        ProcessNode(scene->mRootNode, scene);

        return true;
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene)
    {
        // process the current node meshes 
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh, scene);
        }
        // process the current node children 
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<vertex_t> vertices;

        // get model vertex attributes 
        for (size_t i = 0; i < mesh->mNumVertices; i++)
        {
            vertex_t vertex;

            vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            if (mesh->mTextureCoords[0])
            {
                vertex.texcoord = { mesh->mTextureCoords[0][i].x, mesh -> mTextureCoords[0][i].y };
            }
            else
            {
                vertex.texcoord = { 0, 0 };
            }

            vertices.push_back(vertex);
        }

        // create vertex buffer and attributes 

        m_vertexBuffer.CreateVertexBuffer((GLsizei)(sizeof(vertex_t) * vertices.size()), (GLsizei)vertices.size(), vertices.data());
        m_vertexBuffer.SetAttribute(0, 3, sizeof(vertex_t), 0);
        m_vertexBuffer.SetAttribute(1, 2, sizeof(vertex_t), offsetof(vertex_t, texcoord));

        // get model index vertices 
        std::vector<GLuint> indices;
        for (size_t i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (size_t j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // create index vertex buffer 
        m_vertexBuffer.CreateIndexBuffer(GL_UNSIGNED_INT, (GLsizei)indices.size(), indices.data());
    }
}

//#include "Model.h"
//#include "Core/File.h"
//#include "Core/Logger.h"
//#include "Math/Transform.h"
//#include "Math/MathUtils.h"
//#include <sstream>
//#include <iostream>
//#include <cstdarg>
//
//namespace c14
//{
//	Model::Model(const std::string& filename)
//	{
//		Load(filename);
//		m_radius = CalculateRadius();
//	}
//
//	bool Model::Create(const std::string filename, ...)
//	{
//		if (!Load(filename))
//		{
//			LOG("Error could not create model %s", filename.c_str());
//			return false;
//		}
//
//		// va_list - type to hold information about variable arguments 
//		va_list args;
//
//		// va_start - enables access to variadic function arguments 
//		va_start(args, filename);
//
//		// va_arg - accesses the next variadic function arguments 
//		Renderer& renderer = va_arg(args, Renderer);
//
//		// va_end - ends traversal of the variadic function arguments 
//		va_end(args);
//
//		// create texture (returns true/false if successful) 
//		return true;
//	}
//
//	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale)
//	{
//		// draw model
//		for (size_t i = 0; i < m_points.size() - 1; i++)
//		{
//			c14::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
//			c14::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;
//
//			renderer.DrawLine(p1, p2, m_color);
//		}
//	}
//
//	void Model::Draw(Renderer& renderer, const Transform& transform)
//	{
//		/*
//		Matrix3x3 mx = transform.matrix;
//		//if (m_points.size() == 0) return;
//
//		// draw model
//		for (size_t i = 0; i < m_points.size() - 1; i++)
//		{
//			c14::Vector2 p1 = mx * m_points[i];
//			c14::Vector2 p2 = mx * m_points[i + 1];
//
//			renderer.DrawLine(p1, p2, m_color);
//		}
//		*/
//	}
//
//	bool Model::Load(const std::string& filename)
//	{
//		std::string buffer;
//		
//		if (!c14::ReadFile(filename, buffer))
//		{
//			LOG("Error could not read file &s", filename.c_str());
//			return false;
//		}
//
//		// read color
//		std::istringstream stream(buffer);
//		stream >> m_color;
//
//		// read num of points
//		std::string line;
//		std::getline(stream, line);
//
//		size_t numPoints = std::stoi(line);
//
//		// read model points
//		for (size_t i = 0; i < numPoints; i++)
//		{
//			Vector2 point;
//
//			stream >> point;
//
//			m_points.push_back(point);
//		}
//
//		std::cout << line << std::endl;
//
//		return true;
//	}
//
//	float Model::CalculateRadius()
//	{
//		float radius = 0;
//
//		// find the largest length (radius)
//		for (auto& point : m_points)
//		{
//			if (point.Length() > radius) radius = point.Length();
//		}
//
//		return radius;
//	}
//}
