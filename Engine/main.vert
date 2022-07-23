#version 450

layout(binding = 0) uniform umvp {
    mat4 mvp;
    vec4 massive[100];
    vec3 pPos;
} ubo;

layout(location = 0) in vec4 vertpos;

layout(location = 1) in ivec3 vertcol;

layout(location = 2) in vec3 normals;

layout(location = 3) in vec2 uv;

layout(location = 0) out vec3 vertcolor;

layout(location = 1) out vec2 uvs;

layout(location = 2) out vec3 normal;

layout(location = 3) out vec3 crntPos;

layout(location = 4) out float param;

vec3 unpackColor(float f) {
    vec3 color;
    color.r = floor(f);
    color.g = floor((f-color.r)*1000);
    color.b = floor((((f-color.r)*1000)-color.g)*1000);
    return color / 255;
}

void main() {
    if(vertpos.w == 1000){
        gl_Position = vec4(vertpos.x, -vertpos.y, 0, 1);
        vertcolor = unpackColor(vertpos.z);
    }else{
        gl_Position = ubo.mvp * vec4(vertpos.x, -vertpos.y, vertpos.z, 1.0);
        vertcolor = vertcol;
        param = vertpos.w;
    }
    uvs = uv;
    crntPos = vec3(mat4(1.0f)*vec4(vertpos.xyz, 1.0f));
    normal = normals;
}
