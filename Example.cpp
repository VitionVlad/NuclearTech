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

    Prop prop1;
    prop1.begpos = render.totalv;
    Engine.plywork("App/Models/prop.ply", render.totalv, true, vec3(0, 0, 0));
    prop1.pos = vec3(0, 15, -3);
    prop1.finpos = render.totalv;
    prop1.saveprop(render.vertexpos);
    prop1.setsize(vec2(0.25, 0.25), vec2(1, 1), 0);

    while(!glfwWindowShouldClose(render.window)){
        glfwPollEvents();
        render.fov = usrfov;
        Engine.Update(movecallback);
        prop1.updateProp(render.vertexpos, render.pos, Engine.speed);
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
