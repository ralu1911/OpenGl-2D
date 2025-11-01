#pragma once
#include <math.h>

class Vector2
{
public:
		float x;
		float y;
    Vector2();
		Vector2(float, float);
    Vector2(const Vector2&);
		~Vector2();

    Vector2 operator=(const Vector2&);

		Vector2 operator +(const Vector2&) const;
    Vector2 operator +=(const Vector2&);
		Vector2 operator -(const Vector2&) const;
    Vector2 operator -=(const Vector2&);
		Vector2 operator *(const Vector2&) const;
    Vector2 operator *=(const Vector2&);
		Vector2 operator /(const Vector2&) const;
    Vector2 operator /=(const Vector2&);

    Vector2 operator +(const float&) const;
    Vector2 operator +=(const float&);
    Vector2 operator -(const float&) const;
    Vector2 operator -=(const float&);
		Vector2 operator *(const float&) const;
    Vector2 operator *=(const float&);
		Vector2 operator /(const float&) const;
    Vector2 operator /=(const float&);

    Vector2 Abs() const;
    float Lenght() const;
    Vector2 Normalize() const;
    float Dot(const Vector2&) const;
    float Angle(const Vector2&) const;
    float Distance(const Vector2&) const;

    static Vector2 Right();
    static Vector2 Up();
    static Vector2 Down();
    static Vector2 Left();
    static Vector2 Zero();


private:

};

