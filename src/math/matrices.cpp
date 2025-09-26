#include <iostream>
#include <array>

class vec4f {
    public:
    std::array<float, 4>data;
    const void print();
    vec4f operator+(const vec4f& in);
    vec4f operator+=(const vec4f& in);
    vec4f operator-(const vec4f& in);
    vec4f operator-=(const vec4f& in);
};

const void vec4f::print() {
    for (int col = 0; col < 4; ++col) {
        std::cout << data[col] << std::endl;
    }
};

vec4f vec4f::operator+(const vec4f& in){
    return vec4f{{
        data[0] + in.data[0],
        data[1] + in.data[1],
        data[2] + in.data[2],
        data[3] + in.data[3]
    }};
}

vec4f vec4f::operator-(const vec4f& in){
    return vec4f{{
        data[0] - in.data[0],
        data[1] - in.data[1],
        data[2] - in.data[2],
        data[3] - in.data[3]
    }};
}

vec4f vec4f::operator+=(const vec4f& in){
    return vec4f{{
        data[0] += in.data[0],
        data[1] += in.data[1],
        data[2] += in.data[2],
        data[3] += in.data[3]
    }};
}

vec4f vec4f::operator-=(const vec4f& in){
    return vec4f{{
        data[0] -= in.data[0],
        data[1] -= in.data[1],
        data[2] -= in.data[2],
        data[3] -= in.data[3]
    }};
}

class mat4f {
    public:
    std::array<float, 16>data;
    const void print();
    mat4f operator+=(const mat4f& in);
};

const void mat4f::print() {
    // 0,4,8,12, 1,5,9,13, 2,6,10,14, 3,7,11,15
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            std::cout << data[col*4+row] << " ";
        }
        std::cout << std::endl;
    }
};

mat4f mat4f::operator+=(const mat4f& in) {
    return mat4f {
        data[0] += in.data[0],
        data[1] += in.data[1],
        data[2] += in.data[2],
        data[3] += in.data[3],
        data[4] += in.data[4],
        data[5] += in.data[5],
        data[5] += in.data[6],
        data[7] += in.data[7],
        data[8] += in.data[8],
        data[9] += in.data[9],
        data[10] += in.data[10],
        data[11] += in.data[11],
        data[12] += in.data[12],
        data[13] += in.data[13],
        data[14] += in.data[14],
        data[15] += in.data[15]
    };
}

mat4f mat4f::operator+=(const mat4f& in) {
    return mat4f {
        data[0] += in.data[0],
        data[1] += in.data[1],
        data[2] += in.data[2],
        data[3] += in.data[3],
        data[4] += in.data[4],
        data[5] += in.data[5],
        data[5] += in.data[6],
        data[7] += in.data[7],
        data[8] += in.data[8],
        data[9] += in.data[9],
        data[10] += in.data[10],
        data[11] += in.data[11],
        data[12] += in.data[12],
        data[13] += in.data[13],
        data[14] += in.data[14],
        data[15] += in.data[15]
    };
}
