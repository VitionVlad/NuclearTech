#include <iostream>

#include <MagmaVK/MagmaVK.hpp>

#include "Loader.hpp"

#include "CollWork.hpp"

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
    dvec2 rawm;
    public:
    float sensivity = 1000;
    void Init(){
        render.Init();
    }
    void objwork(const char* path, int begpos){
        loadobj(path, render.vertexpos, render.totalv, begpos);
        render.CreateVertexInput();
    }
    void Update(GLFWkeyfun keyfun, bool mouselook){
        glfwSetKeyCallback(render.window, keyfun);
        colision.calculateCollision(render.vertexpos, render.totalv, render.pos);
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
        colision.updateLastCoord(render.pos);
    }
    void End(){
        render.Destroy();
    }
};