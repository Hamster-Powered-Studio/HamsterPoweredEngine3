#pragma once
#include <string>
#include <vector>
#include <assimp/material.h>

#include "IDrawable.h"
#include "Mesh.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

namespace Hamster
{
    // A model is a collection of meshes. It can be drawn, transformed, etc.
    class Model : public IDrawable, public ITransformable
    {
    public:
        
        
        // Import a model from a file path
        Model(std::string path);
        
        // Inherited from IDrawable. Draws all meshes in the model
        //void Draw(const glm::mat4& parentTransform = glm::mat4(1.f)) override;

        // Set the material of a mesh in the model by index. If index is -1, set the material of all meshes
        void SetMaterial(std::shared_ptr<Material> _material, int _index = -1);

        const std::shared_ptr<Material>& GetMaterial(int index = 0);
        
        // Get the number of materials in the model. Currently, this is the same as the number of meshes
        int GetMaterialCount() const { return (int)meshes.size(); }

        const std::vector<std::pair<Mesh, uint32_t>>& GetMeshes() {return meshes;};
        
        ~Model();
    private:
        
        // A list of meshes in the model
        std::vector<std::pair<Mesh, uint32_t>> meshes;

        // The directory of the model file. Used to load textures
        std::string directory;

        // Load a model from a file path
        void LoadModel(std::string path);

        // Recursively process a node in the model import process
        void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform);

        // Process a mesh during the model import process
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

        // Get texture resources from a material during the model import process
        std::vector<GLHandle<Texture2D>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    public:
        void SubmitToRenderer(RenderPass& renderPass, const glm::mat4& parentTransform = glm::mat4(1.0)) override;
    };
}