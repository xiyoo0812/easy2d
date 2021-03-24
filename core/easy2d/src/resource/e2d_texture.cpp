#include "e2d_texture.h"
#include "base/e2d_image.h"
//#include <Application.h>
//#include <RenderContext.h>

using namespace Easy2D;

Texture::Texture(ResourcesManager<Texture> *rsmr, const Path& pathfile)
    :Resource(rsmr, pathfile)
{
    //is not loaded
    loaded=false;
}

Texture::~Texture()
{
    //release resource
    release();
}

//flip vertical
bool Texture::flipVertical()
{
    return bFlipVertical;
}
bool Texture::flipVertical(bool value)
{
    return bFlipVertical=value;
}
//texture enable
void Texture::bind(uint ntexture)
{
    //
    DEBUG_ASSERT(gpuid);
    //
    RenderContext::bindTexture(gpuid,ntexture);
	//save
	ntextureBind = ntexture;
    //filters
#ifndef DISABLE_MIDMAP
    if(chBlr || chMps)
    {
        //change filter
        auto filterMag=bBilinear?GL_LINEAR:GL_NEAREST;
        auto filter= bBilinear ?  ( bMipmaps ? GL_LINEAR_MIPMAP_LINEAR   : GL_LINEAR  ):
                                  ( bMipmaps ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST );
        RenderContext::filterTexture(filter,filterMag);
        CHECK_GPU_ERRORS();

        //update
        chMps=chBlr=false;
    }
#else
    if(chBlr)
    {
        //change filter
        auto filter=bBilinear?GL_LINEAR:GL_NEAREST;
        RenderContext::filterTexture(filter,filter);
        //update
        chBlr=false;
    }
#endif
}
//setting
bool Texture::bilinear()
{
    return bBilinear;
}
bool Texture::bilinear(bool value)
{
    chBlr=bBilinear!=value;
    return bBilinear=value;
}
bool Texture::mipmaps()
{
    return bMipmaps;
}
bool Texture::mipmaps(bool value)
{
    chMps=bMipmaps!=value;
    return bMipmaps=value;
}
//operators
bool Texture::operator ==(const Texture& t) const
{
    return gpuid==t.gpuid;
}
bool Texture::operator !=(const Texture& t) const
{
    return gpuid!=t.gpuid;
}

//return mesh
SPtr<Mesh> Texture::getPO2Sprite()
{
    //create texture
    if(!po2Srpite)
    {
    //    po2Srpite = std::make_shared<Mesh>(new Mesh());
        //if loaded build mesh
        __build();
    }
    return po2Srpite;
}

//texture
void Texture::__build()
{
    //set loaded values
    if(isLoad() && po2Srpite)
    {
//         //clear cpu mesh
//         po2Srpite->cpuClear();
//         //unload gpu mesh
//         if(po2Srpite->isLoad())
//             po2Srpite->unload();
//         //set size mesh
//         float hlSizeX=spriteWidth*0.5f;
//         float hlSizeY=spriteHeight*0.5f;
//         //add vertexs
//         po2Srpite->addVertex(  hlSizeX,-hlSizeY,offsetUV.z,offsetUV.w);
//         po2Srpite->addVertex(  hlSizeX,hlSizeY,offsetUV.z,offsetUV.y);
//         po2Srpite->addVertex( -hlSizeX,-hlSizeY,offsetUV.x,offsetUV.w);
//         po2Srpite->addVertex( -hlSizeX,hlSizeY,offsetUV.x,offsetUV.y);
//         //end add vertexs
//         //set draw mode
//         po2Srpite->setDrawMode(TRIANGLE_STRIP);
//         //build mesh
//         po2Srpite->build();
    }
}

//load methods
bool Texture::load()
{
    /////////////////////////////////////////////////////////////////////
    //cpu load
    //load image
    Image image;
    if (image.loadImage(rpath.string()))
    {
        width = realWidth = image.geiWidth();
        height = realHeight = image.geiHeight();
        spriteWidth = realWidth;
        spriteHeight = realHeight;
    }
    //create texture
    loadFromBinaryData(image.mBuffer,width,height,realWidth,realHeight,image.type,type);
    //is loaded
    loaded=true;
    //if olready getted, build mesh
    __build();
    //return
    return loaded;
}
bool Texture::unload()
{
    //unload
	//get status
	auto textureinfo=RenderContext::currentTexture(ntextureBind);
	if (textureinfo.enable && textureinfo.idtexture == gpuid)
	{
		RenderContext::unbindTexture(ntextureBind);
	}
	RenderContext::deleteTexture(gpuid);
    //reset values
    width = height = 0;
    realWidth = realHeight = 0;
    gpuid = 0;
    //unbuild mesh
    if(po2Srpite && po2Srpite->isLoad())
        po2Srpite->unload();
    //is not loaded
    loaded=false;
    //return
    return !loaded;
}


bool Texture::loadFromBinaryData(std::vector<uchar>& bytes, uint width, uint height, uint format, uint type)
{
    return loadFromBinaryData(&bytes[0],width,height,width,height,format,type);
}
bool Texture::loadFromBinaryData(std::vector<uchar>& bytes, uint width, uint height, uint gpuwidth, uint gpuheight, uint format, uint type)
{
    return loadFromBinaryData(&bytes[0],width,height,gpuwidth,gpuwidth,format,type);
}

bool Texture::loadFromBinaryData(const uchar* bytes, uint width, uint height, uint format, uint type)
{
    return loadFromBinaryData(bytes,width,height,width,height,format,type);
}
bool Texture::loadFromBinaryData(const uchar* bytes, uint argWidth, uint argHeight, uint argGpuWidth, uint argGpuHeight, uint format, uint type)
{
    width=argWidth;
    height=argHeight;
    realWidth=argGpuWidth;
    realHeight=argGpuHeight;
    //resize
    //create a gpu texture
#ifndef DISABLE_MIDMAP
    gpuid=RenderContext::createTexture(format, type,  realWidth, realHeight, 0, bMipmaps);
#else   
    gpuid=RenderContext::createTexture(format, type,  realWidth, realHeight, 0);
#endif
    //bind
    bind();
    //add image
    if(bytes)
    {
        RenderContext::subTexture(type,width, height, bytes);
    }
    //is loaded
    loaded=true;
    //is not relodable
    reloadable=false;
    //if olready getted, build mesh
    __build();
    //return
    return loaded;
}
