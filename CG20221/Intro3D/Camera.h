#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using namespace std;

class Camera
{
public:
	Camera() {};
	~Camera() {};

	glm::mat4 view, projection;
	glm::vec3 position, upDirectionVector, front;

	float speed = 0.085f;
	float yaw = -90.0f, pitch = 0.0f;

	enum movement { MOVE_FWD = GLFW_KEY_W, MOVE_BKW = GLFW_KEY_S, MOVE_LEFT = GLFW_KEY_A, MOVE_RIGHT = GLFW_KEY_D };
	enum viewSide { FRONT = GLFW_KEY_1, BACK = GLFW_KEY_2, LEFT = GLFW_KEY_3, RIGHT = GLFW_KEY_4, TOP = GLFW_KEY_5 };

	void initialize()
	{
		position = glm::vec3(0.0f, 0.0f, 1.0f);
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
		
		view = glm::mat4(1);
		view = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), upDirectionVector);
	
		projection = glm::mat4(1);
		projection = glm::perspective(45.0f, 1000.0f / 1000.0f, 0.1f, 100.0f);
	}


	void updateViewMatrix()
	{
		view = glm::mat4(1);

		view = glm::lookAt(position, position + front, upDirectionVector);
	}

	void updatePosition(int direction)
	{
		view = glm::mat4(1);

		switch (direction) 
		{
			case(MOVE_FWD):
				position += speed * front;
				break;
			case(MOVE_BKW):
				position -= speed * front;
				break;
			case(MOVE_RIGHT):
				position += glm::normalize(glm::cross(front, upDirectionVector)) * speed;
				break;
			case(MOVE_LEFT):
				position -= glm::normalize(glm::cross(front, upDirectionVector)) * speed;
				break;
		}
	}

	void updateViewDirection(int direction)
	{
		view = glm::mat4(1);

		switch (direction)
		{
			case(FRONT):
				position = glm::vec3(0.0f, 0.0f, 1.0f);
				upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
				break;
			case(BACK):
				position = glm::vec3(0.0f, 0.0f, -1.0f);
				upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
				break;
			case(LEFT):
				position = glm::vec3(-1.0f, 0.0f, 0.0f);
				upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
				break;
			case(RIGHT):
				position = glm::vec3(1.0f, 0.0f, 0.0f);
				upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
				break;
			case(TOP):
				position = glm::vec3(0.0f, 1.0f, 0.0f);
				upDirectionVector = glm::vec3(0.0f, 0.0f, 1.0f);
				break;
		}
	}
};