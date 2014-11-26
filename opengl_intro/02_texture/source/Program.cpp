//
//  Program.cpp
//  opengl_tutorial
//
//  Created by zpf on 14-11-15.
//  Copyright (c) 2014年 zpf. All rights reserved.
//

#include "Program.h"
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

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

void Program::use() const {
    glUseProgram(_object);
}

bool Program::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (currentProgram == (GLint)_object);
}

void Program::stopUsing() const {
    assert(isInUse());
    glUseProgram(0);
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






void Program::setUniformMatrix2(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(uniform(name), count, transpose, v);
}

void Program::setUniformMatrix3(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(uniform(name), count, transpose, v);
}

void Program::setUniformMatrix4(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(uniform(name), count, transpose, v);
}

void Program::setUniform(const GLchar* name, const glm::mat2& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* name, const glm::mat3& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* name, const glm::mat4& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* uniformName, const glm::vec3& v) {
    setUniform3v(uniformName, glm::value_ptr(v));
}

void Program::setUniform(const GLchar* uniformName, const glm::vec4& v) {
    setUniform4v(uniformName, glm::value_ptr(v));
}














