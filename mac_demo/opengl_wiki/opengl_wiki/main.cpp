//
//  main.cpp
//  opengl_wiki
//
//  Created by zpf on 14-10-12.
//  Copyright (c) 2014年 zpf. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>

#define __gl_h_

#include <GLUT/glut.h>


GLuint program;
GLint  attribute_coord2d;

//create GLSL program
int init_resources(void)
{
    GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vs_source = "#version 150      \n"
                            "in vec2 coord2d;"
                            //"attribute vec2 coord2d;"
                            "void main() {      "
    
                            "  gl_Position = vec4(coord2d, 0.0, 1.0);"
                            "}";
    
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs,GL_COMPILE_STATUS, &compile_ok);
    
    if (0 == compile_ok) {
        fprintf(stderr, "Error in vertex shader\n");
        return 0;
    }
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs_source =
        "#version 150      \n"
        "out vec4 FragColor;"
        "void main() {   "
        "FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
        "}";
    
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
    if (!compile_ok) {
        fprintf(stderr, "Error in fragment shader\n");
        return 0;
    }
    
    
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram (program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if(!link_ok) {
        fprintf(stderr, "glLinkProgram");
        return 0;
    }
    
    const char* attribute_name = "coord2d";
    attribute_coord2d = glGetAttribLocation(program,attribute_name);
    if (attribute_coord2d == -1) {
        fprintf (stderr, "Could not bind attribute %s\n", attribute_name);
        return 0;
    }
    
    return 1;
}
//draw graphics
void onDisplay() {
    /* backgroud as white*/
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(program);
    glEnableVertexAttribArray(attribute_coord2d);
    GLfloat triangle_vertices[] = {
         0.0f,  0.8f,
        -0.8f, -0.8f,
         0.8f, -0.8f,
    };
    
    /*describe our veertices array to OpenGL*/
    glVertexAttribPointer(
                          attribute_coord2d,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          triangle_vertices
                          );
    /*push each element in buffer_vertices to vertex shader*/
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDisableVertexAttribArray(attribute_coord2d);
    
    //glutSwapBuffers();
   // glFlush();

}
//destroy GLSL program
void free_resources() {
    glDeleteProgram(program);

}

int main (int argc, char* argv[]) {
    /*GLUT initialize*/
    glutInit(&argc, argv);
    //glutinitContextVersion(2,0);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("My First OpenGL app");
    
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return EXIT_SUCCESS;
    }
    
    if(init_resources()) {
        glutDisplayFunc(onDisplay);
        glutMainLoop();
    }
    
    //free_resources();
   // return EXIT_SUCCESS;
}