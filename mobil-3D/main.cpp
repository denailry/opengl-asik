#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

#include "lib/shader.h"
#include "camera/camera.h"
#include "lib/filesystem.h"
#include "lib/objloader.hpp"
#include "rain/raindrop.hpp"
#include "rain/rain.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const float UPDATE_DELAY = 0.003;

GLFWwindow* createWindow() {
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mobil 3D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

    glEnable(GL_DEPTH_TEST);

    return window;
}

void initGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLuint initVertexArray() {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    return VAO;
}

GLuint initVertexBuffer(std::vector<glm::vec3> &vertices) {
    GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    return vertexbuffer;
}

GLuint initUVBuffer(std::vector<glm::vec2> &uvs) {
    GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    return uvbuffer;
}

void setupCar(GLuint VBO, GLuint UVS) {
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0,          // attribute
        3,          // size
        GL_FLOAT,   // type
        GL_FALSE,   // normalized?
        0,          // stride
        (void*)0    // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, UVS);
    glVertexAttribPointer(
        1,          // attribute
        2,          // size
        GL_FLOAT,   // type
        GL_FALSE,   // normalized?
        0,          // stride
        (void*)0    // array buffer offset
    );
}

void setupRain(GLuint VBO) {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0,          // attribute
        3,          // size
        GL_FLOAT,   // type
        GL_FALSE,   // normalized?
        0,          // stride
        (void*)0    // array buffer offset
    );
}

std::vector<glm::vec3> generateRainVertices() {
    std::vector<glm::vec3> vertices;
    
    float x = 0;
    float z = 0;

    float yStart = RAIN_Y_OFFSET;
    float yEnd = RAIN_Y_OFFSET - RAIN_HEIGHT;
    float xStart = x - RAIN_WIDTH;
    float xEnd = x + RAIN_WIDTH;
    float zStart = z - RAIN_WIDTH;
    float zEnd = z + RAIN_WIDTH;

    vertices.push_back(glm::vec3(xStart, yStart, zStart));
    vertices.push_back(glm::vec3(xEnd, yStart, zStart));
    vertices.push_back(glm::vec3(x, yEnd, z));
    vertices.push_back(glm::vec3(xStart, yStart, zEnd));
    vertices.push_back(glm::vec3(xStart, yStart, zStart));
    vertices.push_back(glm::vec3(x, yEnd, z));
    vertices.push_back(glm::vec3(xEnd, yStart, zEnd));
    vertices.push_back(glm::vec3(xEnd, yStart, zStart));
    vertices.push_back(glm::vec3(x, yEnd, z));
    vertices.push_back(glm::vec3(xStart, yStart, zEnd));
    vertices.push_back(glm::vec3(xEnd, yStart, zEnd));
    vertices.push_back(glm::vec3(x, yEnd, z));

    return vertices;
}

void draw(GLuint VAO, Shader shader, int size) {
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
    float angle = 20.0f * 0;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, size);
}

int main() {
    initGL();
    GLFWwindow* window = createWindow();
    if (window == 0) {
        return -1;
    }

    Shader cameraShader("camera/camera.vs", "camera/camera.fs");

	std::vector<glm::vec3> carVertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("model/model.obj", carVertices, uvs, normals);

    GLuint VAOCar = initVertexArray();
    GLuint VBOCar = initVertexBuffer(carVertices);
    GLuint uvBuffer = initUVBuffer(uvs);
    setupCar(VBOCar, uvBuffer);
    
    std::vector<glm::vec3> rainVertices = generateRainVertices();
    Rain rain(200, 7);
    GLuint VAORain = initVertexArray();
    GLuint VBORain = initVertexBuffer(rainVertices);
    setupRain(VBORain);

    float lastMoveFrame = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        cameraShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        cameraShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        cameraShader.setMat4("view", view);
        
        cameraShader.setVec3("offset", glm::vec3(0.0, 0.0, 0.0));
        draw(VAOCar, cameraShader, carVertices.size());

        for (RainDrop raindrop : rain.getRainDrops()) {
            cameraShader.setVec3("offset", raindrop.getOffset());
            draw(VAORain, cameraShader, rainVertices.size());
        }

        if (currentFrame - lastMoveFrame > UPDATE_DELAY) {
            lastMoveFrame = currentFrame;
            rain.update();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAOCar);
    glDeleteBuffers(1, &VBOCar);
    glDeleteBuffers(1, &uvBuffer);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}