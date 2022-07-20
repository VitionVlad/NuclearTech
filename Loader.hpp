#include <iostream>

#include <cstring>

#include <stdio.h>

#include <fstream>

#include <glm/glm.hpp>

using namespace std;

using namespace glm;

vec4 lvertex[9999999];

ivec3 lvertexcol[9999999];

int indices[9999999];

void loadobj(const char* path, vec4 *vertex, int &totalvert, int begvertpos, vec3 pos){
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
			lvertex[line].w = 1;
			line++;
		}

		if (strcmp(lineHeader, "f") == 0) {
			fscanf(obj, "%d %d %d \n", &indices[faceline], &indices[faceline+1], &indices[faceline+2]);
			faceline = faceline + 3;
		}
	}
	fclose(obj);
    for(int i = 0; i != faceline; i++){
        vertex[i+begvertpos].x = lvertex[indices[i]].x + pos.x;
		vertex[i+begvertpos].y = lvertex[indices[i]].y + pos.y;
		vertex[i+begvertpos].z = lvertex[indices[i]].z + pos.z;
		vertex[i+begvertpos].w = 1.0f;
        totalvert++;
    }
}

void loadply(const char* path, vec4 *vertex, int &totalvert, int begvertpos, vec3 pos){
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

		if (strcmp(lineHeader, "coment") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "ply") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "property") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "element") == 0) {
			char ele[128];
			int arg;
			fscanf(obj, "%s %d", ele, &arg);
			if(strcmp(ele, "vertex") == 0){
				line = arg;
			}
			if(strcmp(ele, "face") == 0){
				faceline = arg;
			}
		}
		if (strcmp(lineHeader, "end_header") == 0) {
			break;
		}
	}
	for(int i = 0; i != line; i++){
		fscanf(obj, "%f %f %f", &lvertex[i].x, &lvertex[i].y, &lvertex[i].z);
		lvertex[i].w = 1;
	}
	for(int i = 0; i != faceline*3; i+=3){
		int p;
		fscanf(obj, "%d %d %d %d", &p, &indices[i], &indices[i+1], &indices[i+2]);
	}
	fclose(obj);
    for(int i = 0; i != faceline*3; i++){
        vertex[i+begvertpos].x = lvertex[indices[i]].x + pos.x;
		vertex[i+begvertpos].y = lvertex[indices[i]].y + pos.y;
		vertex[i+begvertpos].z = lvertex[indices[i]].z + pos.z;
		vertex[i+begvertpos].w = 1.0f;
        totalvert++;
    }
}

float packColor(vec3 color) {
	if(color.r < 5){
		color.r = 5;
	}
	if(color.g < 5){
		color.g = 5;
	}
	if(color.b < 5){
		color.b = 5;
	}
    return color.r+(color.g*0.001)+(color.b*0.000001);
}

void loadplycolor(const char* path, vec4 *vertex, int &totalvert, int begvertpos, vec3 pos){
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

		if (strcmp(lineHeader, "coment") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "ply") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "property") == 0) {
			fscanf(obj, "%*[^\n]\n");
		}

		if (strcmp(lineHeader, "element") == 0) {
			char ele[128];
			int arg;
			fscanf(obj, "%s %d", ele, &arg);
			if(strcmp(ele, "vertex") == 0){
				line = arg;
			}
			if(strcmp(ele, "face") == 0){
				faceline = arg;
			}
		}
		if (strcmp(lineHeader, "end_header") == 0) {
			break;
		}
	}
	for(int i = 0; i != line; i++){
		int a;
		fscanf(obj, "%f %f %f %d %d %d %d", &lvertex[i].x, &lvertex[i].y, &lvertex[i].z, &lvertexcol[i].x, &lvertexcol[i].y, &lvertexcol[i].z, &a);
	}
	for(int i = 0; i != faceline*3; i+=3){
		int p;
		fscanf(obj, "%d %d %d %d", &p, &indices[i], &indices[i+1], &indices[i+2]);
	}
	fclose(obj);
    for(int i = 0; i != faceline*3; i++){
        vertex[i+begvertpos].x = lvertex[indices[i]].x + pos.x;
		vertex[i+begvertpos].y = lvertex[indices[i]].y + pos.y;
		vertex[i+begvertpos].z = lvertex[indices[i]].z + pos.z;
		vertex[i+begvertpos].w = packColor(lvertexcol[indices[i]]);
        totalvert++;
    }
}
