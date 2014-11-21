//
//  Shader.h
//  opengl_tutorial
//
//  Created by zpf on 14-11-15.
//  Copyright (c) 2014年 zpf. All rights reserved.
//

#ifndef __opengl_tutorial__Shader__
#define __opengl_tutorial__Shader__

#include <stdio.h>

#endif /* defined(__opengl_tutorial__Shader__) */

#include <GL/glew.h>
#include <string>

namespace tdogl {
    class Shader {
    public:
        
        static Shader shaderFromFile(const std::string& filePath, GLenum shaderType);
        
        Shader(const std::string& shaderCode ,GLenum shaderType);
        
        GLuint object() const;
        
        Shader(const Shader& other);
        Shader& operator = (const Shader& other);
        ~Shader();
        
    private:
        GLuint _object;
        unsigned* _refCount;
        
        void _retain();
        void _release();
    };
}