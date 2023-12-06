#include "RenderTarget2D.h"

#include <iostream>
#include <glad/gl.h>
#include <glm/ext/matrix_clip_space.hpp>

#include "Material.h"
#include "Shader.h"
#include "VertexArray.h"

namespace Hamster
{
    RenderTarget2D::RenderTarget2D(glm::vec2 _size)
    {
        size = _size;
        glGenFramebuffers(1, &rendererID);
    
    }

    RenderTarget2D::~RenderTarget2D()
    {
        glDeleteFramebuffers(1, &rendererID);
    }

    void RenderTarget2D::Initialize()
    {
        AddAttachment(AttachmentType::COLOR);
        AddAttachment(AttachmentType::DEPTH);
        Invalidate();
    }
/*
    void RenderTarget2D::SetBufferTextures(Ref<Material> material)
    {
        material->SetParameter("uGBuffer.diffuse", textures[0].Texture);
        material->SetParameter("uGBuffer.depth", textures[1].Texture);
    }
*/

    void RenderTarget2D::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
        glViewport(0, 0, (int)size.x, (int)size.y);
    }

    void RenderTarget2D::Unbind() const
    {
        glBindFramebuffer( GL_FRAMEBUFFER, 0);
    }

    void RenderTarget2D::Invalidate()
    {
        // Delete the old framebuffer
        glDeleteFramebuffers(1, &rendererID);

        // Create a new framebuffer
        glGenFramebuffers(1, &rendererID);
        Bind();


        std::vector<GLenum> drawbuffers;
        for (auto attachment : textures)
        {
            attachment.Texture.Get()->Regenerate(size);
        
            if (attachment.Type == AttachmentType::COLOR || attachment.Type == AttachmentType::COLOR16F || attachment.Type == AttachmentType::FLOAT || attachment.Type == AttachmentType::FLOAT16F || attachment.Type == AttachmentType::FLOAT32F)
            {
                
                int index = (int)drawbuffers.size();
                glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, attachment.Texture.Get()->GetRendererID(), 0);
                drawbuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
            }
            else
            {
                glFramebufferTexture(GL_FRAMEBUFFER, (int)attachment.Type, attachment.Texture.Get()->GetRendererID(), 0);
            }
        }
    
        glDrawBuffers((int)drawbuffers.size(), drawbuffers.data());
    
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer is incomplete!" << std::endl;
    }

    void RenderTarget2D::SetSize(glm::vec2 _size)
    {
        size = _size;
        Invalidate();
    }



    void RenderTarget2D::Clear(const glm::vec4& _color )
    {
        Bind();
        glClearColor(_color.r, _color.g, _color.b, _color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /*
    void RenderTarget2D::Draw(Ref<VertexArray> item, Ref<Material> material, const glm::mat4& transform, uint32_t drawType)
    {
        Bind();
        item->Bind();

        // Set up the view and projection matrices for the shader
        glm::mat4 vp;
        glm::mat4 vm = view.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), size.x / size.y, 0.1f, 1000.0f);
        vp = projection * vm;

        // Fallback to default material if none is provided
        if (!material)
        {
            material = Material::DefaultMaterial();
        }
    
    
        // Update common uniforms
        material->SetParameter( "uModel", transform );
        material->SetParameter( "uViewProjection", vp );
        material->SetParameter( "uView", vm );
        material->SetParameter( "uProjection", projection );
        //material->SetParameter("uTime", State::Time);
        material->SetParameter("uResolution", size);

        // Apply the material
        material->Apply();


    
    
        //GetTexture(0)->Bind(0);
        // Switch between fill and wireframe mode
        switch (drawMode)
        {
        case DrawMode::FILL:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_CULL_FACE);
            break;
        case DrawMode::WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_CULL_FACE);
            break;
        }

        // We can't use the index buffer if we're drawing points
        if (drawType == GL_POINTS)
        {
            int count = item->GetVertexCount();
            glDrawArrays(GL_POINTS, 0, count);
        }
        else
        {
            // Draw the item
            glDrawElements(drawType, item->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    
    }
*/
    /*
    void RenderTarget2D::Draw(IDrawable* item, const glm::mat4& parentTransform)
    {
        // Tell the item to draw itself using this render target
        item->OnDraw(*this, parentTransform);
    }
    */

    GLHandle<Texture2D> RenderTarget2D::AddAttachment(AttachmentType type)
    {
        Bind();
        TextureFormat format = TextureFormat::RGBA;
        InternalTextureFormat internalFormat = InternalTextureFormat::RGBA8;

        switch (type)
        {
        case AttachmentType::COLOR:
            format = TextureFormat::RGBA;
            internalFormat = InternalTextureFormat::RGBA8;
            break;
        case AttachmentType::FLOAT:
            format = TextureFormat::R;
            internalFormat = InternalTextureFormat::R8;
            break;
        case AttachmentType::FLOAT16F:
            format = TextureFormat::R;
            internalFormat = InternalTextureFormat::R16F;
            break;
        case AttachmentType::FLOAT32F:
            format = TextureFormat::R;
            internalFormat = InternalTextureFormat::R32F;
            break;
        case AttachmentType::DEPTH:
            format = TextureFormat::DEPTH;
            internalFormat = InternalTextureFormat::DEPTH24;
            break;
        case AttachmentType::STENCIL:
            format = TextureFormat::STENCIL;
            internalFormat = InternalTextureFormat::STENCIL8;
            break;
        case AttachmentType::DEPTH_STENCIL:
            format = TextureFormat::DEPTH_STENCIL;
            internalFormat = InternalTextureFormat::DEPTH24_STENCIL8;
            break;
        case AttachmentType::COLOR16F:
            format = TextureFormat::RGBA;
            internalFormat = InternalTextureFormat::RGBA16F;
            break;
        }
    
        auto attachment = textures.emplace_back( Attachment{type, GraphicsResourceManager::ConstructObject<Texture2D>(size, format, internalFormat)} );
    
        attachment.Texture.Get()->SetWrap(TextureWrap::CLAMP_TO_EDGE);
        attachment.Texture.Get()->SetFilter(TextureFilter::LINEAR, TextureFilter::LINEAR);

        int typecount = 0;
        for (auto texs : textures)
        {
            if (texs.Type == type && texs.Texture != attachment.Texture) 
                typecount++;
        }
    
    
        glFramebufferTexture2D(GL_FRAMEBUFFER, (int)type + typecount, GL_TEXTURE_2D, attachment.Texture.Get()->GetRendererID(), 0);
    
        return attachment.Texture;
    
    }
}
