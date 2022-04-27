#include "SceneManager.h"
#include "Cube.cpp"
#include "Mesh.cpp"
#include "Camera.h"

bool firstCursorMovement;

glm::mat4 model;

glm::vec3 rotationAxis;

Camera* camera;

double xCursor, yCursor;
double lastX, lastY;

GLuint VAO;
//Cube* cube;
Mesh* mesh;

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

	shader = new Shader();
	setupMesh("Pikachu.obj");
	shader->use();

	firstCursorMovement = true;

	glm::mat4 model = glm::mat4(1);
	model = glm::scale(model, glm::vec3(3.0, 3.0, 3.0));
	shader->setMat4("model", glm::value_ptr(model));

	camera = new Camera();
	camera->initialize();
	
	shader->setMat4("view", glm::value_ptr(camera->view));
	shader->setMat4("projection", glm::value_ptr(camera->projection));

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneManager::loadGraphics()
{
	glfwInit();

	window = glfwCreateWindow(WIDTH, HEIGHT, "Ola, 3D!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard_callback);
	//glfwSetCursorPosCallback(window, cursorPos_callback);

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

//void SceneManager::setupCube() 
//{
//	cube = new Cube();
//
//	cube->shouldRotate = false;
//
//	VAO = cube->setupGeometry();
//}

void SceneManager::setupMesh(string meshFileName)
{
	mesh = new Mesh(meshFileName);

	mesh->shouldRotate = false;

	VAO = mesh->setupGeometry();
}

void SceneManager::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		float rotationAngle = (GLfloat)glfwGetTime();

		model = glm::mat4(1);

		if (mesh->shouldRotate)
		{
			model = glm::rotate(model, rotationAngle, rotationAxis);
		}

		camera->updateViewMatrix();

		shader->setMat4("view", glm::value_ptr(camera->view));
		shader->setMat4("model", glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, mesh->size);

		//glDrawArrays(GL_POINTS, 0, cube->TRIANGLES * cube->NUM_VERTICES);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
}


void SceneManager::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	setRotation(key, action);
	setView(key, action);
	moveCamera(key, action);
}

void SceneManager::moveCamera(int key, int action)
{
	if (key == camera->MOVE_FWD)
	{
		camera->updatePosition(camera->MOVE_FWD);
	}

	if (key == camera->MOVE_BKW)
	{
		camera->updatePosition(camera->MOVE_BKW);
	}

	if (key == camera->MOVE_RIGHT)
	{
		camera->updatePosition(camera->MOVE_RIGHT);
	}

	if (key == camera->MOVE_LEFT)
	{
		camera->updatePosition(camera->MOVE_LEFT);
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

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera->yaw += xoffset;
	camera->pitch += yoffset;

	if (camera->pitch > 89.0f) camera->pitch = 89.0f;
	if (camera->pitch < -89.0f) camera->pitch = -89.0f;

	glm::vec3 front;

	front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
	front.y = sin(glm::radians(camera->pitch));
	front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));

	camera->front = glm::normalize(front);
}

void SceneManager::setRotation(int key, int action)
{
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		mesh->shouldRotate = true;
		rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		mesh->shouldRotate = true;
		rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		mesh->shouldRotate = true;
		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	}
}

void SceneManager::setView(int key, int action)
{
	if (key == camera->FRONT && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->FRONT);
	}

	if (key == camera->BACK && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->BACK);
	}

	if (key == camera->LEFT && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->LEFT);
	}

	if (key == camera->RIGHT && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->RIGHT);
	}

	if (key == camera->TOP && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->TOP);
	}
}