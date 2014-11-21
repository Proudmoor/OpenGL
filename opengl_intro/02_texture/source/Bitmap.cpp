//
//  Bitmap.cpp
//  opengl_intro
//
//  Created by zpf on 14-11-17.
//
//

#include "Bitmap.h"
#include <stdexcept>

#define STBI_FAILURE_USERMSG
#include <stb_image.c>

using namespace tdogl;

inline unsigned char AverageRGB (unsigned char rgb[3]) {
    return (unsigned char)(((double)rgb[0] +(double)rgb[1] + (double)rgb[2]) /3.0);
}

static void Grayscale2GrayscaleAlpha (unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = 255;
}

static void Grayscale2RGB (unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
}

static void Grayscale2RGBA (unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
    dest[3] = 255;
}

static void GrayscaleAlpha2Grayscale(unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
}

static void GrayscaleAlpha2RGB (unsigned  char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
}

static void GrayscaleAlpha2RGBA(unsigned char* src, unsigned char* dest){
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
    dest[3] = src[1];
}

static void RGB2Grayscale(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
}

static void RGB2GrayscaleAlpha(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
    dest[1] = 255;
}

static void RGB2RGBA(unsigned char* src, unsigned char* dest){
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = 255;
}

static void RGBA2Grayscale(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
}


static void RGBA2GrayscaleAlpha(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
    dest[1] = src[3];
}

static void RGBA2RGB(unsigned char* src, unsigned char* dest){
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}
























