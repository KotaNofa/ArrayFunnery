#ifndef MAT4_H
#define MAT4_H

#include <iostream>
#include <array>

class mat4f {
    public:
    std::array<float, 16>data;
    mat4f();
    void Scale(float amount);
    void Translate(float x, float y, float z);
    void Project(float fov, float aspect, float z_near, float z_far);
    const void print();
    mat4f operator*=(const mat4f& in);
};

class vec4f {
    public:
    std::array<float, 4>data;
    const void print();
    vec4f operator+(const vec4f& in);
    vec4f operator+=(const vec4f& in);
    vec4f operator-(const vec4f& in);
    vec4f operator-=(const vec4f& in);
    vec4f operator*=(const mat4f& in); 
};

#endif