#include <iostream>

#include "EngineVK.hpp"

NuclearTechVk Engine;

float usrfov = 110;

int main(){
    glfwInit();
    //yes, you need to init window
    glfwWindowHint(GLFW_RESIZABLE, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    render.window = glfwCreateWindow(render.resolution.x, render.resolution.y, "", NULL, NULL);
    //just some init shit
    render.totalv = 0;
    render.pos.z = -8;
    //engine init
    Engine.Init();
    //obj load example
    //theoreticaly you can do this each frame, but it will be slow, it should go after engine init
    Engine.objwork("App/test.obj", 0);
    glfwSetInputMode(render.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //some bullshit to write fps into tittle bar
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    string tittle;
    double currentTime;
    while(!glfwWindowShouldClose(render.window)){
        //poll events
        glfwPollEvents();
        //writing your fov and drawing frame
        render.fov = usrfov;
        Engine.Update(movecallback, true);
        //writing fps into tittle bar
        currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){
            tittle = to_string(nbFrames);
            glfwSetWindowTitle(render.window, tittle.c_str());
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    //destroyng everything
    Engine.End();
    glfwDestroyWindow(render.window);
}
