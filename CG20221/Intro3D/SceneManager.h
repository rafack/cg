#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Object.h"
#include <iostream>
#include <cstring>
#include<vector>

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	GLFWwindow* initialize();
	int setupMesh(string meshFileName);
	void run();
	void drawCall();
	GLuint setupGrid(int rows, int cols);
	int getMeshSize();
	vector<string> getObjConfig();

private:
	static void processInput(GLFWwindow* window);
	static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void cursorPos_callback(GLFWwindow* window, double xPos, double yPos);
	
	GLFWwindow* window;
	Shader* shader;

	const GLuint WIDTH = 800, HEIGHT = 600;

	void loadGraphics();
	void setupWindow();
};