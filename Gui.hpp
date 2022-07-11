#include <iostream>

#include <glm/glm.hpp>

using namespace glm;

void GuiDrawTriangle(float packedcolor, vec2 v1, vec2 v2, vec2 v3, vec4 *vertex, int totalvert){
    vertex[totalvert] = vec4(v1.x, v1.y, packedcolor, 1000);
    vertex[totalvert+1] = vec4(v2.x, v2.y, packedcolor, 1000);
    vertex[totalvert+2] = vec4(v3.x, v3.y, packedcolor, 1000);
}
void GuiDrawRectangle(float packedcolor, vec2 v1, vec2 v2, vec2 v3, vec2 v4, vec4 *vertex, int totalvert){
    GuiDrawTriangle(packedcolor, v1, v2, v3, vertex, totalvert);
    GuiDrawTriangle(packedcolor, v1, v3, v4, vertex, totalvert+3);
}

class Button{
    private:
    int begpos;
    float mcolor = 255.0;
    float scolor = 0.255000;
    float pcolor = 0.000255;
    vec2 mousepos;
    public:
    bool pressed = false;
    vec2 v1 = vec2(-0.5, 0.5);
    vec2 v2 = vec2(0, 0.5);
    vec2 v3 = vec2(0, 0);
    vec2 v4 = vec2(-0.5, 0);
    void Setup(int &totalvert, float maincolor, float selectcolor, float presscolor){
        begpos = totalvert;
        totalvert += 6;
        mcolor = maincolor;
        scolor = selectcolor;
        pcolor = presscolor;
    }
    void Update(vec4 *vertex, dvec2 rawm, ivec2 resolution, int state){
        mousepos.x = rawm.x / (resolution.x / 2.f) - 1;
        mousepos.y = 1 - rawm.y / (resolution.y / 2.f);
        if(mousepos.x < v3.x && mousepos.y > v3.y && mousepos.x > v1.x && mousepos.y < v1.y && state != GLFW_PRESS){
            GuiDrawRectangle(scolor, v1, v2, v3, v4, vertex, begpos);
            pressed = false;
        }else if(mousepos.x < v3.x && mousepos.y > v3.y && mousepos.x > v1.x && mousepos.y < v1.y && state == GLFW_PRESS){
            GuiDrawRectangle(pcolor, v1, v2, v3, v4, vertex, begpos);
            pressed = true;
        }else{
            GuiDrawRectangle(mcolor, v1, v2, v3, v4, vertex, begpos);
            pressed = false;
        }
    }
};

class ProgressBar{
    private:
    int begpos;
    public:
    vec2 v1 = vec2(-1, -0.9);
    vec2 v2 = vec2(-1, -1);
    float color;
    void setup(int &totalvert, float maincolor){
        begpos = totalvert;
        totalvert += 6;
        color = maincolor;
    }
    void Update(vec4 *vertex, float value, float maxvalue){
        GuiDrawRectangle(color, v1, vec2((value/maxvalue)+v1.x, v1.y), vec2((value/maxvalue)+v2.x, v2.y), v2, vertex, begpos);
    }
};