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
    float rho, phiAngle, thetaAngle;

    glm::vec4 La, Ld, Ls;

    float power;

    float nearPlane, farPlane;
    bool orthoProj;

    float lightSpeed;
    glm::vec3 direction;

    GLuint depthFramebuffer;
    GLuint depthTexture;

    // Where the light will look at
    glm::vec3 targetPosition;

    // Constructor with cartesian coordinates
    Light(GLFWwindow* window, glm::vec4 La, glm::vec4 Ld, glm::vec4 Ls, glm::vec3 position, float power, int SHADOW_WIDTH, int SHADOW_HEIGHT);

    // Constructor with spherical coordinates
    Light(GLFWwindow* window, glm::vec4 La, glm::vec4 Ld, glm::vec4 Ls, float rho, float phi, float theta, float power, int SHADOW_WIDTH, int SHADOW_HEIGHT);

    void initialize(int SHADOW_WIDTH, int SHADOW_HEIGHT);
    void update(glm::vec3 cameraPosition);
    void uploadToShader(GLuint LaLocation, GLuint LdLocation, GLuint LsLocation, GLuint positionLocation, GLuint powerLocation);
};

#endif