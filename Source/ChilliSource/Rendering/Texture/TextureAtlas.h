//
//  TextureAtlas.h
//  ChilliSource
//  Created by Scott Downie on 22/10/2010.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2010 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CHILLISOURCE_RENDERING_TEXTURE_TEXTUREATLAS_H_
#define _CHILLISOURCE_RENDERING_TEXTURE_TEXTUREATLAS_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Math/Geometry/Shapes.h>
#include <ChilliSource/Core/Resource/Resource.h>
#include <ChilliSource/Rendering/Texture/UVs.h>

#include <unordered_map>

namespace ChilliSource
{
    //---------------------------------------------------------------------
    /// A resource that holds the information about packed textures in a
    /// texture page. Includes methods for accessing the individual texture
    /// data (such as UVs, size, etc) by name.
    ///
    /// @author S Downie
    //---------------------------------------------------------------------
    class TextureAtlas final : public Resource
    {
    public:
        
        //---------------------------------------------------------------------
        /// Holds the description of a single frame (or texture) packed into
        /// the atlas. This includes the size, UVs, etc. The UVs are
        /// in texels
        ///
        /// @author S Downie
        //---------------------------------------------------------------------
        struct FrameRaw
        {
            s16 m_texCoordU;
            s16 m_texCoordV;
            s16 m_croppedWidth;
            s16 m_croppedHeight;
            s16 m_offsetX;
            s16 m_offsetY;
            s16 m_originalWidth;
            s16 m_originalHeight;
        };
        //---------------------------------------------------------------------
        /// Holds the description of a single frame (or texture) packed into
        /// the atlas. This includes the size, UVs, etc. The UVs are normalised
        ///
        /// @author S Downie
        //---------------------------------------------------------------------
        struct Frame
        {
            UVs m_uvs;
            Vector2 m_croppedSize;
            Vector2 m_originalSize;
            Vector2 m_offset;
        };
        //---------------------------------------------------------------------
        /// Holds the description of a texture atlas. Used to build the resource
        ///
        /// @author S Downie
        //---------------------------------------------------------------------
        struct Descriptor
        {
            std::vector<FrameRaw> m_frames;
            std::vector<u32> m_keys;
            
            u32 m_textureAtlasWidth = 0;
            u32 m_textureAtlasHeight = 0;
        };
        
        CS_DECLARE_NAMEDTYPE(TextureAtlas);
        
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Interface type
        ///
        /// @return Whether this object is of given type
        //---------------------------------------------------------------------
        bool IsA(InterfaceIDType in_interfaceId) const override;
        //---------------------------------------------------------------------
        /// Construct the sprite sheet data from the given descriptor
        /// this populates the resource ready for use
        ///
        /// @author S Downie
        ///
        /// @param Sprite sheet descriptor
        //---------------------------------------------------------------------
        void Build(const Descriptor& in_desc);
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Texture Id as generated by the sprite tool
        ///
        /// @return Frame data
        //---------------------------------------------------------------------
        const Frame& GetFrame(const std::string& in_textureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Texture Id as generated by the sprite tool
        ///
        /// @return Whether frame exists with given Id
        //---------------------------------------------------------------------
        bool HasFrameWithId(const std::string& in_textureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Texture Id as generated by the sprite tool
        ///
        /// @return Rect containing UV coords for the given frame
        //---------------------------------------------------------------------
        UVs GetFrameUVs(const std::string& in_textureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Texture Id as generated by the sprite tool
        ///
        /// @return Size of the given frame in pixels
        //---------------------------------------------------------------------
        Vector2 GetCroppedFrameSize(const std::string& in_textureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Texture Id as generated by the sprite tool
        ///
        /// @return Size of the given frame in pixels prior to alpha cropping
        //---------------------------------------------------------------------
        Vector2 GetOriginalFrameSize(const std::string& in_textureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Texture Id as generated by the sprite tool
        ///
        /// @return The value in pixels of the X, Y crop offset from the original
        /// sprite.
        //---------------------------------------------------------------------
        Vector2 GetFrameOffset(const std::string& in_textureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Hashed texture id from tool name
        ///
        /// @return Frame data
        //---------------------------------------------------------------------
        const Frame& GetFrame(u32 in_hashedTextureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Hashed texture id from tool name
        ///
        /// @return Whether frame exists with given Id
        //---------------------------------------------------------------------
        bool HasFrameWithId(u32 in_hashedTextureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Hashed texture id from tool name
        ///
        /// @return Rect containing UV coords for the given frame
        //---------------------------------------------------------------------
        UVs GetFrameUVs(u32 in_hashedTextureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Hashed texture id from tool name
        ///
        /// @return Size of the given frame in pixels
        //---------------------------------------------------------------------
        Vector2 GetCroppedFrameSize(u32 in_hashedTextureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Hashed texture id from tool name
        ///
        /// @return Size of the given frame in pixels prior to alpha cropping
        //---------------------------------------------------------------------
        Vector2 GetOriginalFrameSize(u32 in_hashedTextureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Hashed texture id from tool name
        ///
        /// @return The value in pixels of the X, Y crop offset from the original
        /// sprite.
        //---------------------------------------------------------------------
        Vector2 GetFrameOffset(u32 in_hashedTextureId) const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Width of TextureAtlas in pixels
        //---------------------------------------------------------------------
        u32 GetWidth() const;
        //---------------------------------------------------------------------
        /// @author S Downie
        ///
        /// @param Height of TextureAtlas in pixels
        //---------------------------------------------------------------------
        u32 GetHeight() const;
        
    private:
        
        friend class ResourcePool;
        //---------------------------------------------------------------------
        /// Factory method to create empty sprite sheet resource. Only called
        /// by the resource pool
        ///
        /// @author S Downie
        ///
        /// @return Ownership of resource
        //---------------------------------------------------------------------
        static TextureAtlasUPtr Create();
        //---------------------------------------------------------------------
        /// Private constructor to enforce use of factory create method
        ///
        /// @author S Downie
        //---------------------------------------------------------------------
        TextureAtlas() = default;
        
    private:
        
        std::unordered_map<u32, Frame> m_frames;
        
        u32 m_textureAtlasWidth = 0;
        u32 m_textureAtlasHeight = 0;
    };
}

#endif
