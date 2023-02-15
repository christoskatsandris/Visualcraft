#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Light {
public:
    GLFWwindow* window;

    // Light parameters
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 lightPosition_worldspace;

    glm::vec4 La, Ld, Ls;

    float power;

    float nearPlane;
    float farPlane;

    bool orthoProj;

    float lightSpeed;
    glm::vec3 direction;

    // Where the light will look at
    glm::vec3 targetPosition;

    // Constructor
    Light(GLFWwindow* window, glm::vec4 La, glm::vec4 Ld, glm::vec4 Ls, glm::vec3 position, float power);

    void update();
    void uploadToShader(GLuint LaLocation, GLuint LdLocation, GLuint LsLocation, GLuint positionLocation, GLuint powerLocation);

    glm::mat4 lightVP();
};

#endif