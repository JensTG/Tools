#include <stdlib.h>
#include <vector>
#include <shader.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

struct DirectLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
struct PointLight {
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
struct SpotLight {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    glm::vec3 position;
    glm::vec3 direction;

    float cutOff;
    float outerCutOff;
};

void applyLights(vector<DirectLight> dLights, vector<PointLight> pLights, vector<SpotLight> sLights, Shader &shader) {
    for(unsigned int i = 0; i < dLights.size(); i++) {
        string lightIndex = string("dLights[").append(to_string(i)).append("].");

        shader.setVec3(lightIndex + "direction", dLights[i].direction);
        shader.setVec3(lightIndex + "ambient", dLights[i].ambient);
        shader.setVec3(lightIndex + "diffuse", dLights[i].diffuse);
        shader.setVec3(lightIndex + "specular", dLights[i].specular);
    }

    for(unsigned int i = 0; i < pLights.size(); i++) {
        string lightIndex = string("pLights[").append(to_string(i)).append("].");

        shader.setVec3(lightIndex + "position", pLights[i].position);
        shader.setVec3(lightIndex + "ambient", pLights[i].ambient);
        shader.setVec3(lightIndex + "diffuse", pLights[i].diffuse);
        shader.setVec3(lightIndex + "specular", pLights[i].specular);

        shader.setFloat(lightIndex + "constant", pLights[i].constant);
        shader.setFloat(lightIndex + "linear", pLights[i].linear);
        shader.setFloat(lightIndex + "quadratic", pLights[i].quadratic);
    }

    for(unsigned int i = 0; i < sLights.size(); i++) {
        string lightIndex = string("sLights[").append(to_string(i)).append("].");

        shader.setVec3(lightIndex + "direction", sLights[i].direction);
        shader.setVec3(lightIndex + "position", sLights[i].position);
        shader.setVec3(lightIndex + "ambient", sLights[i].ambient);
        shader.setVec3(lightIndex + "diffuse", sLights[i].diffuse);
        shader.setVec3(lightIndex + "specular", sLights[i].specular);

        shader.setFloat(lightIndex + "cutOff", sLights[i].cutOff);
        shader.setFloat(lightIndex + "outerCutOff", sLights[i].outerCutOff);
    }
}