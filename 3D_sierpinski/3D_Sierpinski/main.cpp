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
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <stdexcept>
#include <cmath>

#include <CoreFoundation/CoreFoundation.h>

#include "Program.h"
#include "Camera.h"

const glm::vec2 SCREEN_SIZE(800,600);

tdogl::Program* gProgram = NULL;
tdogl::Camera gCamera;

typedef glm::vec3 point3;
typedef glm::vec3 color3;
GLuint gVAO = 0;
GLuint gVBO = 0;
GLfloat gDegreesRotated = 0.0f;

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

void triangle(const point3& a, const point3& b, const point3& c, const int color){
    
    
    static color3 base_colors[4] = {
        color3(0.0f, 0.0f, 0.0f), color3(0.0f, 1.0f, 0.0f),
        color3(0.0f, 0.0f, 1.0f), color3(1.0f, 0.0f, 0.0f)
    };

    points[Index] = a;  colors[Index] = base_colors[color]; Index++;
    points[Index] = b;  colors[Index] = base_colors[color]; Index++;
    points[Index] = c;  colors[Index] = base_colors[color]; Index++;
}

void tetra(const point3& a, const point3& b, const point3& c, const point3& d){
    triangle(a, b, c, 0);
    triangle(a, c, d, 1);
    triangle(a, d, b, 2);
    triangle(b, d, c, 3);
}

void divide_tetra(const point3& a, const point3& b, const point3& c, const point3& d, int m){
    if(m > 0){
        glm::vec3 mid[6];
        
        mid[0] = (a + b) / 2.0f;
        mid[1] = (a + c) / 2.0f;
        mid[2] = (a + d) / 2.0f;
        mid[3] = (b + c) / 2.0f;
        mid[4] = (c + d) / 2.0f;
        mid[5] = (b + d) / 2.0f;
        
        divide_tetra(a, mid[0], mid[1], mid[2], m-1);
        divide_tetra(mid[0], b, mid[3], mid[5], m-1);
        divide_tetra(mid[1], mid[3], c, mid[4], m-1);
        divide_tetra(mid[2], mid[5], mid[4], d, m-1);
    }
    
    else tetra(a, b, c, d);
}
static void LoadShaders() {
    std:: vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("vertex.txt"), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath("fragment.txt"), GL_FRAGMENT_SHADER));
    gProgram = new tdogl::Program(shaders);
    
//    gProgram -> use();
//    
//    glm::mat4 projection = glm::perspective<float>(50.0, SCREEN_SIZE.x/SCREEN_SIZE.y, 0.1, 10.0);
//    gProgram -> setUniform("projection", projection);
//    
//    glm::mat4 camera = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,1), glm::vec3(0,1,1));
//    gProgram -> setUniform("camera", camera);
//    
//    gProgram -> stopUsing();
    
}

static void LoadTriangle() {
    point3 vertices[4] = {
        point3 ( -1.0f, -1.0f, -1.0f),
        point3 (  1.0f, -1.0f, -1.0f),
        point3 (  0.0f,  1.0f, -1.0f),
        point3 (  0.0f,  0.0f,  1.0f)
    };
    
    divide_tetra(vertices[0], vertices[1], vertices[2], vertices[3], NumTimesTosubdivide);
    
    

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
    
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    
    
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    
    
    glEnableVertexAttribArray(gProgram->attrib("vert"));
    glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(gProgram -> attrib("vColor"));
    glVertexAttribPointer(gProgram->attrib("vColor"), 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(points));
    
}

static void Render() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glUseProgram(gProgram->object());
    
    gProgram -> setUniform("camera", gCamera.matrix());
    
    gProgram -> setUniform("model", glm::rotate(glm::mat4(), gDegreesRotated, glm::vec3(0,1,0)));
    
    glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
    glBindVertexArray(0);
    //glFlush();
    
    gProgram -> stopUsing();
    
    glfwSwapBuffers();
}

void Update(float secondsElapsed) {
    const GLfloat degreesPerSecond = 30.0f;
    gDegreesRotated += secondsElapsed * degreesPerSecond;
    while (gDegreesRotated > 360.0f) gDegreesRotated -= 360.0f;
    
    const float moveSpeed = 3.0;
    if (glfwGetKey('S')) {
        gCamera.offsetPositon(secondsElapsed * moveSpeed * -gCamera.forward());
    } else if (glfwGetKey('W')){
        gCamera.offsetPositon(secondsElapsed * moveSpeed * gCamera.forward());
    } else if (glfwGetKey('A')) {
        gCamera.offsetPositon(secondsElapsed * moveSpeed * -gCamera.right());
    } else if (glfwGetKey('D')) {
        gCamera.offsetPositon(secondsElapsed * moveSpeed * gCamera.right());
    }
    if (glfwGetKey('Z')) {
        gCamera.offsetPositon(secondsElapsed* moveSpeed * -glm::vec3(0,1,0));
    } else if (glfwGetKey('X')) {
        gCamera.offsetPositon(secondsElapsed * moveSpeed * glm::vec3(0,1,0));
    }
    
    //mouse movement with camera
    const float mouseSensitivity = 0.1;
    int mouseX, mouseY;
    glfwGetMousePos(&mouseX, &mouseY);
    gCamera.offsetOrientation(mouseSensitivity* mouseY, mouseSensitivity* mouseX);
    glfwSetMousePos(0,0);
    
    //mouse wheel with field of view
    const float zoomSensitivity = -0.8;
    float fieldOfView = gCamera.fieldOfView() + zoomSensitivity *(float)glfwGetMouseWheel();
    if(fieldOfView < 5.0f) fieldOfView = 5.0f;
    if(fieldOfView > 130.0f) fieldOfView = 130.0f;
    gCamera.setFieldOfView(fieldOfView);
    glfwSetMouseWheel(0);
    
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
    
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(0,0);
    glfwSetMouseWheel(0);
    
    LoadShaders();
    LoadTriangle();
    
    gCamera.setPosition(glm::vec3(0,0,4));
    gCamera.setViewportAspectRatio(SCREEN_SIZE.x / SCREEN_SIZE.y);
    
    double lastTime = glfwGetTime();
    while(glfwGetWindowParam(GLFW_OPENED)){
        
        double thisTime = glfwGetTime();
        Update(thisTime - lastTime);
        lastTime  = thisTime;
        Render();
        //std::cout << "next " << std::endl;
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
