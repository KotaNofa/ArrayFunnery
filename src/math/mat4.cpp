#include "mat4.h" 


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

vec4f vec4f::operator*=(const mat4f &in)
{
    vec4f orig = *this;
    for (int r = 0; r < 4; ++r) {
        data[r] =
            in.data[0*4 + r] * orig.data[0] +
            in.data[1*4 + r] * orig.data[1] +
            in.data[2*4 + r] * orig.data[2] +
            in.data[3*4 + r] * orig.data[3];
    }
    return *this;
}
mat4f::mat4f() {
    data = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
}

void mat4f::Scale(float amount) {

    mat4f temp;
    temp.data = {
        amount,0,0,0,
        0,amount,0,0,
        0,0,amount,0,
        0,0,0,1
    };
    
    *this *= temp;
}

void mat4f::Translate(float x, float y, float z) {
    mat4f temp;
    temp.data = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        x,y,z,1
    };
    *this *= temp;
}

void mat4f::RotateX(float x)
{
    mat4f temp;
    temp.data = {
        1,0,0,0,
        0,cos(x),sin(x),0,
        0,-sin(x),cos(x),0,
        0,0,0,1
    };
    *this *= temp;
}

void mat4f::RotateY(float y)
{
    mat4f temp;
    temp.data = {
        cos(y),0,-sin(y),0,
        0,1,0, 0,
        sin(y),0,cos(y),0,
        0,0,0,1
    };
    *this *= temp;
}

void mat4f::RotateZ(float z)
{
    mat4f temp;
    temp.data = {
        cos(z),sin(z),0,0,
        -sin(z),cos(z),0,0,
        0,0,1,0,
        0,0,0,1
    };
    *this *= temp;
}
void mat4f::Project(float fov, float aspect, float z_near, float z_far)
{
    mat4f temp;
    temp.data = {
        1/((aspect)*tan(fov/2)), 0,0,0,
        0,1/(tan(fov/2)),0,0,
        0,0,-(z_far + z_near)/(z_far-z_near),-1,
        0,0,(2*z_far*z_near)/(z_far-z_near),0
    };
    *this *= temp;
}

const void mat4f::print()
{
    // 0,4,8,12, 1,5,9,13, 2,6,10,14, 3,7,11,15
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            std::cout << data[col*4+row] << " ";
        }
        std::cout << std::endl;
    }
};

mat4f mat4f::operator*=(const mat4f& in) {
    mat4f temp = *this;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += temp.data[k*4 + row] * in.data[col*4 + k];
            }
            this->data[col*4 + row] = sum;
        }
    }
    return *this;
};

