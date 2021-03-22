#ifndef TEXTURE_H
#define TEXTURE_H

#include "e2d_config.h"
#include "e2d_resource.h"
#include "math/e2d_math.h"

namespace Easy2D
{
    class Mesh;
    class Texture : public Resource<Texture>
    {
        uint gpuid = 0;
        uint ntextureBind = 0;
        uint width = 0, height = 0;
        uint realWidth = 0, realHeight = 0;
        uint spriteWidth = 0, spriteHeight = 0;
        Vec4 offsetUV = Vec4(0, 0, 1, 1);
        bool bBilinear = true, chBlr = true, bMipmaps = true, chMps = true, bFlipVertical = false;
        //sprite pow of tow
        SPtr<Mesh*> po2Srpite = nullptr;
        void __build();

    public:
        Texture(ResourcesManager<Texture> *rsmr=nullptr, const Path& pathfile="");
        //destructor
        virtual ~Texture();
        //
        void bind(uint ntexture=0);
        //flip vertical
        bool flipVertical();
        bool flipVertical(bool value);
        //load methods
        virtual bool load();
        virtual bool unload();

        //loading from buffer
        bool loadFromBinaryData(const uchar* bytes, uint width, uint height, uint format, uint type);
        bool loadFromBinaryData(std::vector<uchar>& bytes, uint width, uint height, uint format, uint type);
        bool loadFromBinaryData(const uchar* bytes, uint width, uint height, uint gpuwidth, uint gpuheight, uint format, uint type);
        bool loadFromBinaryData(std::vector<uchar>& bytes, uint width, uint height, uint gpuwidth, uint gpuheight, uint format, uint type);

        //settings
        bool bilinear();
        bool bilinear(bool value);
        bool mipmaps();
        bool mipmaps(bool value);
        //offset UV (npow)
        inline Vec2 getOffestUV() const
        {
            return Vec2(offsetUV.z,offsetUV.w);
        }
        inline const Vec4& getOffestUV4() const
        {
            return offsetUV;
        }
        //mesh size this..
        SPtr<Mesh> getPO2Sprite();
        //query
        inline uint getGpuID()
        {
            return gpuid;
        }
        inline uint getWidth()
        {
            return width;
        }
        inline uint getRealWidth()
        {
            return realWidth;
        }
        inline uint getSpriteWidth()
        {
            return spriteWidth;
        }
        inline uint getHeight()
        {
            return height;
        }
        inline uint getRealHeight()
        {
            return realHeight;
        }
        inline uint getSpriteHeight()
        {
            return spriteHeight;
        }

        inline Vec2 getSize()
        {
            return Vec2((float)width, (float)height);
        }
        inline Vec2 getRealSize()
        {
            return Vec2((float)realWidth, (float)realHeight);
        }
        inline Vec2 getSpriteSize()
        {
            return Vec2((float)spriteWidth, (float)spriteHeight);
        }
        //overload
        bool operator ==(const Texture&) const;
        bool operator !=(const Texture&) const;
    };
};

#endif