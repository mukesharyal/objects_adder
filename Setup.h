// This is the header file where all the definitions are stored

// The class Object, Grid, Highlight can be defined here

// Only the declarations can be done here, and the definitions can be done in the Setup.cpp file. That is also the convention.

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#define WIDTH 800
#define HEIGHT 600

// The window reference to do something with the window
extern GLFWwindow* window;


// The shader program to be used for the rendering
extern GLint shaderProgram;

// The memory where the HighLight object is stored
extern GLuint highlightedCellVBO, highlightedCellVAO;

// The position of the grid points with reference to the cursor are sent between files, as they are used in multiple places
extern GLfloat xLeft, xRight, yTop, yBottom;

extern int mode;
extern float size;

extern int selectedObject;

extern bool topView;

extern std::vector<std::vector<float>> objects;
extern int numObjects;

std::string readShaderSource(const std::string& filepath);

GLuint compileShader(GLenum type, const std::string& source);

GLuint createShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

int startWindow(GLFWwindow* &window);

void setupImGui();

void setupGrid(GLuint &gridVAO, GLuint &gridVBO, GLuint &gridEBO);

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void renderGrid();

//void renderHouse(GLuint shaderProgram, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

