#version 450

layout(binding = 0) uniform umvp {
    mat4 mvp;
    vec4 massive[100];
    vec3 pPos;
} ubo;

layout(binding = 1) uniform sampler2DArray texSampler;

layout(location = 0)in vec3 vertcolor;

layout(location = 1) in vec2 uvs;

layout(location = 2) in vec3 normal;

layout(location = 3) in vec3 crntPos;

layout(location = 4) in float param;

layout(location = 0) out vec4 outColor;

vec3 unpackColor(float f) {
    vec3 color;
    color.r = floor(f);
    color.g = floor((f-color.r)*1000);
    color.b = floor((((f-color.r)*1000)-color.g)*1000);
    return color / 255;
}

vec3 PointLight(vec4 pos, ivec2 textures){
    vec3 lightvec = pos.xyz - crntPos;
    float dist = length(lightvec);
    float a = 0.1f;
    float b = 0.06f;
    float inten = 1.0f / (a*dist*dist+b*dist+1.0f);
    float ambient = 0.01;
    vec3 finnorm = normalize(normal);
    vec3 lightdir = normalize(lightvec);
    float diffuse = max(dot(finnorm, lightdir), 0.0f);
    float specular = 0.5f;
    vec3 viewdir = normalize(vec3(-ubo.pPos.x, ubo.pPos.y, -ubo.pPos.z) - crntPos);
    vec3 reflectdir = reflect(-lightdir, finnorm);
    vec3 halfway = normalize(viewdir + lightdir);
    float specam = pow(max(dot(finnorm, halfway), 0.0f), 16);
    float fspecular = specam * specular;
    vec3 fincol = texture(texSampler, vec3(uvs, textures.x)).bgr * (diffuse*inten+ambient) + texture(texSampler, vec3(uvs, textures.y)).b * (fspecular * inten) * unpackColor(pos.w);
    return fincol;
}

void main() {

    ivec2 texNum;

    if(param == 0){
        texNum = ivec2(0, 1);
    }

    for(int i = 0; i != 10; i++){
        if(ubo.massive[i].w != 0){
            outColor = vec4(PointLight(ubo.massive[i], texNum), 1);
        }
    }
}
