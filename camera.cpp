#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f; 

glm::vec3 cameraPos = glm::vec3(0.5f, 0.4f, 0.5f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSpeed = 0.05f;
float cameraRotationSpeed = 3.0f;

glm::mat4 viewMatrix;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        glm::vec3 cameraDirection = glm::normalize(cameraTarget);
        cameraPos += cameraDirection * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        glm::vec3 cameraDirection = glm::normalize(cameraTarget);
        cameraPos -= cameraDirection * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        viewMatrix = glm::rotate(viewMatrix, glm::radians(cameraRotationSpeed), cameraUp);
        cameraTarget = glm::vec3(viewMatrix * glm::vec4(cameraTarget, 1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        viewMatrix = glm::rotate(viewMatrix, glm::radians(-cameraRotationSpeed), cameraUp);
        cameraTarget = glm::vec3(viewMatrix * glm::vec4(cameraTarget, 1.0f));
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

vector<float> loadMesh(string filename) {
    vector<float> vertices;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return vertices;
    }

    while (!infile.eof()) {
        float x, y, z;
        infile >> x >> y >> z;
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    infile.close();

    return vertices;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

   
