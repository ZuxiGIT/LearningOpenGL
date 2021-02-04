#pragma once
#include <GLEW/glew.h>
#include <stdio.h>
#include <vector>

namespace GL {
    class VAO
    {
        GLuint m_VAO_ref = 0;
        std::vector<GLuint> m_VBO_buffers = {};
        GLuint m_indices_buffer = 0;
        GLuint m_indices_count = 0;
        GLuint m_vertex_count = 0;
        
        void bind()   { glBindVertexArray(m_VAO_ref); }
        void unbind() { glBindVertexArray(0); }
    public:
        VAO();
        VAO(const VAO& VAO) = delete;
        void operator=(const VAO& rhs) = delete;
        void draw(GLenum type = GL_TRIANGLES);
        void loadVertexData(const std::vector<float>& data);
        void loadIndices(const std::vector<unsigned int>& indices);
        ~VAO();
    };


}