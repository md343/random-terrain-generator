#define MAP_LENGTH 128
#define MAP_VERT MAP_LENGTH*MAP_LENGTH*6
#define MAP_IND (MAP_LENGTH-1)*(MAP_LENGTH-1)*6

#ifndef MAP_CLASS_H
#define MAP_CLASS_H


#include"glad/glad.h"
#include"PerlinNoise.hpp"
//#include<GLFW/glfw3.h>

//#include"glm/glm.hpp"

class Map
{
    public:
        GLuint vec = 6;
        GLuint dim = MAP_LENGTH;
        GLuint length = vec*dim;
        
        float centreX = 0;
        float centreY = 0;


        GLfloat vertices[MAP_VERT];//vec*dim^2
        GLuint indices[MAP_IND];//6*(dim-1)^2
        

        Map();

        

};



#endif
