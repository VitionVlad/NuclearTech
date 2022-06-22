#version 450

layout(binding = 0) uniform umvp {
    mat4 mvp;
} ubo;

layout(location = 0) in vec4 vertpos;

layout(location = 0) out vec3 vertcolor;

vec3 unpackColor(float f) {
    vec3 color;
    color.r = round(f);
    color.g = round((f-color.r)*1000);
    color.b = round((((f-color.r)*1000)-color.g)*1000)+2;
    return color / 255;
}

void main() {
    gl_Position = ubo.mvp * vec4(vertpos.x, -vertpos.y, vertpos.z, 1.0);
    vertcolor = unpackColor(vertpos.w);
}