#version 450

layout(location = 0) in vec3 vertcolor;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(vertcolor.b, vertcolor.g, vertcolor.r, 1.0);
}