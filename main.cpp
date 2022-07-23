#include <iostream>

#include <NuclearTech/EngineVK.hpp>

NuclearTechVk Engine;

float usrfov = 110;

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    render.window = glfwCreateWindow(render.resolution.x, render.resolution.y, "", NULL, NULL);
    render.vshaderpath = "Engine/raw/vert.spv";
    render.fshaderpath = "Engine/raw/frag.spv";
    render.pos.y = 10;
    Engine.Init();
    Engine.objwork("App/Models/test.obj", 0, vec3(0, 0, 0), 0);
    glfwSetInputMode(render.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    string tittle;
    double currentTime;
    Engine.mouselook = true;
    Engine.collisionenable = true;
    Engine.enablephysics = true;
    pSpeed = 0.5;
    Engine.light(vec3(0, 2, 0), 100.100100, 1);

    while(!glfwWindowShouldClose(render.window)){
        glfwPollEvents();
        render.fov = usrfov;
        Engine.Update(movecallback);
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
