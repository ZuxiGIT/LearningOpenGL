#pragma once
#include "GLFW.hpp"
#include <string>

namespace GLFW
{
    class Window
    {
        GLFWwindow* m_window = nullptr;
        static bool glew_init;
    public:
        Window(const std::string title, int width, int height);
        Window(const Window&) = delete;
        Window& operator=(const Window& rhs) = delete;
        GLFWwindow* pointer();
        void setContextCurrent() { glfwMakeContextCurrent(m_window); }
        ~Window();
    };
}