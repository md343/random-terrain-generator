#define NUM_PARTICLES 1024*4
#define WORK_GROUP_SIZE 1024
#define WRITELOG 0
#include"glad/glad.h"
#include<GLFW/glfw3.h>
#include"window.h"
#include<VAO.h>
#include<VBO.h>
#include<EBO.h>
#include<SSBO.h>
#include<shaderClass.h>
#include<Camera.h>
#include<texture.h>
#include<map.h>


#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
int width, height;


float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    width = 1024;
    height = 1024;

    Window window(width, height);
    if (window.open == false) return 0;

    Camera camera(width, height);
    Map map;
    
	VAO VAO1;

	VBO VBO1(map.vertices, sizeof(map.vertices));
	EBO EBO1(map.indices, sizeof(map.indices));
    std::cout << "0";
	VAO1.LinkAttrib(0, 3, GL_FLOAT, 0);
	VAO1.LinkAttrib(1, 3, GL_FLOAT, 3 * sizeof(float));

	VAO1.LinkVertBuffer(VBO1, 6 * sizeof(GLfloat));
	VAO1.LinkElemBuffer(EBO1);

    std::cout << "1";

    Shader vfShader("res/shaders/default.vert", "res/shaders/default.frag");
    std::cout << "2";

    unsigned int modelLoc = glGetUniformLocation(vfShader.ID, "model");
    unsigned int lightLoc = glGetUniformLocation(vfShader.ID, "lightPos");
    //unsigned int camMat = glGetUniformLocation(vfShader.ID, "camMat");
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 lightPos = glm::vec3(0.0, 2.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    std::cout << "TEST" << std::endl;
    while (!glfwWindowShouldClose(window.ID))
    {
        float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        camera.speed = 5.0f*deltaTime;
        camera.Inputs(window.ID);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        
        vfShader.Activate();

        camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(vfShader, "camMat");
        // if (glfwGetKey(window.ID, GLFW_KEY_U) == GLFW_PRESS)
        // {
        //     lightPos.x += 0.005;
        // }
        // if (glfwGetKey(window.ID, GLFW_KEY_J) == GLFW_PRESS)
        // {
        //     lightPos.x -= 0.005;
        // }
        // if (glfwGetKey(window.ID, GLFW_KEY_I) == GLFW_PRESS)
        // {
        //     lightPos.z += 0.005;
        // }
        // if (glfwGetKey(window.ID, GLFW_KEY_K) == GLFW_PRESS)
        // {
        //     lightPos.z -= 0.005;
        // }
        lightPos.x = 1.5*sin(2*currentFrame);
        lightPos.z = 1.5*cos(2*currentFrame);
        lightPos.y = 2 +sin(1.5*currentFrame);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(map.indices) / sizeof(map.indices[0]), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window.ID);
		glfwPollEvents();
        
    }
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	

	vfShader.Delete();


    glfwDestroyWindow(window.ID);
    glfwTerminate();
    return 0;
}
