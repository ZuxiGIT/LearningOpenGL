#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


namespace GLFW
{
    class GLFW
    {
    public:
        GLFW(const GLFW& GLFW) = delete;
        GLFW& operator=(const GLFW& rhs) = delete;
        GLFW();
        ~GLFW();
    };
}