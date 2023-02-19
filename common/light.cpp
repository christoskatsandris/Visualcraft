#include "light.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Light::Light(GLFWwindow* window, glm::vec4 La, glm::vec4 Ld, glm::vec4 Ls, glm::vec3 position, float power, int SHADOW_WIDTH, int SHADOW_HEIGHT)
    : window(window), La(La), Ld(Ld), Ls(Ls), lightPosition_worldspace(position), power(power)
{
    rho = sqrt(pow(lightPosition_worldspace.x, 2) + pow(lightPosition_worldspace.y, 2) + pow(lightPosition_worldspace.z, 2));
    phiAngle = -acos(lightPosition_worldspace.z / rho);
    thetaAngle = atan(lightPosition_worldspace.y / lightPosition_worldspace.x);

    initialize(SHADOW_WIDTH, SHADOW_HEIGHT);
}

Light::Light(GLFWwindow* window, glm::vec4 La, glm::vec4 Ld, glm::vec4 Ls, float rho, float phi, float theta, float power, int SHADOW_WIDTH, int SHADOW_HEIGHT)
    : window(window), La(La), Ld(Ld), Ls(Ls), rho(rho), phiAngle(phi), thetaAngle(theta), power(power)
{
    lightPosition_worldspace = vec3(
        rho * sin(phi) * cos(theta),
        rho * sin(phi) * sin(theta),
        rho * cos(phi)
    );
    
    initialize(SHADOW_WIDTH, SHADOW_HEIGHT);
}

void Light::initialize(int SHADOW_WIDTH, int SHADOW_HEIGHT) {
    // setting near and far plane affects the detail of the shadow
    nearPlane = 1.0;
    farPlane = 3000.0;

    direction = normalize(targetPosition - lightPosition_worldspace);

    lightSpeed = 0.1f;
    targetPosition = glm::vec3(0.0, 0.0, 0.0);

    projectionMatrix = ortho(-100.0f, 100.0f, -100.0f, 100.0f, nearPlane, farPlane);
    orthoProj = true;

    glGenFramebuffers(1, &depthFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);							// Task 4.5 Texture wrapping methods
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);							// GL_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        glfwTerminate();
        throw std::runtime_error("Frame buffer not initialized correctly");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::update(vec3 cameraPosition) {
    //// Move across z-axis
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
    //    lightPosition_worldspace += lightSpeed * vec3(0.0, 0.0, 1.0);
    //}
    //if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
    //    lightPosition_worldspace -= lightSpeed * vec3(0.0, 0.0, 1.0);
    //}
    //// Move across x-axis
    //if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
    //    lightPosition_worldspace += lightSpeed * vec3(1.0, 0.0, 0.0);
    //}
    //if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
    //    lightPosition_worldspace -= lightSpeed * vec3(1.0, 0.0, 0.0);
    //}
    //// Move across y-axis
    //if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
    //    lightPosition_worldspace += lightSpeed * vec3(0.0, 1.0, 0.0);
    //}
    //if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
    //    lightPosition_worldspace -= lightSpeed * vec3(0.0, 1.0, 0.0);
    //}

    phiAngle += 0.0005f;
    if (phiAngle >= 2 * 3.14f) phiAngle = 0;

    lightPosition_worldspace = vec3(
        rho * sin(phiAngle) * cos(thetaAngle),
        rho * sin(phiAngle) * sin(thetaAngle),
        rho * cos(phiAngle)
    );

    lightPosition_worldspace += vec3(
        cameraPosition.x,
        0,
        cameraPosition.z
    );

    float absolute_light_x = lightPosition_worldspace.x - cameraPosition.x;

    // Update sky color to match daylight
    if (absolute_light_x > 4) {
        glClearColor(0.53f * (absolute_light_x / 22.0f), 0.81f * (absolute_light_x / 22.0f), 0.92f * (absolute_light_x / 22.0f), 0.5f);
    }
    else {
        glClearColor(0.53f * (4.0f / 22.0f), 0.81f * (4.0f / 22.0f), 0.92f * (4.0f / 22.0f), 0.5f);
    }

    // We have the direction of the light and the point where the light is looking at
    // We will use this information to calculate the "up" vector, 
    // just like we did with the camera

    direction = normalize(targetPosition - lightPosition_worldspace);

    // converting direction to cylidrical coordinates
    float x = direction.x;
    float y = direction.y;
    float z = direction.z;

    // We don't need to calculate the vertical angle

    float horizontalAngle;
    if (z > 0.0) horizontalAngle = atan(x / z);
    else if (z < 0.0) horizontalAngle = atan(x / z) + 3.1415f;
    else horizontalAngle = 3.1415f / 2.0f;

    // Right vector
    vec3 right(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    // Up vector
    vec3 up = cross(right, direction);

    viewMatrix = lookAt(
        lightPosition_worldspace,
        targetPosition,
        up
    );
}

void Light::uploadToShader(GLuint LaLocation, GLuint LdLocation, GLuint LsLocation, GLuint positionLocation, GLuint powerLocation) {
    glUniform4f(LaLocation, La.r, La.g, La.b, La.a);
    glUniform4f(LdLocation, Ld.r, Ld.g, Ld.b, Ld.a);
    glUniform4f(LsLocation, Ls.r, Ls.g, Ls.b, Ls.a);
    glUniform3f(positionLocation, lightPosition_worldspace.x, lightPosition_worldspace.y, lightPosition_worldspace.z);
    glUniform1f(powerLocation, power);
}
