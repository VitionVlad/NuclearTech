#include <iostream>

#include <thread>

#include <MagmaVK/MagmaVK.hpp>

#include "Prop.hpp"

#include "Animation.hpp"

MagmaVK render;

CollWork colision;

void movecallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_W && action == GLFW_REPEAT){
        render.pos.z = render.pos.z + 0.1;
        render.pos.x = render.pos.x - render.rot.x / 10;
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT){
        render.pos.x = render.pos.x + 0.1;
        render.pos.z = render.pos.z + render.rot.x / 10;
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT){
        render.pos.z = render.pos.z - 0.1;
        render.pos.x = render.pos.x + render.rot.x / 10;
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT){
        render.pos.x = render.pos.x - 0.1;
        render.pos.z = render.pos.z - render.rot.x / 10;
    }
}

class NuclearTechVk{
    private:
    vec2 oldpos;
    dvec2 rawm;
    public:
    vec2 speed;
    float sensivity = 1000;
    bool mouselook;
    bool collisionenable;
    bool enablephysics;
    void Init(){
        render.Init();
    }
    void objwork(const char* path, int begpos, vec3 pos){
        loadobj(path, render.vertexpos, render.totalv, begpos, pos);
    }
    void plywork(const char* path, int begpos, bool color, vec3 pos){
        switch(color){
            case 0:
            loadply(path, render.vertexpos, render.totalv, begpos, pos);
            break;
            case 1:
            loadplycolor(path, render.vertexpos, render.totalv, begpos, pos);
            break;
        }
    }
    void Update(GLFWkeyfun keyfun){
        glfwSetKeyCallback(render.window, keyfun);
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
            colision.calculateCollision(render.vertexpos, render.totalv, render.pos);
        }
        if(mouselook == true){
            glfwGetCursorPos(render.window, &rawm.x, &rawm.y);
            render.rot.x = rawm.x / sensivity;
            render.rot.y = -rawm.y / sensivity;
            if(render.rot.x < -1.4){
                render.rot.x = -1.38;
            }
            if(render.rot.x > 1.4){
                render.rot.x = 1.38;
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
