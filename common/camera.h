#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <vector>

class Camera {
public:
    GLFWwindow* window;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    // Initial position : on +Z
    glm::vec3 position, direction;
    // Initial horizontal angle : toward -Z
    float horizontalAngle;
    // Initial vertical angle : none
    float verticalAngle;
    // Field of View
    float FoV;
    float speed; // units / second
    float mouseSpeed;
    float fovSpeed;
    bool jump;
    int jumpSteps;
    std::vector<float> heightMap;

    Camera(GLFWwindow* window, glm::vec3 position, float horizontalAngle, float verticalAngle, std::vector<float> heightMap);
    void update(float columnHighestBlock, bool frontMoveAllowed, bool backMoveAllowed, bool rightMoveAllowed, bool leftMoveAllowed, bool jumpAlloweds);
};

#endif
