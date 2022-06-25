#include <iostream>

#include "EngineVK.hpp"

NuclearTechVk Engine;

float usrfov = 110;

int main(){
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    render.window = glfwCreateWindow(render.resolution.x, render.resolution.y, "", NULL, NULL);
    render.vshaderpath = "Engine/raw/vert.spv";
    render.fshaderpath = "Engine/raw/frag.spv";
    render.pos.y = 10;
    Engine.Init();
    Engine.plywork("App/Models/untitled.ply", 0, true, vec3(0, 0, 0));
    glfwSetInputMode(render.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    string tittle;
    double currentTime;
    Engine.mouselook = true;
    Engine.collisionenable = true;
    Engine.enablephysics = true;
    Animation anim1;
    anim1.begpos = render.totalv;
    anim1.totalframes = 2;
    while(!glfwWindowShouldClose(render.window)){
        glfwPollEvents();
        render.fov = usrfov;
        Engine.Update(movecallback);
        anim1.Play(vec3(0, 2, -3), render.vertexpos, render.totalv);
        currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){
            tittle = to_string(nbFrames);
            glfwSetWindowTitle(render.window, tittle.c_str());
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    Engine.End();
    glfwDestroyWindow(render.window);
}
