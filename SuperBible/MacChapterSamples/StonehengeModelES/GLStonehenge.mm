//
//  GLStonehenge.cpp
// 
//
//  Created by Richard Wright on 1/6/13.
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

#include "GLStonehenge.h"
#include <assert.h>
#include <string.h>



#define MAX_SHADER_LENGTH   8192

// Rather than malloc/free a block everytime a shader must be loaded,
// I will dedicate a single 8k block for reading in shaders.
static GLubyte shaderText[MAX_SHADER_LENGTH];

//////////////////////////////////////////////////////////////////////////
// Load the shader from the source text
void gltLoadShaderSrc(const char *szShaderSrc, GLuint shader)
	{
    GLchar *fsStringPtr[1];

    fsStringPtr[0] = (GLchar *)szShaderSrc;
    glShaderSource(shader, 1, (const GLchar **)fsStringPtr, NULL);
	}


////////////////////////////////////////////////////////////////
// Load the shader from the specified file. Returns false if the
// shader could not be loaded
bool gltLoadShaderFile(const char *szFile, GLuint shader)
	{
    GLint shaderLength = 0;
    FILE *fp;
	
    // Open the shader file
    fp = fopen(szFile, "r");
    if(fp != NULL)
		{
        // See how long the file is
        while (fgetc(fp) != EOF)
            shaderLength++;
		
        // Allocate a block of memory to send in the shader
        assert(shaderLength < MAX_SHADER_LENGTH);   // make me bigger!
        if(shaderLength > MAX_SHADER_LENGTH)
			{
            fclose(fp);
            return false;
			}
		
        // Go back to beginning of file
        rewind(fp);
		
        // Read the whole file in
        if (shaderText != NULL)
            fread(shaderText, 1, shaderLength, fp);
		
        // Make sure it is null terminated and close the file
        shaderText[shaderLength] = '\0';
        fclose(fp);
		}
    else
        return false;    
	
    // Load the string
    gltLoadShaderSrc((const char *)shaderText, shader);
    
    return true;
	}   


/////////////////////////////////////////////////////////////////
// Load a pair of shaders, compile, and link together. Specify the complete
// source text for each shader. After the shader names, specify the number
// of attributes, followed by the index and attribute name of each attribute
GLuint gltLoadShaderPairWithAttributes(const char *szVertexProg, const char *szFragmentProg, ...)
{
    // Temporary Shader objects
    GLuint hVertexShader;
    GLuint hFragmentShader;
    GLuint hReturn = 0;
    GLint testVal;
	
    // Create shader objects
    hVertexShader = glCreateShader(GL_VERTEX_SHADER);
    hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
    // Load them. If fail clean up and return null
    // Vertex Program
    if(gltLoadShaderFile(szVertexProg, hVertexShader) == false)
    {
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
		fprintf(stderr, "The shader at %s could not be found.\n", szVertexProg);
        return (GLuint)NULL;
    }
	
    // Fragment Program
    if(gltLoadShaderFile(szFragmentProg, hFragmentShader) == false)
    {
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
		fprintf(stderr,"The shader at %s  could not be found.\n", szFragmentProg);
        return (GLuint)NULL;
    }
    
    // Compile them both
    glCompileShader(hVertexShader);
    glCompileShader(hFragmentShader);
    
    // Check for errors in vertex shader
    glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
		char infoLog[1024];
		glGetShaderInfoLog(hVertexShader, 1024, NULL, infoLog);
		fprintf(stderr, "The shader at %s failed to compile with the following error:\n%s\n", szVertexProg, infoLog);
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
        return (GLuint)NULL;
    }
    
    // Check for errors in fragment shader
    glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
		char infoLog[1024];
		glGetShaderInfoLog(hFragmentShader, 1024, NULL, infoLog);
		fprintf(stderr, "The shader at %s failed to compile with the following error:\n%s\n", szFragmentProg, infoLog);
        glDeleteShader(hVertexShader);
        glDeleteShader(hFragmentShader);
        return (GLuint)NULL;
    }
    
    // Create the final program object, and attach the shaders
    hReturn = glCreateProgram();
    glAttachShader(hReturn, hVertexShader);
    glAttachShader(hReturn, hFragmentShader);
    
    
    // Now, we need to bind the attribute names to their specific locations
	// List of attributes
	va_list attributeList;
	va_start(attributeList, szFragmentProg);
    
    // Iterate over this argument list
	char *szNextArg;
	int iArgCount = va_arg(attributeList, int);	// Number of attributes
	for(int i = 0; i < iArgCount; i++)
    {
		int index = va_arg(attributeList, int);
		szNextArg = va_arg(attributeList, char*);
		glBindAttribLocation(hReturn, index, szNextArg);
    }
	va_end(attributeList);
    
    // Attempt to link
    glLinkProgram(hReturn);
	
    // These are no longer needed
    glDeleteShader(hVertexShader);
    glDeleteShader(hFragmentShader);
    
    // Make sure link worked too
    glGetProgramiv(hReturn, GL_LINK_STATUS, &testVal);
    if(testVal == GL_FALSE)
    {
		char infoLog[1024];
		glGetProgramInfoLog(hReturn, 1024, NULL, infoLog);
		fprintf(stderr,"The programs %s and %s failed to link with the following errors:\n%s\n",
                szVertexProg, szFragmentProg, infoLog);
		glDeleteProgram(hReturn);
		return (GLuint)NULL;
    }
    
    // All done, return our ready to use shader program
    return hReturn;  
}   






GLStonehenge::GLStonehenge(void)
    {
    
    
    
    }



GLStonehenge::~GLStonehenge(void)
    {
    
    
    }





//////////////////////////////////////////////////////////////////////////////////////////
// Screen resized or initially created. Set the viewport and compute the projection matrix
// given the new screen aspect ratio.
void GLStonehenge::resized(int w, int h)
    {
    glViewport(0, 0, w, h);
    fScreenWidth = float(w);
    fScreenHeight = float(h);
    mProjection = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(30.0f), float(w)/float(h), 1.0f, 15000.0f);
    }


void GLStonehenge::readModel(const char *szFileName, int nIndex)
    {
    // Load the first set of stones
    FILE *pFileHandle;

    pFileHandle = fopen(szFileName,"rb");
    if(pFileHandle == NULL)
        return;

    // Get the number of verts and indexes
    fread(&nNumVerts[nIndex], sizeof(GLuint), 1, pFileHandle);
    fread(&nNumIndexes[nIndex], sizeof(GLuint), 1, pFileHandle);
    
    // Bind the the vertex array object
    glBindVertexArrayOES(hVertexArrays[nIndex]);
    
    ///////////////////////////
    // First are the vertexes
    glBindBuffer(GL_ARRAY_BUFFER, hVertexPositions[nIndex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nNumVerts[nIndex], NULL, GL_STATIC_DRAW);
    float *pData = (float *)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
    fread(pData, sizeof(float) * 3 * nNumVerts[nIndex], 1, pFileHandle);
    glUnmapBufferOES(GL_ARRAY_BUFFER);
    glVertexAttribPointer(VERTEX_POS, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_POS);
    
    // Next are normals
    glBindBuffer(GL_ARRAY_BUFFER, hVertexNormals[nIndex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nNumVerts[nIndex], NULL, GL_STATIC_DRAW);
    pData = (float *)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
    fread(pData, sizeof(float) * 3 * nNumVerts[nIndex], 1, pFileHandle);
    glUnmapBufferOES(GL_ARRAY_BUFFER);
    glVertexAttribPointer(VERTEX_NOMRAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_NOMRAL);
    
    // Texture Coordinates
    glBindBuffer(GL_ARRAY_BUFFER, hVertexTexCoords[nIndex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * nNumVerts[nIndex], NULL, GL_STATIC_DRAW);
    pData = (float *)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
    fread(pData, sizeof(float) * 2 * nNumVerts[nIndex], 1, pFileHandle);
    glUnmapBufferOES(GL_ARRAY_BUFFER);
    glVertexAttribPointer(VERTEX_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_TEXTURE);

    // Indexes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hIndexArrays[nIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nNumIndexes[nIndex], NULL, GL_STATIC_DRAW);
    GLuint *pIndexData = (GLuint *)glMapBufferOES(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
    fread(pIndexData, sizeof(GLuint), nNumIndexes[nIndex], pFileHandle);
    glUnmapBufferOES(GL_ELEMENT_ARRAY_BUFFER);

    
    // Tangent vectors
    glBindBuffer(GL_ARRAY_BUFFER, hVertexTangents[nIndex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nNumVerts[nIndex], NULL, GL_STATIC_DRAW);
    pData = (float *)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
    fread(pData, sizeof(float) * 3 * nNumVerts[nIndex], 1, pFileHandle);
    glUnmapBufferOES(GL_ARRAY_BUFFER);
    glVertexAttribPointer(VERTEX_TANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_TANGENT);


    fclose(pFileHandle);
    }


void GLStonehenge::initModels(void)
    {
    glGenVertexArraysOES(OBJECT_LAST, hVertexArrays);
    glGenBuffers(OBJECT_LAST, hIndexArrays);
    glGenBuffers(OBJECT_LAST, hVertexPositions);
    glGenBuffers(OBJECT_LAST, hVertexNormals);
    glGenBuffers(OBJECT_LAST, hVertexTangents);
    glGenBuffers(OBJECT_LAST, hVertexTexCoords);
    
    readModel("stones0.iva", OBJECT_STONES_SMALL);
    readModel("stones1.iva", OBJECT_STONES_LARGE);
    readModel("stones2.iva", OBJECT_STONES_OTHER);
    
    
    // Ground is just a single plane
    float fGroundLevel = -127.0f;
    float fGroundRadius = 2000.0f;

    GLfloat vGroundVerts[12] = {    -fGroundRadius, -fGroundRadius, fGroundLevel,
                                    fGroundRadius, -fGroundRadius, fGroundLevel,
                                    fGroundRadius, fGroundRadius, fGroundLevel,
                                    -fGroundRadius, fGroundRadius, fGroundLevel };
        
    GLfloat vGroundTex[8] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };

    glBindVertexArrayOES(hVertexArrays[OBJECT_GROUND]);
    
    glGenBuffers(1, &hBufferGroundVerts);
    glBindBuffer(GL_ARRAY_BUFFER, hBufferGroundVerts);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vGroundVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_POS, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_POS);
    
    glGenBuffers(1, &hBufferGroundTexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, hBufferGroundTexCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vGroundTex, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_TEXTURE);
    
    
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"stones" ofType:@"png"];
    NSError *error = nil;
    textureStones = [GLKTextureLoader textureWithContentsOfFile:path options:nil error:&error];
    if(!textureStones)
        NSLog(@"Texture load failure: %@", error);
    
    [textureStones retain];
    
    glBindTexture(GL_TEXTURE_2D, textureStones.name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
    glGenerateMipmap(GL_TEXTURE_2D);


    path = [[NSBundle mainBundle] pathForResource:@"marble" ofType:@"png"];
    error = nil;
    textureOtherStones = [GLKTextureLoader textureWithContentsOfFile:path options:nil error:&error];
    if(!textureOtherStones)
        NSLog(@"Texture load failure: %@", error);
    
    [textureOtherStones retain];
    
    glBindTexture(GL_TEXTURE_2D, textureOtherStones.name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
    glGenerateMipmap(GL_TEXTURE_2D);


    path = [[NSBundle mainBundle] pathForResource:@"stonesbump" ofType:@"png"];
    error = nil;
    textureNormalMap = [GLKTextureLoader textureWithContentsOfFile:path options:nil error:&error];
    if(!textureNormalMap)
        NSLog(@"Texture load failure: %@", error);
    [textureNormalMap retain];
    
    glBindTexture(GL_TEXTURE_2D, textureNormalMap.name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
    glGenerateMipmap(GL_TEXTURE_2D);



    path = [[NSBundle mainBundle] pathForResource:@"grass" ofType:@"png"];
    error = nil;
    textureGround = [GLKTextureLoader textureWithContentsOfFile:path options:nil error:&error];
    if(!textureGround)
        NSLog(@"Texture load failure: %@", error);
    [textureGround retain];
    
    glBindTexture(GL_TEXTURE_2D, textureGround.name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
    glGenerateMipmap(GL_TEXTURE_2D);



    path = [[NSBundle mainBundle] pathForResource:@"detail2" ofType:@"png"];
    error = nil;
    textureGroundDetail = [GLKTextureLoader textureWithContentsOfFile:path options:nil error:&error];
    if(!textureGroundDetail)
        NSLog(@"Texture load failure: %@", error);
    [textureGroundDetail retain];
    
    glBindTexture(GL_TEXTURE_2D, textureGroundDetail.name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
    glGenerateMipmap(GL_TEXTURE_2D);


    /////////////////////////////////////////////////////////////
    hShaderStones = gltLoadShaderPairWithAttributes("sh.vp", "sh.fp", 4, VERTEX_POS, "vVertexPos", VERTEX_NOMRAL, "vNormal",
        VERTEX_TEXTURE, "vTextCoord", VERTEX_TANGENT, "vTangent");
        
    hUniformStonesMVP = glGetUniformLocation(hShaderStones, "mModelViewProjectionMatrix");
    hUniformStonesNormalMatrix = glGetUniformLocation(hShaderStones, "mNormalMatrix");
    hUniformStonesLightDir = glGetUniformLocation(hShaderStones, "vLightDirEye");
    hUniformColorMap = glGetUniformLocation(hShaderStones, "colorMap");
    hUniformNormalMap = glGetUniformLocation(hShaderStones, "normalMap");
    
    // These two uniforms only need to be set once, do it here
    glUseProgram(hShaderStones);
    glUniform1i(hUniformColorMap, 0);
    glUniform1i(hUniformNormalMap, 1);
    
    
    //////////////////////////////////////////////////////////////
    hShaderGround = gltLoadShaderPairWithAttributes("ground.vp", "ground.fp", 2, VERTEX_POS, "vVertexPos", VERTEX_TEXTURE, "vTextCoord");
    hUniformGroundMVP = glGetUniformLocation(hShaderGround, "mModelViewProjectionMatrix");
    hUniformGroundColorMap = glGetUniformLocation(hShaderGround, "colorMap");
    hUniformGroundDetail = glGetUniformLocation(hShaderGround, "detailMap");
    
    glUseProgram(hShaderGround);
    glUniform1i(hUniformGroundColorMap, 0);
    glUniform1i(hUniformGroundDetail, 1);
    
    
    // Default Camera Location
    cameraFrame.vWhere = { 1260.0f, 0.0f, -60.0f };
    cameraFrame.vForward = { -1.0f, 0.0f, 0.0f};
    cameraFrame.vUp = { 0.0f, 0.0f, 1.0f};
    fTilt = 0.0f;


//    cameraFrame.vWhere = { 0.0f, 0.0f, 2500.0f };
//    cameraFrame.vForward = { 0.0f, 0.0f, -1.0f};
//    cameraFrame.vUp = { 1.0f, 0.0f, 0.0f};

        
    glClearColor(0.33f, 0.07f, 0.93f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
        
    }

void GLStonehenge::cleanupModels(void)
    {
    glDeleteBuffers(OBJECT_LAST, hIndexArrays);
    glDeleteBuffers(OBJECT_LAST, hVertexPositions);
    glDeleteBuffers(OBJECT_LAST, hVertexNormals);
    glDeleteBuffers(OBJECT_LAST, hVertexTangents);
    glDeleteBuffers(OBJECT_LAST, hVertexTexCoords);
    glDeleteVertexArraysOES(OBJECT_LAST, hVertexArrays);
    }


//////////////////////////////////////////////////////////////////////////////
// Add tilt up and down, clamp at +/- 45 degrees
void GLStonehenge::addTilt(float angle)
    {
    fTilt += angle;
    if(fTilt > GLKMathDegreesToRadians(45.0f))
        fTilt = GLKMathDegreesToRadians(45.0f);
        
    if(fTilt < GLKMathDegreesToRadians(-45.0f))
        fTilt = GLKMathDegreesToRadians(-45.0f);
    
    }

//////////////////////////////////////////////////////////////////////////////
// Moving forward is just an addition along the forward vector
void GLStonehenge::moveForward(float distance)
    {
    // Scale forward vector by distance
    GLKVector3 vForward = GLKVector3MultiplyScalar(cameraFrame.vForward, distance * 8.0f);
    
    // Add result to location
    GLKVector3 vNewWhere = GLKVector3Add(cameraFrame.vWhere, vForward);
    cameraFrame.vWhere = vNewWhere;
    }

////////////////////////////////////////////////////////////////////////////
// The Camera can turn left or right only
void GLStonehenge::rotateLocalY(float angle)
    {
    // Create a rotation matrix around the camera's up vector
    GLKMatrix4 rot = GLKMatrix4MakeRotation(angle, cameraFrame.vUp.x,
                                                   cameraFrame.vUp.y,
                                                   cameraFrame.vUp.z);
    
    // Rotate the camera's Z axis around this vector... that's all
    GLKVector3 vNewForward = GLKMatrix4MultiplyVector3(rot, cameraFrame.vForward);
    cameraFrame.vForward = GLKVector3Normalize(vNewForward);
    }




void GLStonehenge::render(void)
    {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Set up camera transform
    GLKVector3 vUp;
    GLKVector3 vForward;
    GLKVector3 vLocalX = GLKVector3CrossProduct(cameraFrame.vUp, cameraFrame.vForward);
    GLKMatrix4 mTiltMatrix = GLKMatrix4MakeRotation(fTilt, vLocalX.x, vLocalX.y, vLocalX.z);
    
    vUp = GLKMatrix4MultiplyVector3(mTiltMatrix, cameraFrame.vUp);
    vForward = GLKMatrix4MultiplyVector3(mTiltMatrix, cameraFrame.vForward);

    GLKVector3 vLooking = GLKVector3Add(cameraFrame.vWhere, vForward);
    

    mCamera = GLKMatrix4MakeLookAt(cameraFrame.vWhere.x, cameraFrame.vWhere.y, cameraFrame.vWhere.z,
                                   vLooking.x, vLooking.y, vLooking.z,
                                   vUp.x, vUp.y, vUp.z);

        
        
    GLKMatrix4 matrixMVP = GLKMatrix4Multiply(mProjection, mCamera);
        
    // Set shader and transformation matrix
    glUseProgram(hShaderStones);
    glUniformMatrix4fv(hUniformStonesMVP, 1, GL_FALSE, matrixMVP.m);
    
    // Setup light in eye coordinates
    GLKVector3 vLightEye;
    GLKVector3 vLightWorld = { 1.0f, 1.0f, 1.0f };
    vLightWorld = GLKVector3Normalize(vLightWorld);
    vLightEye = GLKMatrix4MultiplyVector3(mCamera, vLightWorld);
    glUniform3fv(hUniformStonesLightDir, 1, vLightEye.v);
        
    GLKMatrix3 mNormal = GLKMatrix4GetMatrix3(mCamera);
    glUniformMatrix3fv(hUniformStonesNormalMatrix, 1, GL_FALSE, mNormal.m);
    
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureNormalMap.name);
    glActiveTexture(GL_TEXTURE0);
    
    
    glBindTexture(GL_TEXTURE_2D, textureStones.name);
    glBindVertexArrayOES(hVertexArrays[OBJECT_STONES_SMALL]);
    glDrawElements(GL_TRIANGLES, nNumIndexes[OBJECT_STONES_SMALL], GL_UNSIGNED_INT, 0);
    
    // Middle stones
    glBindTexture(GL_TEXTURE_2D, textureOtherStones.name);
    glBindVertexArrayOES(hVertexArrays[OBJECT_STONES_LARGE]);
    glDrawElements(GL_TRIANGLES, nNumIndexes[OBJECT_STONES_LARGE], GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, textureStones.name);
    glBindVertexArrayOES(hVertexArrays[OBJECT_STONES_OTHER]);
    glDrawElements(GL_TRIANGLES, nNumIndexes[OBJECT_STONES_OTHER], GL_UNSIGNED_INT, 0);
    
    
    ///////////////////////////////////////////////////
    // Ground
    glUseProgram(hShaderGround);
    glUniformMatrix4fv(hUniformGroundMVP, 1, GL_FALSE, matrixMVP.m);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureGroundDetail.name);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureGround.name);

    glBindVertexArrayOES(hVertexArrays[OBJECT_GROUND]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }