#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <C:/VSC_PRO_B/Tools/Include/glad/glad.h> // include glad to get all the required OpenGL headers

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
    Shader(const char* vertexPath, const char* fragmentPath) {
        // :::::::::: Get source code ::::::::::
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;
        // Ensure ifstreams can throw exceptions:
        vShaderFile.exceptions (ifstream::failbit | istream::badbit);
        fShaderFile.exceptions (ifstream::failbit | istream::badbit);
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
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
            cout << "ERROR: Soure file not succesfully read" << endl;
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
};

#endif