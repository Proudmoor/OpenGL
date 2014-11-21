//
//  main.cpp
//  3D_Sierpinski
//
//  Created by zpf on 14-11-21.
//
//

#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#include <cassert>
#include <stdexcept>
#include <cmath>

#include <CoreFoundation/CoreFoundation.h>

#include "Program.h"

const glm::vec2 SCREEN_SIZE(800,600);

tdogl::Program* gProgram = NULL;

typedef glm::vec3 point3;
typedef glm::vec3 color3;

GLuint gVAO = 0;
GLuint gVBO = 0;

const int NumTimesTosubdivide = 4;
const int NumTetrahedrons = 256;
const int NumTriangles = 4 * NumTetrahedrons;
const int NumVertices = 3 * NumTriangles;

glm::vec3 points[NumVertices];
glm::vec3 colors[NumVertices];

int Index = 0;

static std::string ResourcePath (std::string fileName) {
    
    char exe_file[PATH_MAX + 1];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if (mainBundle) {
        CFURLRef mainURL = CFBundleCopyBundleURL(mainBundle);
        
        if(mainURL) {
            int ok = CFURLGetFileSystemRepresentation(mainURL, (Boolean) true, (UInt8*) exe_file, PATH_MAX);
            
            if(ok) {
                return std::string(exe_file)  + "/" + fileName;
            }
        }
    }
    
    return "./";
}

static glm::vec3  base_colors[] = {
    glm::vec3( 1.0, 0.0, 0.0 ),
    glm::vec3( 0.0, 1.0, 0.0 ),
    glm::vec3( 0.0, 0.0, 1.0 ),
    glm::vec3( 0.0, 0.0, 0.0 )
};

void triangle(const point3& a, const point3& b, const point3& c,const int color){
    
    points[Index++] = a;
    points[Index++] = b;
    points[Index++] = c;
    colors[Index] = base_colors[color];
    
}

void divide_triangle(const point3& a, const point3& b, const point3&c, const int color,int m) {
    point3 v1, v2, v3;
    
    if (m > 0) {
        v1 = (a + b) / 2.0f;
        v2 = (a + c) / 2.0f;
        v3 = (b + c) / 2.0f;
        divide_triangle(a, v1, v2, color,m-1);
        divide_triangle(c, v2, v3, color,m-1);
        divide_triangle(b, v3, v1, color,m-1);
    }
    else triangle(a,b,c,color);
    
}


void tetra(const point3& a, const point3& b, const point3& c, const point3& d,int m){
    divide_triangle(a, b, c, 0, m);
    divide_triangle(a, c, d, 1, m);
    divide_triangle(a, d, b, 2, m);
    divide_triangle(b, d, c, 3, m);
}

static void LoadShaders() {
    std:: vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("vertex.txt"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("fragment.txt"), GL_FRAGMENT_SHADER));
    gProgram = new tdogl::Program(shaders);
}

static void LoadTriangle() {
    point3 vertices[4] = {
        point3 ( -1.0f, -1.0f, -1.0f),
        point3 (  1.0f, -1.0f, -1.0f),
        point3 (  0.0f,  1.0f, -1.0f),
        point3 (  0.0f,  0.0f,  1.0f)
    };
    
    tetra(vertices[0], vertices[1], vertices[2], vertices[3], NumTimesTosubdivide);
    

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
    
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    
    
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    
    glUseProgram(gProgram->object());
    
    glEnableVertexAttribArray(gProgram->attrib("vert"));
    glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(gProgram -> attrib("vColor"));
    glVertexAttribPointer(gProgram->attrib("vColor"), 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(points));
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
   
}

static void Render() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glUseProgram(gProgram->object());
    
    glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
    glBindVertexArray(0);
    
    glfwSwapBuffers();
}

void AppMain() {
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    
    if(!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 0, 0, GLFW_WINDOW))
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
    
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
    
    
    LoadShaders();
    LoadTriangle();
    
    
    while(glfwGetWindowParam(GLFW_OPENED)){
        
        Render();
        std::cout << "next " << std::endl;
    }
    
    glfwTerminate();
}


int main(int argc, const char * argv[]) {
    try {
        AppMain();
    }catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
