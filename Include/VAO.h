#ifndef VAO_H
#define VAO_H

#include <C:/VSC_PRO_B/Tools/Include/glad/glad.h> // include glad to get all the required OpenGL headers
#include <rendering.h>

#include <string>
#include <vector>
using namespace std;

class VAO
{
    public:
    unsigned int ID = 0;
    unsigned int nInd = 0;
    unsigned int bufferOffset = 0;

    VAO();

    VAO(vector<float> vertices, vector<unsigned int> indices)
    {
        nInd = indices.size();

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &ID);

        // 1. bind Vertex Array Object
        glBindVertexArray(ID);
        // 2. copy our vertices array in a vertex buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        // 3. copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
        // 4. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)bufferOffset);
        glEnableVertexAttribArray(0);

        bufferOffset += vertices.size() * sizeof(float);
    }

    VAO(string shapePath)
    {
        vector<float> vertices = fileToVector<float>(shapePath + ".v");
        vector<unsigned int> indices = fileToVector<unsigned int>(shapePath + ".i");

        if(vertices.size() % 3 != 0)
            cout << "ERROR: Incorrect number of vertice components" << endl;
        if(indices.size() % 3 != 0)
            cout << "ERROR: Incorrect number of indices" << endl;
        
        nInd = indices.size();

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &ID);

        // 1. bind Vertex Array Object
        glBindVertexArray(ID);
        // 2. copy our vertices array in a vertex buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        // 3. copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
        // 4. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)bufferOffset);
        glEnableVertexAttribArray(0);

        bufferOffset += vertices.size() * sizeof(float);
    }

    void attachTexture(string texPath)
    {
        glBindVertexArray(ID);
        vector<float> textures = fileToVector<float>(texPath + ".t");
        if(textures.size() % 2 != 0)
            cout << "ERROR: Incorrect number of texture components" << endl;
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textures.size(), textures.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)bufferOffset);
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
        bufferOffset += textures.size() * sizeof(float);
    }
    
    void bind()
    {
        glBindVertexArray(ID);
    }
};

#endif