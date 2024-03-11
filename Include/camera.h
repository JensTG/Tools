#ifndef CAMERA
#define CAMERA
#include <rendering.h>
#include <glad/glad.h>

class camera
{
    public:
    vec3 cPos;
    vec3 cFront;
    vec3 cUp;

    float cYaw;
    float cPitch;
    float cRoll;

    float cLook;
    float cSpeed;

    mat4 view = mat4(1.0f);

    camera
    (
        float cl, float cs, 
        vec3 start = vec3(0.0f, 0.0f, 6.0f), 
        vec3 look = vec3(0.0f, 0.0f, -1.0f), 
        vec3 up = vec3(0.0f, 1.0f, 0.0f),
        float y = -90.0f, float p = 0.0f, float r = 0.0f
    ) 
    {
        cLook = cl;
        cSpeed = cs;

        cPos = start;
        cFront = look;
        cUp = up;

        cYaw = y;
        cPitch = p;
        cRoll = r;
    }

    void takeKeyLook(GLFWwindow* window, float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cPitch -= cLook * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cPitch += cLook * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cYaw += cLook * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cYaw -= cLook * deltaTime;

        cPitch = cPitch < -89.0f ? -89.0f : cPitch;
        cPitch = cPitch > 89.0f ? 89.0f : cPitch;

        cFront = vec3(cos(radians(cYaw)) * cos(radians(cPitch)), sin(radians(cPitch)), sin(radians(cYaw)) * cos(radians(cPitch)));
    }

    void takeMouseLook(GLFWwindow* window, float deltaTime)
    {

    }

    void takeMovement(GLFWwindow* window, float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cPos -= cFront * cSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cPos += cFront * cSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cPos += normalize(cross(cFront, cUp)) * cSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cPos -= normalize(cross(cFront, cUp)) * cSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            cPos -= normalize(cross(cross(cFront, cUp), cFront)) * cSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            cPos += normalize(cross(cross(cFront, cUp), cFront)) * cSpeed * deltaTime;
    }

    mat4 calculate()
    {
        return view = lookAt(cPos, cPos + cFront, cUp);
    }
};

#endif