#include <iostream>

#include <glm/glm.hpp>

using namespace std;

using namespace glm;

class CollWork{
    public:
    vec3 lastpos;
    void updateLastCoord(vec3 pos){
        lastpos = pos;
    }
    bool inRange(int low, int high, int mx){
        return ((mx-high)*(mx-low) <= 0);
    }
    void vertexCollision(vec3 vertpos, vec3 &pos){
        if(inRange(vertpos.x-0.02,vertpos.x+0.02, pos.x)&&inRange(vertpos.y-0.02,vertpos.y+0.02, pos.y)&&inRange(vertpos.z-0.02,vertpos.z+0.02, pos.z)){
            pos = lastpos;
        }
    }
    void calculateCollision(vec3 vertex[9999999], int totalvertex, vec3 &pos){
        totalvertex = totalvertex + 3;
        for(int i = 1; i != totalvertex; i++){
            vertexCollision(vertex[i], pos);
        }
    }
};