#include <iostream>

#include "EngineVK.hpp"

NuclearTechVk Engine;

float usrfov = 110;

int main(){
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    render.window = glfwCreateWindow(render.resolution.x, render.resolution.y, "", NULL, NULL);
    render.totalv = 0;
    render.pos.z = -8;
    Engine.Init();
    Engine.objwork("App/test.obj", 0);
    glfwSetInputMode(render.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    string tittle;
    double currentTime;
    while(!glfwWindowShouldClose(render.window)){
        glfwPollEvents();
        render.fov = usrfov;
        Engine.Update(movecallback, true);
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