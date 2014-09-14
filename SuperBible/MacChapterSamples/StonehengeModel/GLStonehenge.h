//
//  GLStoneHenge.h
// 
//
//  Created by Richard Wright on 1/6/13.
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

#ifndef __GLUTCore32Demo__GLStoneHenge__
#define __GLUTCore32Demo__GLStoneHenge__


#include <Foundation/Foundation.h>
#include <Foundation/NSString.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AppKit/AppKit.h>

#include <OpenGL/gl3.h>
#include <GLKit/GLKitBase.h>
#include <GLKit/GLKMath.h>
#include <GLKit/GLKMatrix4.h>
#include <GLKit/GLKVector3.h>
#include <GLKit/GLKTextureLoader.h>
#include "StopWatch.h"
#include "GLString.h"
#include <iostream>

#define OBJECT_STONES_LARGE 0
#define OBJECT_STONES_SMALL 1
#define OBJECT_STONES_OTHER 2
#define OBJECT_GROUND       3
#define OBJECT_LAST         4


#define VERTEX_POS          0
#define VERTEX_NOMRAL       1
#define VERTEX_TEXTURE      2
#define VERTEX_TANGENT      3


struct CAMERA_FRAME {
    GLKVector3         vWhere;      // Location of camera
    GLKVector3         vUp;         // Up vector of camera
    GLKVector3         vForward;    // Forward vector of camera
    };


class GLStonehenge
    {
    public:
        GLStonehenge(void);
        ~GLStonehenge(void);
    
        void initModels(void);
        void cleanupModels(void);
        void resized(int w, int h);
        void render(void);
        
        void moveForward(float distance);
        void rotateLocalY(float angle);
        void addTilt(float angle);
        
    protected:
        GLuint  hIndexArray;
        
        // Vertex Arrays for three models
        GLuint  hVertexArrays[OBJECT_LAST];
        
        GLuint  hBufferGroundVerts;
        GLuint  hBufferGroundTexCoords;
        
        GLuint  hBufferSkyVerts;
        GLuint  hBufferSkyTexCoords;
        
        // Buffer objects
        GLuint  hIndexArrays[OBJECT_LAST];
        GLuint  hVertexPositions[OBJECT_LAST];
        GLuint  hVertexNormals[OBJECT_LAST];
        GLuint  hVertexTangents[OBJECT_LAST];
        GLuint  hVertexTexCoords[OBJECT_LAST];
        
        GLuint  nNumVerts[OBJECT_LAST];
        GLuint  nNumIndexes[OBJECT_LAST];
        
        // Shaders
        GLuint  hShaderStones;                      // Normal mapped stones
        GLint   hUniformStonesMVP;
        GLint   hUniformStonesNormalMatrix;
        GLint   hUniformStonesLightDir;
        GLint   hUniformColorMap;
        GLint   hUniformNormalMap;
        
        GLuint  hShaderGround;                      // Detail texture on ground
        GLint   hUniformGroundMVP;
        GLint   hUniformGroundColorMap;
        GLint   hUniformGroundDetail;
        
        GLuint  hShaderText;                        // Texture rectangle/replace for text
        GLint   hUniformTextMVP;
        GLint   hUniformTextColorMap;
        
        GLKMatrix4  mProjection;
                
        GLKTextureInfo      *textureStones;
        GLKTextureInfo      *textureOtherStones;
        GLKTextureInfo      *textureNormalMap;
        GLKTextureInfo      *textureGround;
        GLKTextureInfo      *textureGroundDetail;
                
        GLKMatrix4          mCamera;
        CAMERA_FRAME        cameraFrame;
        float               fTilt;
        
        void readModel(const char *szFileName, int nIndex);
        
        NSMutableDictionary         *stanStringAttrib;
        GLString                    *pFPSString;
        float                       fScreenWidth;
        float                       fScreenHeight;
    
    };













#endif /* defined(__GLUTCore32Demo__GLStoneHenge__) */
