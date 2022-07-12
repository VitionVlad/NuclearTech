#version 450

layout(binding = 0) uniform uniformbuf {
    mat4 mvp;
    vec4 v1;
    vec4 v2;
    vec4 v3;
    vec4 v4;
    vec4 v5;    
} ubo;

layout(location = 0) in vec4 vertpos;

layout(location = 0) out vec3 vertcolor;

layout(location = 1) out vec3 fragpos;

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
        vertcolor = unpackColor(vertpos.w);
        fragpos = vec3(vertpos.x, vertpos.y, vertpos.z);
    }
}
