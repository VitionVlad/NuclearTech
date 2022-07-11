#version 450

layout(binding = 0) uniform umvp {
    mat4 mvp;
} ubo;

layout(location = 0) in vec4 vertpos;

layout(location = 0) out vec3 vertcolor;

layout(location = 1) out vec3 lightpos;

vec3 unpackColor(float f) {
    vec3 color;
    color.r = floor(f);
    color.g = floor((f-color.r)*1000);
    color.b = floor((((f-color.r)*1000)-color.g)*1000);
    return color / 255;
}

void main() {
    if(vertpos.w == 1000){
        gl_Position = vec4(vertpos.x, vertpos.y, 0, 1);
        vertcolor = unpackColor(vertpos.z);
    }else if(vertpos.w == 2000){
        lightpos = vec3(vertpos.x, vertpos.y, vertpos.z);
    }else{
        gl_Position = ubo.mvp * vec4(vertpos.x, -vertpos.y, vertpos.z, 1.0);
        vertcolor = unpackColor(vertpos.w);
    }
}
