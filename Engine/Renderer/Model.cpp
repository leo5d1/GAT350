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
            vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
            vertex.tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };

            if (mesh->mTangents)
            {
                vertex.tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
            }
            else
            {
                vertex.tangent = { 0, 0, 0 };
            }

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
        m_vertexBuffer.SetAttribute(2, 3, sizeof(vertex_t), offsetof(vertex_t, normal));
        m_vertexBuffer.SetAttribute(3, 3, sizeof(vertex_t), offsetof(vertex_t, tangent));

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