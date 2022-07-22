#include <iostream>

#include <thread>

#include "Gui.hpp"

float pSpeed = 0.1;

MagmaVK render;

CollWork colision;

void movecallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_W && action == GLFW_REPEAT){
        render.pos.z += cos(render.rot.y) * cos(render.rot.x) * pSpeed;
        render.pos.x += cos(render.rot.y) * sin(render.rot.x) * -pSpeed;
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT){
        render.pos.x += cos(render.rot.y) * cos(render.rot.x) * pSpeed;
        render.pos.z -= cos(render.rot.y) * sin(render.rot.x) * -pSpeed;
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT){
        render.pos.z -= cos(render.rot.y) * cos(render.rot.x) * pSpeed;
        render.pos.x -= cos(render.rot.y) * sin(render.rot.x) * -pSpeed;
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT){
        render.pos.x -= cos(render.rot.y) * cos(render.rot.x) * pSpeed;
        render.pos.z += cos(render.rot.y) * sin(render.rot.x) * -pSpeed;
    }
}

class NuclearTechVk{
    private:
    vec2 oldpos;
    public:
    dvec2 rawm;
    vec2 speed;
    float sensivity = 1000;
    bool mouselook;
    bool collisionenable;
    bool enablephysics;
    vec2 mouseupdown = vec2(1.5, -1.5);
    void Init(){
        render.Init();
    }
    void objwork(const char* path, int begpos, vec3 pos){
        loadobj(path, render.vertex, render.totalv, begpos, pos);
    }
    void plywork(const char* path, int begpos, bool color, vec3 pos){
        switch(color){
            case 0:
            loadply(path, render.vertex, render.totalv, begpos, pos);
            break;
            case 1:
            loadplycolor(path, render.vertex, render.totalv, begpos, pos);
            break;
        }
    }
    void CreateProp(Prop prop, const char* pathtomodel, int modeltype, vec2 updown, vec2 border, float allwdown){
        prop.begpos = render.totalv;
        switch (modeltype){
        case 0:
        objwork(pathtomodel, render.totalv, vec3(0, 0, 0));
            break;
         case 1:
        plywork(pathtomodel, render.totalv, false, vec3(0, 0, 0));
            break;
         case 2:
        plywork(pathtomodel, render.totalv, true, vec3(0, 0, 0));
            break;
        default:
        throw runtime_error("Error: Unknown model type");
            break;
        }
        prop.pos = vec3(0, 0, 0);
        prop.finpos = render.totalv;
        prop.saveprop(render.vertex);
        prop.setsize(updown, border, allwdown);
    }
    float packColor(vec3 color) {
        if(color.r < 5){
            color.r = 5;
        }
        if(color.g < 5){
            color.g = 5;
        }
        if(color.b < 5){
            color.b = 5;
        }
    return color.r+(color.g*0.001)+(color.b*0.000001);
}
    void light(vec3 pos, float color, uint lightcnt){
        if(lightcnt > 100){
            throw runtime_error("Fatal light error");
        }else{
            render.ubo.massive[lightcnt] = vec4(pos.x, pos.y, pos.z, color);
        }
    }
    void Update(GLFWkeyfun keyfun){
        glfwSetKeyCallback(render.window, keyfun);
        glfwGetCursorPos(render.window, &rawm.x, &rawm.y);
        if(oldpos.x != render.pos.x && oldpos.y != render.pos.z){
            speed.x = render.pos.x - oldpos.x;
            speed.y = render.pos.z - oldpos.y; 
            oldpos.x = render.pos.x;
            oldpos.y = render.pos.z;
        }
        if(oldpos.x == render.pos.x && oldpos.y == render.pos.y){
            speed.x = 0;
            speed.y = 0;
        }
        if(collisionenable == true){
            colision.calculateCollision(render.vertex, render.totalv, render.pos);
        }
        if(mouselook == true){
            render.rot.x = rawm.x / sensivity;
            render.rot.y = -rawm.y / sensivity;
            if(render.rot.y < mouseupdown.y){
                render.rot.y = mouseupdown.y;
            }
            if(render.rot.y > mouseupdown.x){
                render.rot.y = mouseupdown.x;
            }
        }
        render.Draw();
        if(collisionenable == true){
            colision.updateLastCoord(render.pos);
        }
        if(enablephysics == true){
            colision.physwork(render.pos);
        }
    }
    void End(){
        render.Destroy();
    }
};
