#include <stdio.h>
#define GLEW_STATIC
#include "GLFW.hpp"
#include "Window.hpp"

#include "OpenGLShader.hpp"
#include "OpenGLBuffer.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);




int main(void)
{

    /* Initialize the library */
    GLFW::GLFW lib;

    GLFW::Window win ("OpenGL", 800, 600);


    GL::ShaderProgram shaderProgram( "shaders/vertexShader.txt",
                                    "shaders/fragmentShader.txt");

    GL::VAO vao;

    std::vector<float> vertices = 
    {
        // positions       
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };
    
    std::vector<float> colors = 
    {
        // color
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f
    };
    
    vao.loadVertexData(vertices);
    vao.loadVertexData(colors);
    

    std::vector<unsigned int> indices = 
    {
        0, 1, 3,
        1, 2, 3
    }; 
    
    vao.loadIndices(indices);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    fprintf(stderr,"Maximum nr of vertex attributes supported: %d\n", nrAttributes);

/*
    printf("%s\n", VertexShaderCode);
    printf("%s\n", fragmentShaderCode);
*/

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    while(!glfwWindowShouldClose(win.pointer()))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        // float timeValue = (float)glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.draw();
        glfwSwapBuffers(win.pointer());
        glfwPollEvents();
    }

    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO); 
    
    
    glfwTerminate();

    return 0;
}
