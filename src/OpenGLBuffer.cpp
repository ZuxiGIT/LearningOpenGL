#include "OpenGLBuffer.hpp"
#include <stdio.h>

namespace GL
{
    
    VAO::VAO()
    {
        glGenVertexArrays(1, &m_VAO_ref);
    }

    void VAO::draw(GLenum type)
    {
        bind();
        if (m_indices_buffer)
        {
            glDrawElements(type, m_indices_count, GL_UNSIGNED_INT, 0);
            //fprintf(stderr, "DRAWELEMENTS\n");
            unbind();
            return;
        }
        fprintf(stderr, "DRAWARRAYS\n");
        glDrawArrays(type, 0, m_vertex_count);
        unbind();
    } 
    
    void VAO::loadVertexData(const std::vector<float>& data)
    {
        bind();
        GLuint vbo;
        
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float) , data.data(), GL_STATIC_DRAW);
        
        glVertexAttribPointer(m_VBO_buffers.size(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(m_VBO_buffers.size());
        
        if (!m_VBO_buffers.size())
        { 
            m_vertex_count = data.size() / 3;
            fprintf(stderr, "Vertex count : %u\n", m_vertex_count);
        }
        

        m_VBO_buffers.push_back(vbo);
        unbind();
    }

    void VAO::loadIndices(const std::vector<unsigned int>& indices)
    {
        bind();

        if(m_indices_buffer)
        {
            fprintf(stderr, "ERROR::ALREADY_LOADED_INDICES");
            return;
        }

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        m_indices_buffer = ebo;
        m_indices_count = indices.size();

        fprintf(stderr, "Indices count : %u\n", m_indices_count);
        
        unbind();
    }

    VAO::~VAO()
    {
        glDeleteBuffers(m_VBO_buffers.size(), m_VBO_buffers.data());
        glDeleteBuffers(1, &m_indices_buffer);
        glDeleteVertexArrays(1, &m_VAO_ref);
    }
}