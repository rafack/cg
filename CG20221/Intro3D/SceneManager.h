#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Object.h"

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void initialize();

private:
	static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void cursorPos_callback(GLFWwindow* window, double xPos, double yPos);
	static void setRotation(int key, int action);
	static void setView(int key, int action);
	
	GLFWwindow* window;
	Shader* shader;

	const GLuint WIDTH = 1000, HEIGHT = 1000;

	void loadGraphics();
	void setupWindow();
};