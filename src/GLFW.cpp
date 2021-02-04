#include "GLFW.hpp"
#include <stdlib.h>
#include <stdio.h>

namespace GLFW
{
    GLFW::GLFW()
    {
        if (!glfwInit())
        {
            fprintf(stderr, "GLFW::INITIALIZING::FAILED");
            fprintf(stderr, "Press any button\n");
            getchar();            
            exit(1);
        }
        fprintf(stderr, "GLFW::INITIALIZED\n");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

    GLFW::~GLFW()
    {
        glfwTerminate();
    }
}