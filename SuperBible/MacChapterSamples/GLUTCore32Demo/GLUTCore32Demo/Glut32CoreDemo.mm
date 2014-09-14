// GLUTCore32Demo.cpp
// OpenGL SuperBible
// Demonstrates using the OpenGL Core profile within GLUT
// Program by Richard S. Wright Jr.

#include <OpenGL/gl3.h>
#include <glut/glut.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "GLStonehenge.h"
#include "StopWatch.h"

GLStonehenge    stonehenge;

/////////////////////////////////////////////////////////
#define MOVE_NONE_BIT       0X00
#define MOVE_FORWARD_BIT    0x01
#define MOVE_BACKWARD_BIT   0x02
#define MOVE_LEFT_BIT       0x04
#define MOVE_RIGHT_BIT      0x08
GLuint  moveFlags = 0x0;



///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
	{
    static float fDistance = 0.025f;
    static CStopWatch cameraTimer;
    float deltaT = cameraTimer.GetElapsedSeconds();
    cameraTimer.Reset();
    
    if(moveFlags & MOVE_FORWARD_BIT)
        stonehenge.moveForward(fDistance * deltaT * 500.0f);
    
    if(moveFlags & MOVE_BACKWARD_BIT)
        stonehenge.moveForward(fDistance * -deltaT * 500.0f);
    
    if(moveFlags & MOVE_LEFT_BIT)
        stonehenge.rotateLocalY(fDistance * 30.0f * deltaT);
    
    if(moveFlags & MOVE_RIGHT_BIT)
        stonehenge.rotateLocalY(fDistance * -30.0f * deltaT);



    stonehenge.render();

    // Flush drawing commands
	glutSwapBuffers();
	glutPostRedisplay();
	}


///////////////////////////////////////////////////////////////////////////////
// A normal ASCII key has been pressed.
void KeyPressFunc(unsigned char key, int x, int y)
	{
	if(key == 32)   // Space Bar
		{


		}

	// Refresh the Window
	glutPostRedisplay();
	}

// Respond to arrow keys by moving the camera frame of reference
void SpecialKeysDown(int key, int x, int y)
    {
    switch(key)
        {
        case GLUT_KEY_UP:
            moveFlags |= MOVE_FORWARD_BIT;
            break;
        case GLUT_KEY_DOWN:
            moveFlags |= MOVE_BACKWARD_BIT;
            break;
        case GLUT_KEY_LEFT:
            moveFlags |= MOVE_LEFT_BIT;
            break;
        case GLUT_KEY_RIGHT:
            moveFlags |= MOVE_RIGHT_BIT;
            break;
        }

        
	glutPostRedisplay();
    }


void SpecialKeysUp(int key, int x, int y)
    {
    switch(key)
        {
        case GLUT_KEY_UP:
            moveFlags &= ~MOVE_FORWARD_BIT;
            break;
        case GLUT_KEY_DOWN:
            moveFlags &= ~MOVE_BACKWARD_BIT;
            break;
        case GLUT_KEY_LEFT:
            moveFlags &= ~MOVE_LEFT_BIT;
            break;
        case GLUT_KEY_RIGHT:
            moveFlags &= ~MOVE_RIGHT_BIT;
            break;
        }

        
	glutPostRedisplay();
    }



///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
	{
    stonehenge.resized(w, h);
	}


///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
	{
	static char szParentDirectory[255];   	

	///////////////////////////////////////////////////////////////////////////   
	// Get the directory where the .exe resides
	char *c;
	strncpy( szParentDirectory, argv[0], sizeof(szParentDirectory) );
	szParentDirectory[254] = '\0'; // Make sure we are NULL terminated
	
	c = (char*) szParentDirectory;

	while (*c != '\0')     // go to end 
	c++;

	while (*c != '/')      // back up to parent 
	c--;

	*c++ = '\0';           // cut off last part (binary name) 

	///////////////////////////////////////////////////////////////////////////   
	// Change to Resources directory. Any data files need to be placed there
    
	chdir(szParentDirectory);

    
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_3_2_CORE_PROFILE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GLUT Core Profile Demo");
	
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(KeyPressFunc);
    glutSpecialFunc(SpecialKeysDown);
    glutSpecialUpFunc(SpecialKeysUp);
	glutDisplayFunc(RenderScene);
    
    printf("Version: %s\r\n", glGetString(GL_VERSION));
    printf("Renderer: %s\r\n", glGetString(GL_RENDERER));
    printf("Vendor: %s\r\n", glGetString(GL_VENDOR));
    printf("GLSL Version: %s\r\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    stonehenge.initModels();
    
	glutMainLoop();
    
    
	return 0;
	}
