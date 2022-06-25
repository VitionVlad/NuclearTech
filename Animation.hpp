#include <iostream>

#include <glm/glm.hpp>

#include "Loader.hpp"

using namespace std;

using namespace glm;

class Animation{
    private:
    int totalvertex = 0;
    bool calctotalv = false;
    public:
    int begpos;
    int framecount = 0;
    string animfiles[60] = {
        "App/Models/prop.ply",
        "App/Models/propa1.ply"
    };
    int format = 2;
    int totalframes = 1;
    void Play(vec3 pos, vec4 *vertex, int &totalv){
        switch(format){
            case 0:
            loadobj(animfiles[framecount].c_str(), vertex, totalvertex, begpos, pos);
            framecount++;
            break;
            case 1:
            loadply(animfiles[framecount].c_str(), vertex, totalvertex, begpos, pos);
            framecount++;
            break;
            case 2:
            loadplycolor(animfiles[framecount].c_str(), vertex, totalvertex, begpos, pos);
            framecount++;
            break;
            default:
            throw runtime_error("Unknown format");
            break;
        }
        if(framecount == totalframes){
            framecount = 0;
        }
        if(calctotalv == false){
            totalv += totalvertex;
            calctotalv = true;
        }
    }
};