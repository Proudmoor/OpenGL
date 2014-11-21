//
//  Program.h
//  3D_sierpinski
//
//  Created by zpf on 14-11-21.
//
//

#ifndef ___D_sierpinski__Program__
#define ___D_sierpinski__Program__

#include <stdio.h>

#endif /* defined(___D_sierpinski__Program__) */
#include "Shader.h"
#include <vector>

namespace tdogl {
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
        const Program& operator = (const Program&);
    };
}