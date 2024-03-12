#ifndef SHADER_H
#define SHADER_H

#include <C:/VSC_PRO_B/Tools/Include/glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(string vertexPath, string fragmentPath, bool fullPath = false) {
        // :::::::::: Get source code ::::::::::
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;
        // Ensure ifstreams can throw exceptions:
        vShaderFile.exceptions (ifstream::failbit | istream::badbit);
        fShaderFile.exceptions (ifstream::failbit | istream::badbit);
        if(!fullPath)
        {
            string shaderPath = "C:/VSC_PRO_B/OpenGL/resources/shaders/";
            vertexPath = shaderPath.append(vertexPath.append(".v"));
            shaderPath = "C:/VSC_PRO_B/OpenGL/resources/shaders/";
            fragmentPath = shaderPath.append(fragmentPath.append(".f"));
        }
        try
        {
            vShaderFile.open(vertexPath.c_str());
            fShaderFile.open(fragmentPath.c_str());
            stringstream vShaderStream, fShaderStream;
            // Read contents:
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // Close files:
            vShaderFile.close();
            fShaderFile.close();
            // Convert to string:
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(ifstream::failure e)
        {
            cout << "ERROR: Source file not succesfully read" << endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // :::::::::: Compiling ::::::::::
        unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER), vShader = glCreateShader(GL_VERTEX_SHADER);
        ID = glCreateProgram();
        char infoLog[512];
        int success;

        glShaderSource(vShader, 1, &vShaderCode, NULL);
        glCompileShader(vShader);
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
        if(!success) 
        {
            glGetShaderInfoLog(vShader, 512, NULL, infoLog);
            cout << "ERROR: Vertex shader was not compiled correctly" << endl << infoLog << endl;
        }

        glShaderSource(fShader, 1, &fShaderCode, NULL);
        glCompileShader(fShader);
        glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
        if(!success) 
        {
            glGetShaderInfoLog(fShader, 512, NULL, infoLog);
            cout << "ERROR: Fragment shader was not compiled correctly" << endl << infoLog << endl;
        }

        glAttachShader(ID, vShader);
        glAttachShader(ID, fShader);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success) 
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            cout << "ERROR: Shader program was not compiled correctly" << endl << infoLog << endl;
        }
    }
    // use/activate the shader
    void use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setVec2(const std::string& name, glm::vec2 value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }
    void setVec3(const std::string& name, glm::vec3 value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }
    void setMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
};

#endif