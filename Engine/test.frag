#version 450

layout(location = 0) in vec3 vertcolor;

layout(location = 1) in vec3 lightpos;

layout(location = 0) out vec4 outColor;

void main() {
    float ambient = 0.1;
    vec3 fincol = vertcolor * ambient;
    outColor = vec4(fincol.b, fincol.g, fincol.r, 1.0);
}
