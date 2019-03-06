#pragma once

#include <iostream>
#include <vector>
#include <GL\glew.h>
#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace sparky { namespace graphics {

    class Shader
    {
    public:
        GLuint m_ShaderID;      //take in shader id everytime we do something with it
        const char* m_VertPath;
        const char* m_FragPath;

    public:
        Shader(const char* vertPath, const char* fragPath);
        ~Shader();
        
        void SetUniform1f(const GLchar* name, float value);
        void SetUniform1i(const GLchar* name, int value);
        void SetUniform2f(const GLchar* name, maths::vec2& vector);
        void SetUniform3f(const GLchar* name, maths::vec3& vector);
        void SetUniform4f(const GLchar* name, maths::vec4& vector);
        void SetUniformMat4(const GLchar* name, maths::mat4& matrix);

        void enable() const;
        void disable() const;

    private:
        GLuint load();
        GLint getUniformLocation(const GLchar* name);
    };

} }