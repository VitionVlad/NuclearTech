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
    void vertexCollision(vec3 vertpos, vec3 &pos){
        if(inRange(vertpos.x-0.01,vertpos.x+0.01, pos.x)&&inRange(vertpos.z-0.01,vertpos.z+0.01, pos.z)&&inRange(vertpos.y-0.01,vertpos.y+0.1, pos.y)){
            pos.y = lastpos.y;
            colide = true;
            if(vertpos.y > pos.y){
                pos.x = lastpos.x;
                pos.z = lastpos.z;
            }
        }else{
            colide = false;
        }
    }
    void calculateCollision(vec3 vertex[9999999], int totalvertex, vec3 &pos){
        totalvertex = totalvertex + 3;
        for(int i = 1; i != totalvertex; i++){
            vertexCollision(vertex[i], pos);
        }
    }
};
