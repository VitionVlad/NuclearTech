#version 450

layout(binding = 0) uniform uniformbuf {
    mat4 mvp;
    vec4 v1;
    vec4 v2;
    vec4 v3;
    vec4 v4;
    vec4 v5;    
} ubo;

layout(location = 0) in vec3 vertcolor;

layout(location = 1) in vec3 fragpos;

layout(location = 0) out vec4 outColor;

void main() {
    float ambient = 0.1;
    vec3 lpos = vec3(ubo.v1.x, ubo.v1.y, ubo.v1.z);
    vec3 fincol;
    float light = distance(lpos, fragpos);
    if(light < 5){
        fincol = vertcolor * 0.5;
    }else{
        fincol = vertcolor * ambient;
    }
    outColor = vec4(fincol.b, fincol.g, fincol.r, 1.0);
}
