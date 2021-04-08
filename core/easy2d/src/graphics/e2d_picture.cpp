//stb load
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"
#include "e2d_picture.h"

//using name space
using namespace Easy2D;

//costruttore
Picture::Picture()
{
}

Picture::Picture(int width, int height, int bits, bool set_default_color/* =false */, const Color& color/* = Color(255,255,255,255) */)
    :mWidth(width), mHeight(height), mChannels(bits)
{
    mBuffer = (BYTE*)malloc(width * height * mChannels * sizeof(BYTE));
    if (set_default_color)
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                this->setPixel(x, y, color);
}

//distruttore
Picture::~Picture()
{
    clear();
}

//carica immagini
bool Picture::loadPicture(const String& path)
{
    mName = path;
    stbi_set_flip_vertically_on_load(true);
    mBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 0);
    if (mBuffer) return true;
    return false;
}

bool Picture::loadFromData(BYTE* data, int size)
{
    stbi_set_flip_vertically_on_load(true);
    mBuffer = stbi_load_from_memory(data, size, &mWidth, &mHeight, &mChannels, 0);
    if (mBuffer) return true;
    return false;
}

bool Picture::save(const String& path)
{
    Path filePath(path);
    stbi_set_flip_vertically_on_load(true);
    String ext = filePath.extension().string();
    if (ext == "png")
    {
        return (stbi_write_png(path.c_str(), mWidth, mHeight, mChannels, (void*)mBuffer, 0) != 0);
    }
    else if (ext == "tga")
    {
        return (stbi_write_tga(path.c_str(), mWidth, mHeight, mChannels, (void*)mBuffer) != 0);
    }
    else if (ext == "jpg")
    {
        return (stbi_write_jpg(path.c_str(), mWidth, mHeight, mChannels, (void*)mBuffer, 12) != 0);
    }
    else if (ext == "bmp")
    {
        return (stbi_write_bmp(path.c_str(), mWidth, mHeight, mChannels, (void*)mBuffer) != 0);
    }
    return false;
}

//cancella
void Picture::clear()
{
    if (mBuffer)
    {
        stbi_image_free(mBuffer);
        mBuffer = nullptr;
    }
    mWidth = 0;
    mHeight = 0;
}

//restituisci un pixel
Color Picture::getPixel(int x, int y)
{
    int alpha = 255;
    if (mChannels != 3)
        alpha = (int)mBuffer[(y * mWidth + x) * 4 + 3] * 1;
    return Color((int)mBuffer[(y * mWidth + x) * mChannels] * 1, (int)mBuffer[(y * mWidth + x) * mChannels + 1] * 1, (int)mBuffer[(y * mWidth + x) * mChannels + 2] * 1, alpha);
}

//imposta un pixel
void Picture::setPixel(int x, int y, const Color& pixel)
{
    mBuffer[(y * mWidth + x) * mChannels] = pixel.r;
    mBuffer[(y * mWidth + x) * mChannels + 1] = pixel.g;
    mBuffer[(y * mWidth + x) * mChannels + 2] = pixel.b;
    if (mChannels != 3)
        mBuffer[(y * mWidth + x) * 4 + 3] = pixel.a;
}

//restituisci subPicture
Picture* Picture::getPicture(Picture* surce, int x, int y, int width, int height)
{
    int _x, _y;
    Color RGBA;
    //creo la memoria
    BYTE* bytes = (BYTE*)malloc(width * height * surce->mChannels * sizeof(BYTE));

    //creo una nuova immagine
    Picture* out_img = new Picture();

    for (_y = y; _y < (height + y); _y++)
    {
        for (_x = x; _x < (width + x); _x++)
        {
            RGBA = surce->getPixel(_x, _y);
            bytes[((_y - y) * width + _x - x) * surce->mChannels] = (BYTE)RGBA.r;
            bytes[((_y - y) * width + _x - x) * surce->mChannels + 1] = (BYTE)RGBA.g;
            bytes[((_y - y) * width + _x - x) * surce->mChannels + 2] = (BYTE)RGBA.b;
            if (surce->mChannels == 4)
                bytes[((_y - y) * width + _x - x) * surce->mChannels + 3] = (BYTE)RGBA.a;
        }
    }
    //salvo
    out_img->mBuffer = bytes;
    out_img->mWidth = width;
    out_img->mHeight = height;
    out_img->mChannels = surce->mChannels;

    return out_img;
}

//scale image:
bool Picture::scale(int newWidth, int newHeight)
{
    BYTE* newbytes = (BYTE*)malloc(mChannels * newWidth * newHeight);
    if (stbir_resize(mBuffer, mWidth, mHeight, 0, newbytes, newWidth, newHeight, 0, STBIR_TYPE_UINT8, mChannels, STBIR_ALPHA_CHANNEL_NONE, 0,
        STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_BOX, STBIR_FILTER_BOX, STBIR_COLORSPACE_SRGB, nullptr) == 0)
    {
        free(newbytes);
        return false;
    }
    stbi_image_free(mBuffer);
    mBuffer = newbytes;
    mWidth = newWidth;
    mHeight = newHeight;
    return true;
}

// OpenGL bite format
BYTE& Picture::pixel(BYTE* bytes, int width, int x, int y, int c)
{
    return bytes[(y * width + x) * 3 + c];
}

// OpenGL screen save
Picture* Picture::getScreenshot(int width, int height)
{
    Picture* out_img = new Picture();
    out_img->mWidth = width;
    out_img->mHeight = height;
    out_img->mChannels = 4;
    out_img->mBuffer = (BYTE*)malloc(width * height * 4);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, out_img->mBuffer);
    return out_img;
}
