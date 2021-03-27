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
            {
                fprintf(stderr, "GLEW::INITIALIZED\n");
                fprintf(stderr, "SYSTEM::INFO\n\n");

                const GLubyte *renderer = glGetString( GL_RENDERER );
                const GLubyte *vendor = glGetString( GL_VENDOR );
                const GLubyte *version = glGetString( GL_VERSION );
                const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
                
                GLint major, minor;
                glGetIntegerv(GL_MAJOR_VERSION, &major);
                glGetIntegerv(GL_MINOR_VERSION, &minor);
                
                printf("GL Vendor : %s\n", vendor);
                printf("GL Renderer : %s\n", renderer);
                printf("GL Version (string) : %s\n", version);
                printf("GL Version (integer) : %d.%d\n", major, minor);
                printf("GLSL Version : %s\n", glslVersion);

                GLint nExtensions;
                glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
                for( int i = 0; i < nExtensions; i++ )
                    printf("%s\n", glGetStringi( GL_EXTENSIONS, i ) );

                fprintf(stderr, "\n\n");
            }
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
    }
}