#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using namespace std;

class Camera
{
public:
	Camera() {};
	~Camera() {};

	glm::mat4 view;
	glm::vec3 position;
	glm::vec3 upDirectionVector;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);

	float cameraSpeed = 0.05;
	float yaw, pitch = 0.0f;

	enum movement { MOVE_FWD = GLFW_KEY_W, MOVE_BKW = GLFW_KEY_S, MOVE_LEFT = GLFW_KEY_A, MOVE_RIGHT = GLFW_KEY_D };
	enum viewSide { FRONT = GLFW_KEY_1, BACK = GLFW_KEY_2, LEFT = GLFW_KEY_3, RIGHT = GLFW_KEY_4, TOP = GLFW_KEY_5 };

	void initialize()
	{
		view = glm::mat4(1);

		position = glm::vec3(0.0f, 0.0f, -1.0f);

		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void updateViewMatrix()
	{
		view = glm::mat4(1);
		view = glm::lookAt(position + front, glm::vec3(0.0f, 0.0f, 0.0f), upDirectionVector);
	}

	void updatePosition(int direction)
	{
		switch (direction) 
		{
			case(MOVE_FWD):
				position += cameraSpeed * front;
				break;
			case(MOVE_BKW):
				position -= cameraSpeed * front;
				break;
			case(MOVE_RIGHT):
				position += glm::normalize(glm::cross(front, upDirectionVector)) * cameraSpeed;
				break;
			case(MOVE_LEFT):
				position -= glm::normalize(glm::cross(front, upDirectionVector)) * cameraSpeed;
				break;
		}
	}

	void updateViewDirection(int direction)
	{
		switch (direction)
		{
			case(FRONT):
				position = glm::vec3(0.0f, 0.0f, -1.0f);
				upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
				break;
			case(BACK):
				position = glm::vec3(0.0f, 0.0f, 1.0f);
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