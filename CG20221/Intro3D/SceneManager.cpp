#include "SceneManager.h"

bool shouldRotate;
bool firstCursorMovement;
int viewID;

glm::vec3 rotationAxis;
glm::vec3 camPosition;
glm::vec3 upDirectionVector;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);

enum camMovement { MOVE_FWD = GLFW_KEY_W, MOVE_BKW = GLFW_KEY_S, MOVE_LEFT = GLFW_KEY_A, MOVE_RIGHT = GLFW_KEY_D };

double xCursor, yCursor;
double lastX, lastY;

float cameraSpeed = 0.05;
float yaw, pitch = 0.0f;

Object* object;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize()
{
	loadGraphics();
	setupWindow();

	object = new Object();
	shader = new Shader();

	GLuint VAO = object->setupGeometry();
	shader->use();

	shouldRotate = false;
	firstCursorMovement = true;

	glm::mat4 model = glm::mat4(1);
	glm::mat4 view = glm::mat4(1);

	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader->setMat4("model", glm::value_ptr(model));

	camPosition = glm::vec3(0.0f, 0.0f, -1.0f);
	upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		float angle = (GLfloat)glfwGetTime();

		model = glm::mat4(1);
		view = glm::mat4(1);

		if (shouldRotate)
		{
			model = glm::rotate(model, angle, rotationAxis);
		}

		shader->setMat4("model", glm::value_ptr(model));

		//glfwGetCursorPos(window, &xCursor, &yCursor);
		//printf("x: %f y: %f", xCursor, yCursor);
		//camPosition = glm::vec3((float)WIDTH - (float)xCursor, (float)HEIGHT - (float)yCursor, -1.0f);

		// Visão de frente..  primeiro param = eye / posicao da cam, segundo = center / p onde esta olhando, 3º up = eixo topo
		view = glm::lookAt(camPosition + cameraFront, glm::vec3(0.0f,0.0f,0.0f), upDirectionVector);
		shader->setMat4("view", glm::value_ptr(view));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, object->TRIANGLES * object->NUM_VERTICES);

		glDrawArrays(GL_POINTS, 0, object->TRIANGLES * object->NUM_VERTICES);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
}

void SceneManager::loadGraphics()
{
	glfwInit();

	window = glfwCreateWindow(WIDTH, HEIGHT, "Ola, 3D!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetCursorPosCallback(window, cursorPos_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
}

void SceneManager::setupWindow()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void SceneManager::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	setRotation(key, action);
	setView(key, action);

	//move camera
	if (key == MOVE_FWD && action == GLFW_PRESS)
	{
		camPosition += cameraSpeed * cameraFront;
	}

	if (key == MOVE_BKW && action == GLFW_PRESS)
	{
		camPosition -= cameraSpeed * cameraFront;
	}

	if (key == MOVE_RIGHT && action == GLFW_PRESS)
	{
		camPosition += glm::normalize(glm::cross(cameraFront, upDirectionVector)) * cameraSpeed;
	}

	if (key == MOVE_LEFT && action == GLFW_PRESS)
	{
		camPosition -= glm::normalize(glm::cross(cameraFront, upDirectionVector)) * cameraSpeed;
	}

}

void SceneManager::cursorPos_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstCursorMovement)
	{
		lastX = xPos;
		lastY = yPos;
		firstCursorMovement = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);
}

void SceneManager::setRotation(int key, int action)
{
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		shouldRotate = true;
		rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		shouldRotate = true;
		rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		shouldRotate = true;
		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	}
}

void SceneManager::setView(int key, int action)
{
	if (key == object->FRONT && action == GLFW_PRESS)
	{
		viewID = object->FRONT;
		camPosition = glm::vec3(0.0f, 0.0f, -1.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	if (key == object->BACK && action == GLFW_PRESS)
	{
		viewID = object->BACK;
		camPosition = glm::vec3(0.0f, 0.0f, 1.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	if (key == object->LEFT && action == GLFW_PRESS)
	{
		viewID = object->LEFT;
		camPosition = glm::vec3(-1.0f, 0.0f, 0.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	if (key == object->RIGHT && action == GLFW_PRESS)
	{
		viewID = object->RIGHT;
		camPosition = glm::vec3(1.0f, 0.0f, 0.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	if (key == object->TOP && action == GLFW_PRESS)
	{
		viewID = object->TOP;
		camPosition = glm::vec3(0.0f, 1.0f, 0.0f);
		upDirectionVector = glm::vec3(0.0f, 0.0f, 1.0f);
	}
}