#pragma once
#include <GLEW/glew.h>
#include <string>
#include <fstream>

namespace GL{

    class Shader
    {
        GLuint m_shader_id = 0;
        std::string m_shader_code = {};
    public:
        enum TYPE
        {
            Vertex   = GL_VERTEX_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER, 
            NOT_DEFINED
        };

        Shader() = delete;
        Shader(TYPE tp) : m_type (tp) { m_shader_id = glCreateShader(m_type);}
        GLuint id() const { return m_shader_id; }
        void loadFromMemory(const char* shader_path);
        void loadFromFile  (const char* shader_path);
        ~Shader() { glDeleteShader(m_shader_id); }

    private:
        void compile() const { glCompileShader(m_shader_id); checkCompileErrors(); }
        void checkCompileErrors() const;
        TYPE m_type = NOT_DEFINED;
    };

    std::string TYPE2str(Shader::TYPE tp);

    class ShaderProgram
    {
        GLuint m_program_id = 0;

    public:
        ShaderProgram() = delete;
        ShaderProgram(const char* vertex_path, const char* fragment_path);
        ~ShaderProgram() { glDeleteProgram(m_program_id); }

        void use() const { glUseProgram(m_program_id); }

        void setBool (const char* name, bool val) const;
        void setInt  (const char* name, int val)  const;
        void setFloat(const char* name, float val)const;
    private:
        void checkLinkErrors() const;
    };

}