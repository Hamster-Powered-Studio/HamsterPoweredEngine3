#include "Model.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Material.h"
#include "ShaderLoader.h"

using namespace Hamster;

Model::Model(std::string path)
{
    LoadModel(path);
}

/*
void Model::Draw(const glm::mat4& parentTransform)
{
    for (auto& mesh : meshes)
    {
        mesh.first.Draw(parentTransform * GetTransform());
    }
}
*/

void Model::SetMaterial(std::shared_ptr<Material> _material, int _index)
{
    for (auto& mesh : meshes)
    {
        if (mesh.second == _index || _index == -1)
        {
            mesh.first.SetMaterial(_material);
        }
    }
}

const std::shared_ptr<Material>& Model::GetMaterial(int index)
{
    return meshes[index].first.GetMaterial();
}

Model::~Model()
{
    meshes.clear();
}

void Model::LoadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_RemoveRedundantMaterials);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    //TODO: fbx will be scaled down by default (blender)
    float scaleFactor = 1.0f;
    if (path.find(".fbx") != std::string::npos || path.find(".FBX") != std::string::npos)
    {
        scaleFactor = 0.01f;
    }
    
    
    directory = path.substr(0, path.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene, glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor)));
    
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform)
{
    aiMatrix4x4 t = node->mTransformation;
    glm::mat4 worldTransform(
        t.a1, t.b1, t.c1, t.d1,
        t.a2, t.b2, t.c2, t.d2,
        t.a3, t.b3, t.c3, t.d3,
        t.a4, t.b4, t.c4, t.d4
    );

    worldTransform = parentTransform * worldTransform;
    
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        auto inst = meshes.emplace_back(ProcessMesh(mesh, scene), mesh->mMaterialIndex);
        inst.first.SetTransform(worldTransform);
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        ProcessNode(node->mChildren[i], scene, worldTransform);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<GLHandle<Texture2D>> textures;
    
    
    //Process Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
        if (mesh->mTextureCoords[0])
        {
            vertex.TexCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
        }
        if (mesh->mColors[0])
        {
            vertex.Colour = { mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a };
        }
        vertices.push_back(vertex);
    }

    //Process Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }


    auto meshObj = Mesh(vertices, indices);

    // Process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        
        std::vector<GLHandle<Texture2D>> diffuseMaps = LoadMaterialTextures(material,
            aiTextureType_DIFFUSE, "texture_diffuse");

        std::shared_ptr<Material> mat = std::make_shared<Material>(ShaderLoader::Load("Resources/Shaders/BasicLit.glsl"));
        if (diffuseMaps.size() > 0) mat->SetParameter("uTexture", diffuseMaps[0]);
        
        meshObj.SetMaterial(mat);
    }

    return meshObj;
}

std::vector<GLHandle<Texture2D>> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
    std::string typeName)
{
    
    std::vector<GLHandle<Texture2D>> textures;

    if (mat->GetTextureCount(type) == 0)
    {
        return textures;
    }
    
    std::cout << "Loading material textures from mesh import..." << std::endl;
    
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::string path = directory + "/" + str.C_Str();
        GLHandle<Texture2D> texture = GraphicsResourceManager::ConstructObject<Texture2D>(path, false);
        textures.push_back(texture);
    }
    return textures;
}

void Model::SubmitToRenderer(RenderPass& renderPass, const glm::mat4& parentTransform)
{
    for (auto mesh : meshes)
    {
        mesh.first.SubmitToRenderer(renderPass, parentTransform * GetTransform());
    }
}
