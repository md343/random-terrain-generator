#include"map.h"
#include<iostream>
#include"texture.h"
#include <glm/glm.hpp>

Map::Map()
{
    std::cout << MAP_VERT << " " << MAP_IND << "\n";
	const siv::PerlinNoise::seed_type seed = 123456u;
	const siv::PerlinNoise perlin{ seed };

    int index;
    float x, y;
    //
    for (int i = 0; i<dim;i++)
    {
	    for (int j = 0; j<dim;j++)
        {
            index = i*dim*vec + j*vec;
            x = ((float)i/(dim-1))*2.0f-1.0f+centreX;
            y = ((float)j/(dim-1))*2.0f-1.0f+centreY;
            const double noise = perlin.octave2D_01(x, y, 8);

            vertices[index] = x;

            vertices[index+1] = noise;

            vertices[index+2] = y;
            
            //cout << vertices[index] << " " << vertices[index+1] << " " << vertices[index+2]<< "\n";
        }
    }

    //UVS
    int idx1, idx2, idy1, idy2;
    

    glm::vec3 dx, dy, normal;
    for (int i = 1; i<dim-1;i++)
    {
   
	    for (int j = 1; j<dim-1;j++)
        {

            index = i*dim*vec + j*vec;
            idx1 = (i-1)*dim*vec + j*vec;
            idx2 = (i+1)*dim*vec + j*vec;
            idy1 = i*dim*vec + (j-1)*vec;
            idy2 = i*dim*vec + (j+1)*vec;
            //std::cout << "2.3";
            //std::cout << i
            dx = glm::vec3((float)vertices[idx2],(float)vertices[idx2+1],(float)vertices[idx2+2])-glm::vec3((float)vertices[idx1],(float)vertices[idx1+1],(float)vertices[idx1+2]);
            dy = glm::vec3((float)vertices[idy2],(float)vertices[idy2+1],(float)vertices[idy2+2])-glm::vec3((float)vertices[idy1],(float)vertices[idy1+1],(float)vertices[idy1+2]);
            normal = -glm::normalize(glm::cross(dx, dy));
            //std::cout << "2.2";
            vertices[index+3] = normal.x;
            // cout << vertices[index] << "\n";
            // index = i*dim + j*vec;
            vertices[index+4] = normal.y;
            // vertices[index+1] = ((float)j/(dim-1))-0.5f;
            vertices[index+5] = normal.z;
            
            // cout << index << " ";
            //std::cout << vertices[index] << " " << vertices[index+1] << " " << vertices[index+2] << vertices[index+3] << " " << vertices[index+4] << " " << vertices[index+5]<< "\n";
        }
    }
    //std::cout << "2";
    int indind = 0;
    for (int i = 0; i<dim-1;i++)
    {
	    for (int j = 0; j<dim-1;j++)
        {
            index = (i*dim + j);
            
            indices[indind] = index;
            indices[indind+1] = index+1;
            indices[indind+2] = index+dim+1;
            //cout << indices[indind] << " " << indices[indind+1] << " " << indices[indind+2]<< "\n";
    
            indices[indind+3] =index;
            indices[indind+4] = index+dim+1;
            indices[indind+5] = index+dim;
            //cout << indices[indind+3] << " " << indices[indind+4] << " " << indices[indind+5]<< "\n";
            indind += 6;


        }
    }
    // for (int i = 0; i< MAP_IND;i++)
    // {
    //     cout << indices[i] << " ";
    // }
    //std::cout << "MAPPED" << "\n";
}



