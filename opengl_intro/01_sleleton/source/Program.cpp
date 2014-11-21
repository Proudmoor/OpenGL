//
//  Program.cpp
//  opengl_tutorial
//
//  Created by zpf on 14-11-15.
//  Copyright (c) 2014年 zpf. All rights reserved.
//

#include "Program.h"
#include <stdexcept>

using namespace tdogl;

Program::Program(const std::vector<Shader>& shaders):
    _object(0)
{
    if(shaders.size() <= 0)
        throw std::runtime_error("No shaders were provided to create the program");
    
    _object = glCreateProgram();
    if (_object == 0)
        throw std::runtime_error("glCreateProgram failed");
    
    for (unsigned i = 0; i < shaders.size(); ++i)
        glAttachShader(_object, shaders[i].object());
    glLinkProgram(_object);
    
    for(unsigned i = 0; i < shaders.size(); ++i)
        glDetachShader(_object, shaders[i].object());
    
    GLint status;
    glGetProgramiv(_object, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg ("Program linking failure: ");
        
        GLint infoLogLength;
        glGetProgramiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(_object, infoLogLength,NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteProgram(_object); _object = 0;
        throw std::runtime_error(msg);
    }
}

Program::~Program() {
    if(_object !=0) glDeleteProgram(_object);
}

GLuint Program::object() const {
    return _object;
}

GLint Program::attrib(const GLchar* attribName) const {
    if(!attribName)
        throw std::runtime_error("attribName was NUll");
    
    GLint attrib = glGetAttribLocation(_object, attribName);
    if (attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
    
    return attrib;
}

GLint Program::uniform (const GLchar* uniformName) const {
    if(!uniformName)
        throw std::runtime_error("uniformName was NULL");
    
    GLint uniform = glGetUniformLocation (_object, uniformName);
    if(uniform == -1)
        throw std::runtime_error(std::string("Program uniform no found: ") + uniformName);
    
    return uniform;
}


















