#ifndef IMAGE_H
#define IMAGE_H

#include "e2d_config.h"
#include "e2d_color.h"
#include "math/e2d_math.h"

namespace Easy2D
{
    class Image
    {
    public:
        //constructors
        Image();
        Image(int width, int height, int bits, bool set_default_color=false, const Color& color= Color(255,255,255,255));
        //destructor
        ~Image();
        //load a image from file
        bool loadImage(const String& path);
        bool loadFromData(BYTE *data, int size);
        //save in a file
        bool save(const String& path);
        //clear
        void clear();
        //get a pixel
        Color getPixel(int x,int y);
        //imposta un pixel
        void setPixel(int x, int y, const Color &pixel);
        //scale image:
        bool scale(int width, int height);
        //width
        inline int getWidth() 
        {
            return mWidth;
        }
        //height
        inline int getHeight()
        {
            return mHeight;
        }
        //channels
        inline int getFormat()
        {
            return mChannels == 4 ? GL_RGBA : GL_RGB;
        }
        //bytes
        inline BYTE* getBuffer()
        {
            return mBuffer;
        }

        //returna a sub immage
        static Image* getImage(Image* surce, int x,int y, int width, int height);
        // return openGL bite format
        static BYTE& pixel(BYTE* bytes, int width, int x, int y, int c);
        // save a openGL screen
        static Image* getScreenshot(int width, int height);

    private:
        //fields
        int mWidth = 0;             ///< image width in pixels
        int mHeight = 0;            ///< image height in pixels
        int mChannels = 0;          ///< count bytes per pixel
        BYTE* mBuffer = nullptr;    ///< image data
        std::string mName = "";     ///< image name
    };
}

#endif
