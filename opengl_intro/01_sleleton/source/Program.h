//
//  Program.h
//  opengl_tutorial
//
//  Created by zpf on 14-11-15.
//  Copyright (c) 2014年 zpf. All rights reserved.
//

#ifndef __opengl_tutorial__Program__
#define __opengl_tutorial__Program__

#include <stdio.h>

#endif /* defined(__opengl_tutorial__Program__) */

#include "Shader.h"
#include <vector>

namespace tdogl{
    class Program {
    public:
        Program(const std::vector<Shader>& shaders);
        ~Program();
        
        GLuint object() const;
        
        GLint attrib(const GLchar* attribName) const;
        
        GLint uniform(const GLchar* uniformName) const;
        
    private:
        GLuint _object;
        
        Program(const Program&);
        const Program& operator= (const Program&);
    };
}
