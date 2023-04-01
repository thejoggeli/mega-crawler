#include "Vector3.h"
#include <Arduino.h>

Vector3::Vector3() : x(0.0), y(0.0), z(0.0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

void Vector3::print() const     {
    Serial.println(toString());
}

String Vector3::toString() const {
    String s = "(";
    s += "x: " + String(x,3) + ", ";
    s += "y: " + String(y,3) + ", ";
    s += "z: " + String(z,3);
    s += ")";
    return s;
}

Vector3& Vector3::rotateAroundX(float angle){
    float L = sqrt(y*y+z*z);
    float A = atan2(z, y) + angle;
    y = cos(A) * L;
    z = sin(A) * L; 
    return *this;
}

Vector3& Vector3::rotateAroundY(float angle){
    float L = sqrt(z*z+x*x);
    float A = atan2(x, z) + angle;
    z = cos(A) * L;
    x = sin(A) * L; 
    return *this;
}

Vector3& Vector3::rotateAroundZ(float angle){
    float L = sqrt(x*x+y*y);
    float A = atan2(y, x) + angle;
    x = cos(A) * L;
    y = sin(A) * L; 
    return *this;
}

Vector3& Vector3::operator = (const float val){
    x = val;
    y = val;
    z = val;
    return *this;
}

Vector3& Vector3::operator = (const Vector3& other){
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vector3& Vector3::operator += (const Vector3& other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}
Vector3& Vector3::operator -= (const Vector3& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}
Vector3& Vector3::operator *= (const Vector3& other){
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}
Vector3& Vector3::operator /= (const Vector3& other){
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector3& Vector3::operator += (const float val){
    x += val;
    y += val;
    z += val;
    return *this;
}
Vector3& Vector3::operator -= (const float val){
    x -= val;
    y -= val;
    z -= val;
    return *this;
}
Vector3& Vector3::operator *= (const float val){
    x *= val;
    y *= val;
    z *= val;
    return *this;
}
Vector3& Vector3::operator /= (const float val){
    float val_inv = 1.0/val;
    x *= val_inv;
    y *= val_inv;
    z *= val_inv;
    return *this;
}

float Vector3::dot(const Vector3& a, const Vector3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {
    return Vector3(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

float Vector3::getDistance(const Vector3& a, const Vector3& b){
    return (a-b).getLength();
}

float Vector3::getSquaredLength(){
    return x*x + y*y + z*z;
}

float Vector3::getLength(){
    return sqrt(x*x + y*y + z*z);
}

void Vector3::setLength(float length){
    float L = 1.0/getLength();
    x = x*L*length;
    y = y*L*length;
    z = z*L*length;
}