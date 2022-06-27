#include <iostream>

#include "CollWork.hpp"

vec4 propvertex[9999999];

class Prop{
    private:
    bool inRange(int low, int high, int mx){
        return ((mx-high)*(mx-low) <= 0);
    }
    vec2 yr;
    vec2 xzr;
    public:
    int begpos;
    int finpos;
    vec3 pos;
    CollWork propcolision;
    bool enablep = true;
    bool enablec = true;
    bool enablepi = true;
    bool enablepip = true;
    bool playerinteracted;
    void setsize(vec2 updown, vec2 border, float allwdown){
        propcolision.borders = border;
        propcolision.height = updown.y;
        propcolision.uph = updown.x;
        propcolision.allowdown = allwdown;
    }
    void saveprop(vec4 *vertex){
        for(int i = begpos; i != finpos; i++){
            propvertex[i].x = vertex[i].x;
            propvertex[i].y = vertex[i].y;
            propvertex[i].z = vertex[i].z;
        }
    }
    void changepos(vec4 *vertex){
        for(int i = begpos; i != finpos; i++){
            vertex[i].x = propvertex[i].x + pos.x;
            vertex[i].y = propvertex[i].y + pos.y;
            vertex[i].z = propvertex[i].z + pos.z;
        }
    }
    void updateProp(vec4 *vertex, vec3 pPos, vec2 speed){
        if(enablec == true){
            propcolision.calculateCollision(vertex, begpos, pos);
            propcolision.updateLastCoord(pos);
        }
        if(enablep == true){
            propcolision.physwork(pos);
        }
        changepos(vertex);
        if(inRange(pPos.z - propcolision.borders.y-1, pPos.z + propcolision.borders.y+1, -pos.z)&&inRange(pPos.x - propcolision.borders.x-1, pPos.x + propcolision.borders.x+1, -pos.x)&&enablepi==true){
            if(enablepip == true){
                pos.z-=speed.y;
                pos.x-=speed.x;
            }
            playerinteracted = true;
        }else{
            playerinteracted = false;
        }
    }
};
