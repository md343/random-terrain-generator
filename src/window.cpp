#include "window.h"


Window::Window(int width, int height)
{
	// Initialize GLFW
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	
	ID = glfwCreateWindow(width, height, "WINDOW", NULL, NULL);
	if (ID == NULL)
	{
		glfwTerminate();
		open = false;
        return;
		//return NULL;
	}
	glfwMakeContextCurrent(ID);
	gladLoadGL();

	glViewport(0, 0, width, height);
};