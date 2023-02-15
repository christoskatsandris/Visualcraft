// Include C++ headers
#include <iostream>
#include <string>
#include <vector>

// Include GLEW, GLFW, GLM
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include utilities
#include <common/camera.h>
#include <common/model.h>
#include <common/PerlinNoise.h>
#include <common/shader.h>
#include <common/texture.h>
#include <common/util.h>

// Include models
#include "voxel.h"
#include "object.h"
#include "animal.h"

// Using directives
using namespace std;
using namespace glm;

// Function prototypes
void initialize();
void prepareShaders();
void createModels();
void calculateVoxelPositions();
void calculateTreePositions();
void calculateRockPositions();
//void calculateCowPositions();
//void calculateDogPositions();
void determineNeighbors();
void createContext();
void mainLoop();
void free();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
Camera* setCameraLocation(float x, float z);
float getColumnHighestBlock(int x_quantized, int z_quantized);
void getBlockPositionFromCoordinates(float x, float z, int* out_x, int* out_z);
int generateRandomNumber(int start, int end);
void allowCameraMove(int thisx, int thisz, bool* out_front, bool* out_back, bool* out_right, bool* out_left, bool* out_jump);

// Global definitions
#define W_WIDTH 1024
#define W_HEIGHT 768
#define W_TITLE "Visualcraft"
#define GRID_SIZE 700

// Global variables
GLFWwindow* window;
GLuint shaderProgram, objectProgram;
Camera* camera;

// Object models
Voxel* voxelModel;
//vector<vector<bool>> neighbors(GRID_SIZE*GRID_SIZE);
Object* treeModel, * rockModel;
//Animal* cowModel, * dogModel;

// GLSL variables: Uniform variable locations
GLuint modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation;
GLuint objectIDLocation;

// GLSL variables: Textures and samplers
GLuint textureAtlas;
GLuint shaderTextureAtlasSampler, objectTextureAtlasSampler;

void prepareShaders() {
    // Create and compile our GLSL program from the shaders
    shaderProgram = loadShaders("Shader.vertexshader", "Shader.fragmentshader");
    objectProgram = loadShaders("Object.vertexshader", "Object.fragmentshader");

    // Load texture maps
    textureAtlas = loadSOIL("../assets/textures/block/texture_atlas.png");

    // Get a pointer to the texture samplers
    shaderTextureAtlasSampler = glGetUniformLocation(shaderProgram, "textureAtlasSampler");
    objectTextureAtlasSampler = glGetUniformLocation(objectProgram, "textureAtlasSampler");

    // Get a pointer location to model matrix in the vertex shader
    modelMatrixLocation = glGetUniformLocation(shaderProgram, "M");
    viewMatrixLocation = glGetUniformLocation(shaderProgram, "V");
    projectionMatrixLocation = glGetUniformLocation(shaderProgram, "P");

    objectIDLocation = glGetUniformLocation(objectProgram, "objectID");

    // Draw wire frame triangles or fill: GL_LINE or GL_FILL
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void createModels() {
    voxelModel = new Voxel(0, 0, 0);
    cout << endl << "========= Tree =========" << endl;
    treeModel = new Object("../assets/models/tree.obj", 5, 5, 5, 1000);
    cout << endl << "========= Rock =========" << endl;
    rockModel = new Object("../assets/models/rock.obj", 1, 1, 1, 45);
    //cout << endl << "========= Cow  =========" << endl;
    //cowModel = new Animal();
    //cout << endl << "========= Dog  =========" << endl;
    //dogModel = new Animal();
    voxelModel->heightMap = createPerlinNoise(GRID_SIZE, GRID_SIZE, GRID_SIZE);
    camera = setCameraLocation(0, 0);
    calculateVoxelPositions();
    calculateTreePositions();
    calculateRockPositions();
    //calculateCowPositions();
    //calculateDogPositions();
    //determineNeighbors();
}

void calculateVoxelPositions() {
    for (int x = -GRID_SIZE / 2; x < GRID_SIZE / 2; x++) {
        for (int z = -GRID_SIZE / 2; z < GRID_SIZE / 2; z++) {
            voxelModel->positions.push_back(vec3(x, 0, z));
        }
    }
}

void calculateTreePositions() {
    int howManyTrees = GRID_SIZE / 5;
    for (int x = -GRID_SIZE / 2.5f; x < GRID_SIZE / 2.5f; x += 5) {
        for (int z = -GRID_SIZE / 2.5f; z < GRID_SIZE / 2.5f; z += 5) {
            if (x == 0 && z == 0) {
                continue;
            }
            float currentHeight = voxelModel->heightMap[(x + GRID_SIZE / 2) * GRID_SIZE + (z + GRID_SIZE / 2)];
            float neighborP1P0Height = voxelModel->heightMap[(x + 1 + GRID_SIZE / 2) * GRID_SIZE + (z + GRID_SIZE / 2)];
            float neighborP2P0Height = voxelModel->heightMap[(x + 2 + GRID_SIZE / 2) * GRID_SIZE + (z + GRID_SIZE / 2)];
            float neighborM1P0Height = voxelModel->heightMap[(x - 1 + GRID_SIZE / 2) * GRID_SIZE + (z + GRID_SIZE / 2)];
            float neighborM2P0Height = voxelModel->heightMap[(x - 2 + GRID_SIZE / 2) * GRID_SIZE + (z + GRID_SIZE / 2)];
            float neighborP0P1Height = voxelModel->heightMap[(x + GRID_SIZE / 2) * GRID_SIZE + (z + 1 + GRID_SIZE / 2)];
            float neighborP0P2Height = voxelModel->heightMap[(x + GRID_SIZE / 2) * GRID_SIZE + (z + 2 + GRID_SIZE / 2)];
            float neighborP0M1Height = voxelModel->heightMap[(x + GRID_SIZE / 2) * GRID_SIZE + (z - 1 + GRID_SIZE / 2)];
            float neighborP0M2Height = voxelModel->heightMap[(x + GRID_SIZE / 2) * GRID_SIZE + (z - 2 + GRID_SIZE / 2)];
            if (currentHeight < -8 && neighborP1P0Height == currentHeight && neighborP2P0Height == currentHeight && neighborM1P0Height == currentHeight && neighborM2P0Height == currentHeight && neighborP0P1Height == currentHeight && neighborP0P2Height == currentHeight && neighborP0M1Height == currentHeight && neighborP0M2Height == currentHeight) {
                treeModel->positions.push_back(vec3(x, 0, z));
                treeModel->heightMap.push_back(currentHeight);
            }
        }
    }

    treeModel->evaluateMap(GRID_SIZE);
}

void calculateRockPositions() {
    int howManyRocks = 1000;

    for (int i = 0; i < howManyRocks; i++) {
        int x = generateRandomNumber(-GRID_SIZE / 2, GRID_SIZE / 2 - 1);
        int z = generateRandomNumber(-GRID_SIZE / 2, GRID_SIZE / 2 - 1);
        float currentHeight = voxelModel->heightMap[(x + GRID_SIZE / 2) * GRID_SIZE + (z + GRID_SIZE / 2)];

        if (currentHeight < -4) {
            rockModel->positions.push_back(vec3(x, 0, z));
            rockModel->heightMap.push_back(currentHeight);
        }
    }

    rockModel->evaluateMap(GRID_SIZE);
}

//void calculateCowPositions() {
//    cowModel->positions.push_back(vec3(26, 0, 26));
//    cowModel->heightMap.push_back(voxelModel->heightMap[(26 + GRID_SIZE / 2) * GRID_SIZE + (26 + GRID_SIZE / 2)]);
//}
//
//void calculateDogPositions() {
//    dogModel->positions.push_back(vec3(26, 0, 26));
//    dogModel->heightMap.push_back(voxelModel->heightMap[(26 + GRID_SIZE / 2) * GRID_SIZE + (26 + GRID_SIZE / 2)]);
//}

void determineNeighbors() {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int z = 0; z < GRID_SIZE; z++) {
            vector<bool> currentNeighbors(4, false);
            if (z != GRID_SIZE - 1 && voxelModel->heightMap[x * GRID_SIZE + z] == voxelModel->heightMap[ x      * GRID_SIZE + z + 1]) currentNeighbors[0] = true; // back
            if (z != 0             && voxelModel->heightMap[x * GRID_SIZE + z] == voxelModel->heightMap[ x      * GRID_SIZE + z - 1]) currentNeighbors[1] = true; // front
            if (x != GRID_SIZE - 1 && voxelModel->heightMap[x * GRID_SIZE + z] == voxelModel->heightMap[(x + 1) * GRID_SIZE + z    ]) currentNeighbors[2] = true; // left
            if (x != 0             && voxelModel->heightMap[x * GRID_SIZE + z] == voxelModel->heightMap[(x - 1) * GRID_SIZE + z    ]) currentNeighbors[3] = true; // right
            //neighbors[x * GRID_SIZE + z] = currentNeighbors;
        }
    }
}

void createContext() {
    voxelModel->createContext(voxelModel->positions, voxelModel->heightMap);
    treeModel->createContext(treeModel->positions, treeModel->heightMap);
    rockModel->createContext(rockModel->positions, rockModel->heightMap);
    //cowModel->createContext(cowModel->positions, cowModel->heightMap);
    //dogModel->createContext(dogModel->positions, dogModel->heightMap);
}

void mainLoop() {
    bool frontMoveAllowed, backMoveAllowed, rightMoveAllowed, leftMoveAllowed, jumpAllowed;
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // Camera
        int thisx, thisz;
        getBlockPositionFromCoordinates(camera->position.x, camera->position.z, &thisx, &thisz);

        allowCameraMove(thisx, thisz, &frontMoveAllowed, &backMoveAllowed, &rightMoveAllowed, &leftMoveAllowed, &jumpAllowed);
        camera->update(getColumnHighestBlock(thisx, thisz), frontMoveAllowed, backMoveAllowed, rightMoveAllowed, leftMoveAllowed, jumpAllowed);

        mat4 projectionMatrix = camera->projectionMatrix;
        mat4 viewMatrix = camera->viewMatrix;
        mat4 modelMatrix = mat4();

        // Render world
        voxelModel->render(shaderProgram, projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation, projectionMatrix, viewMatrix, modelMatrix, NULL, NULL, textureAtlas, shaderTextureAtlasSampler, GRID_SIZE * GRID_SIZE);
        treeModel->render(objectProgram, projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation, projectionMatrix, viewMatrix, modelMatrix, 1, objectIDLocation, textureAtlas, objectTextureAtlasSampler, treeModel->positions.size());
        rockModel->render(objectProgram, projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation, projectionMatrix, viewMatrix, modelMatrix, 2, objectIDLocation, textureAtlas, objectTextureAtlasSampler, rockModel->positions.size());
        //cowModel->render(objectProgram, projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation, projectionMatrix, viewMatrix, modelMatrix, 3, objectIDLocation, textureAtlas, objectTextureAtlasSampler, cowModel->positions.size());
        //dogModel->render(objectProgram, projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation, projectionMatrix, viewMatrix, modelMatrix, 4, objectIDLocation, textureAtlas, objectTextureAtlasSampler, dogModel->positions.size());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

void initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        throw runtime_error("Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(W_WIDTH, W_HEIGHT, W_TITLE, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw runtime_error(string(string("Failed to open GLFW window.") + 
            " If you have an Intel GPU, they are not 3.3 compatible." + 
            "Try the 2.1 version.\n"));
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw runtime_error("Failed to initialize GLEW\n");
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Hide the mouse and enable unlimited movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, W_WIDTH / 2, W_HEIGHT / 2);
    
    // Sky blue background color
    glClearColor(0.53f, 0.81f, 0.92f, 0.5f);

    //glfwSetKeyCallback(window, pollKeyboard);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Accept fragment if it is closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable textures
    glEnable(GL_TEXTURE_2D);

    // Log
    logGLParameters();
}

void free() {
    delete voxelModel, treeModel, rockModel;// , cowModel, dogModel;

    glDeleteTextures(1, &textureAtlas);

    glDeleteProgram(shaderProgram);
    glDeleteProgram(objectProgram);
    glfwTerminate();
}

int main(void) {
    try {
        initialize();
        prepareShaders();
        createModels();
        createContext();
        mainLoop();
        free();
    }
    catch (exception& ex) {
        cout << ex.what() << endl;
        (void)getchar();
        free();
        return -1;
    }
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

Camera* setCameraLocation(float x, float z) {
    int x_quantized, z_quantized;
    getBlockPositionFromCoordinates(x, z, &x_quantized, &z_quantized);
    return new Camera(
        window,
        vec3(0.5 * x, getColumnHighestBlock(x_quantized, z_quantized) + 0.6, -0.5 * z),
        0, - 3.14f / 16.0f,
        voxelModel->heightMap,
        false
    );
}

float getColumnHighestBlock(int x_quantized, int z_quantized) {
    return -0.5f * voxelModel->heightMap[GRID_SIZE * x_quantized + z_quantized] + 0.5f;
}

void getBlockPositionFromCoordinates(float x, float z, int* out_x, int* out_z) {
    *out_x = floor(2 * (x + 0.25)) + GRID_SIZE / 2;
    *out_z = floor(2 * (-z + 0.25)) + GRID_SIZE / 2;
}

int generateRandomNumber(int start, int end) {
    int range = end - start + 1;
    return start + (rand() % range);
}

void allowCameraMove(int thisx, int thisz, bool* out_front, bool* out_back, bool* out_right, bool* out_left, bool* out_jump) {
    int looksTowardsX = 0, looksTowardsZ = 0, rightTowardsX = 0, rightTowardsZ = 0;
    float xdotdir = dot(camera->direction, vec3(1, 0, 0));
    float zdotdir = dot(camera->direction, vec3(0, 0, 1));

    if (xdotdir > 0) {
        looksTowardsX = 1;
        rightTowardsZ = -1;
    }
    else if (xdotdir < 0) {
        looksTowardsX = -1;
        rightTowardsZ = 1;
    }

    if (zdotdir > 0) {
        looksTowardsZ = -1;
        rightTowardsX = 1;
    }
    else if (zdotdir < 0) {
        looksTowardsZ = 1;
        rightTowardsX = -1;
    }

    float thisHighestBlock = getColumnHighestBlock(thisx, thisz);
    float frontHighestBlock = getColumnHighestBlock(thisx + looksTowardsX, thisz + looksTowardsZ);
    float backHighestBlock = getColumnHighestBlock(thisx - looksTowardsX, thisz - looksTowardsZ);
    float rightHighestBlock = getColumnHighestBlock(thisx + rightTowardsX, thisz + rightTowardsZ);
    float leftHighestBlock = getColumnHighestBlock(thisx - rightTowardsX, thisz - rightTowardsZ);

    // Block moving when looking all the way up or down.
    if (!(xdotdir > 0.45f || xdotdir < -0.45f || zdotdir > 0.45f || zdotdir < -0.45f)) {
        *out_front = false;
        *out_back = false;
        *out_right = false;
        *out_left = false;
        return;
    }

    // Block jumping when under a tree.
    if (treeModel->hasLocated[(thisx + looksTowardsX) * GRID_SIZE + (thisz + looksTowardsZ)] || 
        treeModel->hasLocated[(thisx - looksTowardsX) * GRID_SIZE + (thisz - looksTowardsZ)] || 
        treeModel->hasLocated[(thisx + rightTowardsX) * GRID_SIZE + (thisz + rightTowardsZ)] || 
        treeModel->hasLocated[(thisx - rightTowardsX) * GRID_SIZE + (thisz - rightTowardsZ)]
        ) *out_jump = false;
    else *out_jump = true;

    if (treeModel->hasLocated[(thisx + looksTowardsX) * GRID_SIZE + (thisz + looksTowardsZ)] || rockModel->hasLocated[(thisx + looksTowardsX) * GRID_SIZE + (thisz + looksTowardsZ)])
        *out_front = false;
    else if (frontHighestBlock <= thisHighestBlock || camera->position.y - 0.6 >= frontHighestBlock) *out_front = true;
    else *out_front = false;

    if (treeModel->hasLocated[(thisx - looksTowardsX) * GRID_SIZE + (thisz - looksTowardsZ)] || rockModel->hasLocated[(thisx - looksTowardsX) * GRID_SIZE + (thisz - looksTowardsZ)])
        *out_back = false;
    else if (backHighestBlock <= thisHighestBlock || camera->position.y - 0.6 >= backHighestBlock) *out_back = true;
    else *out_back = false;

    if (treeModel->hasLocated[(thisx + rightTowardsX) * GRID_SIZE + (thisz + rightTowardsZ)] || rockModel->hasLocated[(thisx + rightTowardsX) * GRID_SIZE + (thisz + rightTowardsZ)])
        *out_right = false;
    else if (rightHighestBlock <= thisHighestBlock || camera->position.y - 0.6 >= rightHighestBlock) *out_right = true;
    else *out_right = false;

    if (treeModel->hasLocated[(thisx - rightTowardsX) * GRID_SIZE + (thisz - rightTowardsZ)] || rockModel->hasLocated[(thisx - rightTowardsX) * GRID_SIZE + (thisz - rightTowardsZ)])
        *out_left = false;
    else if (leftHighestBlock <= thisHighestBlock || camera->position.y - 0.6 >= leftHighestBlock) *out_left = true;
    else *out_left = false;
}
