#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "camera.h"

#define GRID_SIZE 700

using namespace std;
using namespace glm;

Camera::Camera(GLFWwindow* window, vec3 position, float horizontalAngle, float verticalAngle, vector<float> heightMap, bool freeMovement)
    : window(window), position(position), horizontalAngle(horizontalAngle), verticalAngle(verticalAngle), heightMap(heightMap), freeMovement(freeMovement) {
    FoV = 45.0f;
    speed = 6.0f;
    mouseSpeed = 0.001f;
    fovSpeed = 2.0f;
    jump = false;
    jumpSteps = 0;
}

void Camera::update(float columnHighestBlock, bool frontMoveAllowed, bool backMoveAllowed, bool rightMoveAllowed, bool leftMoveAllowed, bool jumpAllowed) {
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Get mouse position
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Reset mouse position for next frame
    glfwSetCursorPos(window, width / 2, height / 2);
    
    // Compute new horizontal and vertical angles, given windows size and cursor position
    horizontalAngle += mouseSpeed * float(width / 2 - xPos);
    if (verticalAngle < -1.57f) verticalAngle = -1.57f;
    if (verticalAngle > 1.57f) verticalAngle = 1.57f;
    if (verticalAngle >= -1.57f && verticalAngle <= 1.57f) {
        verticalAngle += mouseSpeed * float(height / 2 - yPos);
    }
    
    // Right and up vectors of the camera coordinate system -- use spherical coordinates
    direction = vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    vec3 right(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    // Up vector
    vec3 up = cross(right, direction);

    if (freeMovement) {
        // Simple camera movement that moves in +-z and +-x axes
        // Move forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position -= vec3(0, 0, 1) * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position += vec3(0, 0, 1) * deltaTime * speed;
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position += vec3(1, 0, 0) * deltaTime * speed;
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position -= vec3(1, 0, 0) * deltaTime * speed;
        }
    }
    else {
        // Camera movement that moves based on direction/right vectors, and obeys terrain
        // Fall down
        if (columnHighestBlock + 1.2 < position.y && !jump) {
            position -= vec3(0, 1, 0) * deltaTime * speed;
        }
        // Jump
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && jumpAllowed && columnHighestBlock + 1.2 >= position.y) {
            jump = true;
        }
        if (jump) {
            float coeff = 1 - 0.03f * jumpSteps;
            position += vec3(0, 1, 0) * deltaTime * coeff * speed;
            jumpSteps++;
            if (jumpSteps == 10) {
                jump = false;
                jumpSteps = 0;
            }
        }

        // Task 5.5: update camera position using the direction/right vectors
        // Move forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && frontMoveAllowed) {
            position += vec3(direction.x, 0, direction.z) * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && backMoveAllowed) {
            position -= vec3(direction.x, 0, direction.z) * deltaTime * speed;
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && rightMoveAllowed) {
            position += vec3(right.x, 0, right.z) * deltaTime * speed;
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && leftMoveAllowed) {
            position -= vec3(right.x, 0, right.z) * deltaTime * speed;
        }
    }
    

    // Handle zoom in/out effects
    //if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    //    //FoV -= fovSpeed;
    //    position += vec3(0, 1, 0) * deltaTime * speed;
    //}
    //if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    //    //FoV += fovSpeed;
    //    position -= vec3(0, 1, 0) * deltaTime * speed;
    //}

    // Construct projection and view matrices
    projectionMatrix = perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = lookAt(
        position,
        position + direction,
        up
    );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}
