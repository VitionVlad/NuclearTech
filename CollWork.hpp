#include <iostream>

#include <glm/glm.hpp>

using namespace std;

using namespace glm;

class CollWork{
    public:
    vec3 lastpos;
    bool colide;
    bool allowmove = true;
    void updateLastCoord(vec3 pos){
        lastpos = pos;
    }
    bool inRange(int low, int high, int mx){
        return ((mx-high)*(mx-low) <= 0);
    }
    void vertexCollision(vec4 vertpos, vec3 &pos){
        if(inRange(pos.x-0.1,pos.x+0.1, -vertpos.x)&&inRange(pos.z-0.1,pos.z+0.1, -vertpos.z)&&inRange(pos.y-1.8,pos.y+0.2, vertpos.y)){
            pos.y = lastpos.y;
            colide = true;
            if(vertpos.y > pos.y - 1.6){
                pos.x = lastpos.x;
                pos.z = lastpos.z;
            }
        }else{
            colide = false;
        }
    }
    void calculateCollision(vec4 *vertex, int totalvertex, vec3 &pos){
        totalvertex = totalvertex + 3;
        for(int i = 0; i != totalvertex; i++){
            vertexCollision(vertex[i], pos);
        }
    }
};
