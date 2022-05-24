#include <iostream>

#include <cstring>

#include <glm/glm.hpp>

using namespace std;

vec3 lvertex[9999999];

int indices[9999999];

void loadobj(const char* path, vec3 vertex[9999999], int &totalvert, int begvertpos){
    FILE* obj;
	//fopen(obj, path, "r");
    obj = fopen(path, "r");
	string arg;
	int line = 1;
	int faceline = 0;
	while (1) {
		char lineHeader[128];

		if (obj == 0) {
			exit(-1);
		}

		int res = fscanf(obj, "%s", lineHeader);
		if (res == EOF) {
			break;
		}

		if (strcmp(lineHeader, "#") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "s") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "o") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "v") == 0) {
			fscanf(obj, "%f %f %f \n", &lvertex[line].x, &lvertex[line].y, &lvertex[line].z);
			line++;
		}

		if (strcmp(lineHeader, "f") == 0) {
			fscanf(obj, "%d %d %d \n", &indices[faceline], &indices[faceline+1], &indices[faceline+2]);
			faceline = faceline + 3;
		}
	}
	fclose(obj);
    for(int i = 0; i != faceline; i++){
        vertex[i+begvertpos] = lvertex[indices[i]];
        totalvert++;
    }
}