#include "Texture.h" 
#include "Renderer.h" 
#include "Core/Logger.h" 
#include <SDL.h> 
#include <SDL_image.h> 
#include <cstdarg> 

namespace c14
{
    Texture::~Texture()
    {
        if (m_texture) glDeleteTextures(1, &m_texture);
    }

    bool Texture::Create(std::string filename, ...)
    {
        // va_list - type to hold information about variable arguments 
        va_list args;

        // va_start - enables access to variadic function arguments 
        va_start(args, filename);

        // va_arg - accesses the next variadic function arguments 
        Renderer& renderer = va_arg(args, Renderer);

        // va_end - ends traversal of the variadic function arguments 
        va_end(args);

        // create texture (returns true/false if successful) 
        return Load(filename, renderer);
    }

    bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
    {
        return true;
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        // load surface 
        // !! call IMG_Load with c-string of filename 
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr)
        {
            LOG(SDL_GetError());
            return false;
        }
        //FlipSurface(surface);

        // create texture 
        glGenTextures(1, &m_texture);
        glBindTexture(m_target, m_texture);

        GLenum format = (surface->format -> BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(m_target, 0, format, surface->w, surface -> h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // !! call SDL_FreeSurface with surface as the parameter 
        // !! no need to keep surface after texture is created 
        SDL_FreeSurface(surface);

        return true;
    }

    c14::Vector2 Texture::GetSize() const
    {
        return Vector2{ 0, 0 };
    }

    void Texture::FlipSurface(SDL_Surface* surface)
    {
        SDL_LockSurface(surface);

        int pitch = surface->pitch; // row size 
        uint8_t* temp = new uint8_t[pitch]; // intermediate buffer 
        uint8_t* pixels = (uint8_t*)surface->pixels;

        for (int i = 0; i < surface->h / 2; ++i) {
            // get pointers to the two rows to swap 
            uint8_t* row1 = pixels + i * pitch;
            uint8_t* row2 = pixels + (surface->h - i - 1) * pitch;

            // swap rows 
            memcpy(temp, row1, pitch);
            memcpy(row1, row2, pitch);
            memcpy(row2, temp, pitch);
        }

        delete[] temp;

        SDL_UnlockSurface(surface);
    }
}