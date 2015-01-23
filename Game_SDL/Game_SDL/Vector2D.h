//
//  Vector2D.h
//  Game_SDL
//
//  Created by zpf on 15-1-21.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __Game_SDL__Vector2D__
#define __Game_SDL__Vector2D__

#include <stdio.h>
#include <math.h>

class Vector2D {
public:
    Vector2D(float x, float y): m_x(x), m_y(y) {
        
    }
    
    float getX() {
        return m_x;
    }
    
    float getY() {
        return m_y;
    }
    
    void setX(float x) {
        m_x = x;
    }
    
    void setY(float y) {
        m_y = y;
    }
    
    float length() {return sqrtf(m_x * m_x + m_y * m_y);}
    
    void normalize() {
        float l = length();
        if (l >0) {
            (*this) *= 1/l;
        }
    }
    
    Vector2D operator + (const Vector2D& v2) const {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }
    
    friend Vector2D& operator +=(Vector2D& v1, const Vector2D& v2) {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;
        
        return v1;
    }
    
    Vector2D operator *(float scalar) {
        return Vector2D (m_x * scalar, m_y * scalar);
    }
    
    Vector2D operator *= (float scalar) {
        m_x *= scalar; m_y *= scalar;
        
        return *this;
    }
    
    Vector2D operator -(const Vector2D& v2) const {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }
    
    friend Vector2D& operator -=(Vector2D& v1, const Vector2D& v2) {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;
        return v1;
    }
    
    Vector2D operator /(float scalar) {
        return Vector2D(m_x / scalar, m_y /scalar);
    }
    
    Vector2D& operator /=(float scalar) {
        m_x /= scalar; m_y /= scalar;
        
        return *this;
    }
    
private:
    float m_x, m_y;
};

#endif /* defined(__Game_SDL__Vector2D__) */
