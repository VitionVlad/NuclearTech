#version 450

layout(binding = 0) uniform umvp {
    mat4 mvp;
    vec4 massive[100];
} ubo;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) flat in ivec3 vertcolor;

layout(location = 1) in vec3 normal;

layout(location = 2) in vec2 uvs;

layout(location = 0) out vec4 outColor;

void main() {
    float ambient = 0.1;
    vec3 fincol = vertcolor/255;
    //outColor = vec4(fincol, 1);
    outColor = texture(texSampler, uvs);
}