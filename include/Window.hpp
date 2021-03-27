#pragma once
#include "GLFW.hpp"
#include <string>

namespace GLFW
{
    class Window
    {
        static bool glew_init;
    public:
        GLFWwindow* m_window = nullptr;
        Window(const std::string title, int width, int height);
        Window(const Window&) = delete;
        Window& operator=(const Window& rhs) = delete;
        void setContextCurrent() { glfwMakeContextCurrent(m_window); }
        ~Window();
    };
}