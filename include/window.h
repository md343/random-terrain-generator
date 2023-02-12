#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include"glad/glad.h"
#include<GLFW/glfw3.h>

class Window
{
    public:
        GLFWwindow* ID;
        bool open = true;

        Window(int width, int height);

};

#endif