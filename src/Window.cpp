#include "Window.hpp"

namespace GLFW
{
    bool Window::glew_init = false;

    Window::Window(const std::string title, int width, int height)
    {
        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        
        if(!m_window)
        {
            fprintf(stderr, "Failed to create GLFW window\n");
            fprintf(stderr, "Press any button\n");
            getchar();
            exit(1);
        }

        setContextCurrent();

        if(!glew_init)
        {
            //fprintf(stderr, "GLEW::INITIALIZING\n");
            glew_init = true;
            glewExperimental = GL_TRUE;
            GLenum err = glewInit();
            if (err != GLEW_OK)
            {
                /* Problem: glewInit failed, something is seriously wrong. */
                fprintf(stderr, "GLEW::INITIALIZING::ERROR: %s\n", glewGetErrorString(err));
                getchar();
            }
            else
                fprintf(stderr, "GLEW::INITIALIZED\n");
        }
    }

    GLFWwindow* Window::pointer()
    {
        return m_window;
    } 

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
    }
}