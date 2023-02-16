#include "light.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Light::Light(GLFWwindow* window, glm::vec4 La, glm::vec4 Ld, glm::vec4 Ls, glm::vec3 position, float power)
    : window(window), La(La), Ld(Ld), Ls(Ls), lightPosition_worldspace(position), power(power)
{
    // setting near and far plane affects the detail of the shadow
    nearPlane = 1.0;
    farPlane = 30.0;

    rho = sqrt(pow(lightPosition_worldspace.x, 2) + pow(lightPosition_worldspace.y, 2) + pow(lightPosition_worldspace.z, 2));
    phiAngle = -acos(lightPosition_worldspace.z / rho);
    thetaAngle = atan(lightPosition_worldspace.y / lightPosition_worldspace.x);

    direction = normalize(targetPosition - lightPosition_worldspace);

    lightSpeed = 0.1f;
    targetPosition = glm::vec3(0.0, 0.0, 0.0);

    projectionMatrix = ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    orthoProj = true;
}

Light::Light(GLFWwindow* window, glm::vec4 La, glm::vec4 Ld, glm::vec4 Ls, float rho, float phi, float theta, float power)
    : window(window), La(La), Ld(Ld), Ls(Ls), rho(rho), phiAngle(phi), thetaAngle(theta), power(power)
{
    // setting near and far plane affects the detail of the shadow
    nearPlane = 1.0;
    farPlane = 30.0;

    lightPosition_worldspace = vec3(
        rho * sin(phi) * cos(theta),
        rho * sin(phi) * sin(theta),
        rho * cos(phi)
    );
    
    direction = normalize(targetPosition - lightPosition_worldspace);

    lightSpeed = 0.1f;
    targetPosition = glm::vec3(0.0, 0.0, 0.0);

    projectionMatrix = ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    orthoProj = true;
}

void Light::update() {
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

    // Update sky color to match daylight
    if (lightPosition_worldspace.x > 110) {
        glClearColor(0.53f * (lightPosition_worldspace.x / 700), 0.81f * (lightPosition_worldspace.x / 700), 0.92f * (lightPosition_worldspace.x / 700), 0.5f);
    }
    else {
        glClearColor(0.53f * (110.0f / 700.0f), 0.81f * (110.0f / 700.0f), 0.92f * (110.0f / 700.0f), 0.5f);
    }

    lightPosition_worldspace = vec3(
        rho * sin(phiAngle) * cos(thetaAngle),
        rho * sin(phiAngle) * sin(thetaAngle),
        rho * cos(phiAngle)
    );

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

mat4 Light::lightVP() {
    return projectionMatrix * viewMatrix;
}