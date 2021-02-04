#include "OpenGLShader.hpp"

namespace GL{

    void Shader::loadFromMemory(const char* shader_code)
    {
        glShaderSource(m_shader_id, 1, &shader_code, nullptr);

        compile();
    }
    //TODO using ifstream or stat stbuf with calloc???? 
    void Shader::loadFromFile(const char* shader_path)
    {
        std::string result;

        std::ifstream file_input(shader_path, std::ios_base::in | std::ios_base::binary);
        if(!file_input.is_open())
        {   
            fprintf(stderr, "ERROR::SHADER::%s::FILE_READING_FAILED\n", TYPE2str(m_type).c_str());
            return;
        }

        file_input.seekg(0, std::ios_base::end);
        result.resize(static_cast<size_t>(file_input.tellg()));
        file_input.seekg(0, std::ios_base::beg);
        file_input.read(&result[0], result.size());
        file_input.close();

    /*
        while(getline(finput, tmp))
            string += (tmp + '\n');

        const char* shader_code = string.c_str();
        fprintf(stderr, "READ SHADER %s \n %s\n-------\n", TYPE2str(m_type).c_str(), shader_code_Cstr);
    */

        const GLchar* shader_code_Cstr = result.c_str();
        glShaderSource(m_shader_id, 1, &shader_code_Cstr, nullptr);
        
        m_shader_code = result;

        compile();
    }

    void Shader::checkCompileErrors() const 
    {
        GLint success;
        char infoLog[512];
        glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(m_shader_id, 512, nullptr, infoLog);
            fprintf(stderr, "ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", TYPE2str(m_type).c_str(), infoLog);
        }
    }

    std::string TYPE2str(Shader::TYPE tp)
    {
        std::string shader_type;
        switch(tp){
            case Shader::Vertex:
                shader_type = "VERTEX";
                break;
            case Shader::Fragment:
                shader_type = "FRAGMENT";
                break;
            case Shader::Geometry:
                shader_type = "GEOMETRY";
                break;
            default:
                shader_type = "NOT DEFINED";
                break;  
        }
        return shader_type;
    }
    //-------------------------------------------------------------------------------
    ShaderProgram::ShaderProgram(const char* vertex_path, const char* fragment_path)
    {
        Shader vertex(Shader::Vertex), fragment(Shader::Fragment);
        vertex.loadFromFile(vertex_path);
        fragment.loadFromFile(fragment_path);

        m_program_id = glCreateProgram();
        glAttachShader(m_program_id, vertex.id());
        glAttachShader(m_program_id, fragment.id());
        glLinkProgram(m_program_id);

        checkLinkErrors();

        glDetachShader(m_program_id, vertex.id());
        glDetachShader(m_program_id, fragment.id());
    }

    void ShaderProgram::setBool(const char* name, bool val) const
    {
        glUniform1i(glGetUniformLocation(m_program_id, name), (int)val);
    }

    void ShaderProgram::setInt(const char* name, int val) const
    {
        glUniform1i(glGetUniformLocation(m_program_id, name), val);
    }

    void ShaderProgram::setFloat(const char* name, float val) const
    {
        glUniform1f(glGetUniformLocation(m_program_id, name), val);
    }

    void ShaderProgram::checkLinkErrors() const
    {
        GLint success;
        char infoLog[512];
        glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_program_id, 512, nullptr, infoLog);
            fprintf(stderr, "ERROR:PROGRAM::LINK::LINKING_FAILED\n%s\n", infoLog);
        }
    }

}