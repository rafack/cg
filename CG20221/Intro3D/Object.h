#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class Object
{
public:
const int TRIANGLES = 12;
const int NUM_VERTICES = 3;

enum side { FRONT = GLFW_KEY_1, BACK = GLFW_KEY_2, LEFT = GLFW_KEY_3, RIGHT = GLFW_KEY_4, TOP = GLFW_KEY_5 };

Object()
{
}

int setupGeometry()
{
	GLfloat vertices[] = {
		-0.5f,-0.5f,-0.5f, 1.0, 1.0, 0.0,// triangle 1 : begin
	-0.5f,-0.5f, 0.5f, 0.0, 1.0, 1.0,
	-0.5f, 0.5f, 0.5f, 1.0, 0.0, 1.0, // triangle 1 : end
	0.5f, 0.5f,-0.5f,  1.0, 1.0, 0.0,// triangle 2 : begin
	-0.5f,-0.5f,-0.5f, 1.0, 0.0, 1.0,
	-0.5f, 0.5f,-0.5f, 0.0, 1.0, 1.0, // triangle 2 : end
	0.5f,-0.5f, 0.5f, 1.0, 1.0, 0.0,
	-0.5f,-0.5f,-0.5f,0.0, 1.0, 1.0,
	0.5f,-0.5f,-0.5f, 1.0, 0.0, 1.0,
	0.5f, 0.5f,-0.5f, 1.0, 1.0, 0.0,
	0.5f,-0.5f,-0.5f, 0.0, 1.0, 1.0,
	-0.5f,-0.5f,-0.5f,1.0, 0.0, 1.0,
	-0.5f,-0.5f,-0.5f, 1.0, 1.0, 0.0,//0
	-0.5f, 0.5f, 0.5f, 1.0, 1.0, 0.0,//2
	-0.5f, 0.5f,-0.5f, 1.0, 1.0, 0.0,//5
	0.5f,-0.5f, 0.5f,  1.0, 1.0, 0.0,
	-0.5f,-0.5f, 0.5f, 1.0, 1.0, 0.0,
	-0.5f,-0.5f,-0.5f, 1.0, 1.0, 0.0,//7
	-0.5f, 0.5f, 0.5f, 1.0, 1.0, 0.0,//5
	-0.5f,-0.5f, 0.5f, 1.0, 1.0, 0.0,//2
	0.5f,-0.5f, 0.5f,  1.0, 0.0, 1.0,//3	
	0.5f, 0.5f, 0.5f,  1.0, 1.0, 0.0,//2
	0.5f,-0.5f,-0.5f,  1.0, 1.0, 0.0,//5
	0.5f, 0.5f,-0.5f,  1.0, 0.0, 1.0,//4
	0.5f,-0.5f,-0.5f, 1.0, 0.0, 1.0,//3	
	0.5f, 0.5f, 0.5f, 1.0, 0.0, 1.0,//4
	0.5f,-0.5f, 0.5f, 0.0, 1.0, 1.0,//1
	0.5f, 0.5f, 0.5f, 0.0, 1.0, 1.0,//1
	0.5f, 0.5f,-0.5f, 1.0, 0.0, 1.0,//4
	-0.5f, 0.5f,-0.5f,0.0, 1.0, 1.0,//6
	0.5f, 0.5f, 0.5f,  0.0, 1.0, 1.0,//1
	-0.5f, 0.5f,-0.5f, 0.0, 1.0, 1.0,//6
	-0.5f, 0.5f, 0.5f, 0.0, 1.0, 1.0,//0	
	0.5f, 0.5f, 0.5f,  1.0, 1.0, 0.0,//7
	-0.5f, 0.5f, 0.5f, 0.0, 1.0, 1.0,//6
	0.5f,-0.5f, 0.5f  , 0.0, 1.0, 1.0,//0
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}
};
