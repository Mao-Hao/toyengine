#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
    // state
    unsigned int ID;
    // constructor
    Shader()
        : ID(0)
    {
    }
    // TODO: move it to resource manager
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // DEBUG:
            //std::cout << "vertex shader: " << vertexPath << std::endl
            //          << vShaderStream.str() << std::endl;
				
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // sets the current shader as active
    Shader& Use()
    {
        glUseProgram(this->ID);
        return *this;
    }

    // compiles the shader from given source code
    void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr)
    {
        unsigned int sVertex, sFragment, gShader;
        // vertex Shader
        sVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(sVertex, 1, &vertexSource, NULL);
        glCompileShader(sVertex);
        checkCompileErrors(sVertex, "VERTEX");
        // fragment Shader
        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(sFragment, 1, &fragmentSource, NULL);
        glCompileShader(sFragment);
        checkCompileErrors(sFragment, "FRAGMENT");
        // if geometry shader source code is given, also compile geometry shader
        if (geometrySource != nullptr) {
            gShader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(gShader, 1, &geometrySource, NULL);
            glCompileShader(gShader);
            checkCompileErrors(gShader, "GEOMETRY");
        }
        // shader program
        this->ID = glCreateProgram();
        glAttachShader(this->ID, sVertex);
        glAttachShader(this->ID, sFragment);
        if (geometrySource != nullptr)
            glAttachShader(this->ID, gShader);
        glLinkProgram(this->ID);
        checkCompileErrors(this->ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(sVertex);
        glDeleteShader(sFragment);
        if (geometrySource != nullptr)
            glDeleteShader(gShader);
    }

    // utility functions
    void SetFloat(const char* name, float value, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform1f(glGetUniformLocation(this->ID, name), value);
    }

    void SetInteger(const char* name, int value, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform1i(glGetUniformLocation(this->ID, name), value);
    }

    void SetVector2f(const char* name, float x, float y, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->ID, name), x, y);
    }

    void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
    }

    void SetVector3f(const char* name, float x, float y, float z, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
    }

    void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
    }

    void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
    }

    void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
    }

    void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false)
    {
        if (useShader)
            this->Use();
        glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
    }

private:
    // checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(object, 1024, NULL, infoLog);
                std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- "
                          << std::endl;
            }
        } else {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(object, 1024, NULL, infoLog);
                std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- "
                          << std::endl;
            }
        }
    }
};
