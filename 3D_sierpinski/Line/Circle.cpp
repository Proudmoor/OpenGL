//
//  Circle.cpp
//  Assignment
//
//  Created by zpf on 14-12-18.
//
//

#include <stdio.h>
#include <GLUt/glut.h>

class screenPt
{
private:
    GLint x, y;
    
public:
    //initiallizes coordinate position to (0, 0)
    screenPt(){
        x = y =0;
    }
    
    void setCoords(GLint xCoordValue, GLint yCoordValue){
        x = xCoordValue;
        y = yCoordValue;
    }
    
    GLint getx() const {
        return x;
    }
    
    GLint gety() const {
        return y;
    }
    
    void incrementX () {
        x ++;
    }
    void decrementX () {
        y --;
    }
    
    
};