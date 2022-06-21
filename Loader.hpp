#include <iostream>

#include <cstring>

#include <stdio.h>

#include <fstream>

#include <glm/glm.hpp>

using namespace std;

using namespace glm;

vec3 lvertex[9999999];

ivec3 lvertexcol[9999999];

int indices[9999999];

void loadobj(const char* path, vec3 *vertex, int &totalvert, int begvertpos){
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

void loadply(const char* path, vec3 *vertex, int &totalvert, int begvertpos){
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
	}
	for(int i = 0; i != faceline*3; i+=3){
		int p;
		fscanf(obj, "%d %d %d %d", &p, &indices[i], &indices[i+1], &indices[i+2]);
	}
	fclose(obj);
    for(int i = 0; i != faceline*3; i++){
        vertex[i+begvertpos] = lvertex[indices[i]];
        totalvert++;
    }
}

void loadplycolor(const char* path, vec3 *vertex, ivec3 *vertexcol, int &totalvert, int begvertpos){
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
		int g;
		fscanf(obj, "%f %f %f %d %d %d %d", &lvertex[i].x, &lvertex[i].y, &lvertex[i].z, &lvertexcol[i].x, &lvertexcol[i].y, &lvertexcol[i].z, &g);
	}
	for(int i = 0; i != faceline*3; i+=3){
		int p;
		fscanf(obj, "%d %d %d %d", &p, &indices[i], &indices[i+1], &indices[i+2]);
	}
	fclose(obj);
    for(int i = 0; i != faceline*3; i++){
        vertex[i+begvertpos] = lvertex[indices[i]];
		vertexcol[i+begvertpos] = lvertexcol[indices[i]];
        totalvert++;
    }
}
