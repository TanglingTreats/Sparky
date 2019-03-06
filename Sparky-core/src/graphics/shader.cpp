#include "shader.h"

namespace sparky { namespace graphics {

    Shader::Shader(const char* vertPath, const char* fragPath)
        : m_VertPath(vertPath), m_FragPath(fragPath)
    {
        m_ShaderID = load();
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ShaderID);
    }

    GLuint Shader::load()
    {

        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
       
        std::string vertSourceString = FileUtils::read_file(m_VertPath).c_str();
        const char* vertSource = vertSourceString.c_str();
        
        glShaderSource(vertex, 1, &vertSource, NULL);
        glCompileShader(vertex);

        GLint result;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertex, length, &length, &error[0]);

            std::cout << "Failed to compile vertex shader!" << &error[0] << std::endl;

            glDeleteShader(vertex);

            return 0;
        }

        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

        std::string fragSourceString = FileUtils::read_file(m_FragPath).c_str();
        const char* fragSource = fragSourceString.c_str();
        
        glShaderSource(fragment, 1, &fragSource, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragment, length, &length, &error[0]);

            std::cout << "Failed to compile fragment shader!" << &error[0] << std::endl;

            glDeleteShader(fragment);

            return 0;
        }


        GLuint program = glCreateProgram();

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);
        glValidateProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetProgramInfoLog(program, length, NULL, &error[0]);

            std::cout << "Failed to link shader program!" << &error[0] << std::endl;

            glDeleteProgram(program);

            return 0;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }

    GLint Shader::getUniformLocation(const GLchar* name)
    {
        return glGetUniformLocation(m_ShaderID, name);
    }

    void Shader::SetUniform1f(const GLchar* name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }
    void Shader::SetUniform1i(const GLchar* name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }
    void Shader::SetUniform2f(const GLchar* name, maths::vec2& vector)
    {
        glUniform2f(getUniformLocation(name), vector.x, vector.y);
    }
    void Shader::SetUniform3f(const GLchar* name, maths::vec3& vector)
    {
        glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
    }
    void Shader::SetUniform4f(const GLchar* name, maths::vec4& vector)
    {
        glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
    }
    void Shader::SetUniformMat4(const GLchar* name, maths::mat4& matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, false, matrix.elements);
    }

    void Shader::enable() const
    {
        glUseProgram(m_ShaderID);
    }

    void Shader::disable() const
    {
        glUseProgram(0);
    }

} }