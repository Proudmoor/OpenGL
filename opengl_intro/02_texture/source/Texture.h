//
//  Texture.h
//  opengl_intro
//
//  Created by zpf on 14-11-17.
//
//

#ifndef __opengl_intro__Texture__
#define __opengl_intro__Texture__

#include <stdio.h>
#include <GL/glew.h>

#include "Bitmap.h"

#endif /* defined(__opengl_intro__Texture__) */

namespace tdogl {
    
    class Texture {
    public:
        Texture (const Bitmap& bitmap,
                 GLint minMagFiler = GL_LINEAR,
                 GLint wrapMode = GL_CLAMP_TO_EDGE);
        
        ~Texture();
        
        GLuint object() const;
        
        GLfloat originalWidth() const;
        
        GLfloat originalHeight() const;
        
    private:
        GLuint _object;
        GLfloat _originalWidth;
        GLfloat _originalHeight;
        
        Texture(const Texture&);
        const Texture& operator= (const Texture&);
    };
}