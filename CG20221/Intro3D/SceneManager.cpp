#include "SceneManager.h"
#include "Cube.cpp"
#include "Camera.h"

bool firstCursorMovement;
//int viewID;

glm::mat4 model;
//glm::mat4 view;

glm::vec3 rotationAxis;
//glm::vec3 camPosition;
//glm::vec3 upDirectionVector;
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);

//enum camMovement { MOVE_FWD = GLFW_KEY_W, MOVE_BKW = GLFW_KEY_S, MOVE_LEFT = GLFW_KEY_A, MOVE_RIGHT = GLFW_KEY_D };

Camera* camera;

double xCursor, yCursor;
double lastX, lastY;

//float cameraSpeed = 0.05;
//float yaw, pitch = 0.0f;

GLuint VAO;
Cube* cube;

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
	shader->use();

	firstCursorMovement = true;

	glm::mat4 model = glm::mat4(1);
	//glm::mat4 view = glm::mat4(1);
	camera = new Camera();
	camera->initialize();

	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader->setMat4("model", glm::value_ptr(model));

	//camPosition = glm::vec3(0.0f, 0.0f, -1.0f);
	//upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneManager::setupCube() 
{
	cube = new Cube();

	cube->shouldRotate = false;

	VAO = cube->setupGeometry();
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

		float angle = (GLfloat)glfwGetTime();

		model = glm::mat4(1);

		if (cube->shouldRotate)
		{
			model = glm::rotate(model, angle, rotationAxis);
		}

		shader->setMat4("model", glm::value_ptr(model));

		//glfwGetCursorPos(window, &xCursor, &yCursor);
		//printf("x: %f y: %f", xCursor, yCursor);
		//camPosition = glm::vec3((float)WIDTH - (float)xCursor, (float)HEIGHT - (float)yCursor, -1.0f);

		// Visão de frente..  primeiro param = eye / posicao da cam, segundo = center / p onde esta olhando, 3º up = eixo topo
		//view = glm::lookAt(camPosition + cameraFront, glm::vec3(0.0f, 0.0f, 0.0f), upDirectionVector);
		camera->updateViewMatrix();
		shader->setMat4("view", glm::value_ptr(camera->view));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, cube->TRIANGLES * cube->NUM_VERTICES);

		glDrawArrays(GL_POINTS, 0, cube->TRIANGLES * cube->NUM_VERTICES);
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

void SceneManager::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	setRotation(key, action);
	setView(key, action);

	//move camera
	if (key == camera->MOVE_FWD && action == GLFW_PRESS)
	{
		camera->updatePosition(camera->MOVE_FWD);
	}

	if (key == camera->MOVE_BKW && action == GLFW_PRESS)
	{
		camera->updatePosition(camera->MOVE_BKW);
	}

	if (key == camera->MOVE_RIGHT && action == GLFW_PRESS)
	{
		camera->updatePosition(camera->MOVE_RIGHT);
	}

	if (key == camera->MOVE_LEFT && action == GLFW_PRESS)
	{
		camera->updatePosition(camera->MOVE_LEFT);
	}

}

//void SceneManager::cursorPos_callback(GLFWwindow* window, double xPos, double yPos)
//{
//	if (firstCursorMovement)
//	{
//		lastX = xPos;
//		lastY = yPos;
//		firstCursorMovement = false;
//	}
//
//	float xoffset = xPos - lastX;
//	float yoffset = lastY - yPos;
//
//	lastX = xPos;
//	lastY = yPos;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	if (pitch > 89.0f) pitch = 89.0f;
//	if (pitch < -89.0f) pitch = -89.0f;
//
//	glm::vec3 front;
//
//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	front.y = sin(glm::radians(pitch));
//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//
//	cameraFront = glm::normalize(front);
//}

void SceneManager::setRotation(int key, int action)
{
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		cube->shouldRotate = true;
		rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		cube->shouldRotate = true;
		rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		cube->shouldRotate = true;
		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	}
}

void SceneManager::setView(int key, int action)
{
	if (key == camera->FRONT && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->FRONT);
		/*camPosition = glm::vec3(0.0f, 0.0f, -1.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);*/
	}

	if (key == camera->BACK && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->BACK);
		/*camPosition = glm::vec3(0.0f, 0.0f, 1.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);*/
	}

	if (key == camera->LEFT && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->LEFT);
		/*camPosition = glm::vec3(-1.0f, 0.0f, 0.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);*/
	}

	if (key == camera->RIGHT && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->RIGHT);
		/*camPosition = glm::vec3(1.0f, 0.0f, 0.0f);
		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);*/
	}

	if (key == camera->TOP && action == GLFW_PRESS)
	{
		camera->updateViewDirection(camera->TOP);
		/*camPosition = glm::vec3(0.0f, 1.0f, 0.0f);
		upDirectionVector = glm::vec3(0.0f, 0.0f, 1.0f);*/
	}
}