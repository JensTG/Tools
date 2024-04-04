#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>

#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
    public:
        // Data:
        vector<Vertex>*         vertices;
        vector<unsigned int>*   indices;
        vector<Texture>*        textures;

        // Funcs:
        Mesh(vector<Vertex>* vertices, vector<unsigned int>* indices, vector<Texture>* textures) {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
        }

        void Draw(Shader &shader) {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            for(int i = 0; i < textures->size(); i++) 
            {
                glActiveTexture(GL_TEXTURE0 + i); // Activate relevant texture

                // Get texture number:
                string number;
                string name = textures->at(i).type;
                if(name == "texture_diffuse")
                    number = to_string(diffuseNr++);
                if(name == "texture_specular")
                    number = to_string(specularNr++);

                shader.setInt(("material." + name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, textures->at(i).id);
            }
            glActiveTexture(GL_TEXTURE0);

            // Draw:
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    private:
        // Buffer IDs:
        unsigned int VAO, VBO, EBO;

        void setupMesh() {
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            glGenVertexArrays(1, &VAO);

            glBindVertexArray(VAO); // Bind Vertex Array Object
            
            // Bind Vertex data to OpenGL
            // Size is sizeof Vertex times amount of "points"
            // Start at the first vertice as this is the first element in Vertex
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

            // Copy our index array in a element buffer for OpenGL to use
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices->size(), indices->data(), GL_STATIC_DRAW);

            // Set attribute pointers:
            // Positions:
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(0);
            // Normals:
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            glEnableVertexAttribArray(0);
            // TexCoords:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
            glEnableVertexAttribArray(0);
            
            glBindVertexArray(0);
        }
};
#endif