//
//  Bitmap.h
//  opengl_intro
//
//  Created by zpf on 14-11-17.
//
//

#ifndef __opengl_intro__Bitmap__
#define __opengl_intro__Bitmap__

#include <stdio.h>

#endif /* defined(__opengl_intro__Bitmap__) */

#include <string>

namespace tdogl {
    class Bitmap {
    public:
        enum Format {
            Format_Grayscale = 1,
            Format_GrayscaleAlpha = 2,
            Format_RGB = 3,
            Format_RGBA =4
        };
        
        Bitmap(unsigned width, unsigned heigth,Format format,const unsigned char* pixels = NULL);
        Bitmap(const Bitmap& other);
        Bitmap& operator = (const Bitmap& other);
        ~Bitmap();
        
        static Bitmap bitmapFromFile(std::string filePath);
        
        unsigned width() const;
        unsigned height() const;
        Format format() const;
        
        unsigned char* pixelBuffer() const;
        
        unsigned char* getPixel(unsigned int column, unsigned int row) const;
        
        void setPixel(unsigned int column, unsigned int row, const unsigned char* pixel);
        
        void flipVertically();
        
        void copyRectFromBitmap(const Bitmap& src,
                                unsigned srcCol,
                                unsigned srcRow,
                                unsigned destCol,
                                unsigned destRow,
                                unsigned width,
                                unsigned height);
    private:
        Format _format;
        unsigned _width;
        unsigned _height;
        unsigned char* _pixels;
        
        void _set(unsigned width, unsigned height, Format format, const unsigned char* pixels);
        static void _getPixelOffset(unsigned col, unsigned width, unsigned height, Format format);
    };
}