#include "SceneManager.h"
#include "Cube.cpp"
#include "Mesh.cpp"
#include "Camera.h"

bool firstCursorMovement ;

glm::mat4 model;

//Camera* camera;

double xCursor, yCursor;
double lastX, lastY;

GLuint VAO;
Shader* shader;
Mesh* mesh;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

GLFWwindow* SceneManager::initialize()
{
	loadGraphics();
	setupWindow();

	return window;

	//shader = new Shader();
	//VAO = setupGrid(2, 2);
	////setupMesh("Pikachu.obj");
	//shader->use();

	//firstCursorMovement = true;

	//camera = new Camera();
	//camera->initialize();
	//
	//shader->setMat4("model", model);
	//shader->setMat4("view",camera->view);
	//shader->setMat4("projection", camera->projection);

	//shader->setVec3("objectColor", 1.0f, 0.0f, 1.0f);
	//shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	//shader->setVec3("lightPos", 0.0, 5.0, 2.0);
	//shader->setVec3("viewPos", camera->position.x, camera->position.y, camera->position.z);

	//glEnable(GL_DEPTH_TEST);
}

void SceneManager::loadGraphics()
{
	glfwInit();

	window = glfwCreateWindow(WIDTH, HEIGHT, "Ola, 3D!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//glfwSetKeyCallback(window, keyboard_callback);
	//glfwSetCursorPosCallback(window, cursorPos_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

int SceneManager::setupMesh(string meshFileName)
{
	mesh = new Mesh(meshFileName);

	return mesh->setupGeometry();
}

int SceneManager::getMeshSize() 
{
	return mesh->size;
}

vector<string> SceneManager::getObjConfig()
{
	vector<string> objectsFiles;

	ifstream inputFileStream;
	inputFileStream.open("./Models/scene_config.txt");

	const int MAX_CHARACTERES_LINE = 50;

	if (inputFileStream.is_open())
	{
		char line[MAX_CHARACTERES_LINE];
		string strLine;

		while (!inputFileStream.eof())
		{
			inputFileStream.getline(line, MAX_CHARACTERES_LINE);
			strLine = line;
			string word;
			istringstream sline(line);
			sline >> word;

			string param = word.substr(0, 3);

			if (param == "obj")
			{
				objectsFiles.push_back(word.substr(3, word.size()));
			}
		}
		inputFileStream.close();
	}
	else cout << "Erro ao ler o arquivo config" << endl;

	return objectsFiles;
};

void SceneManager::run()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1,0.2,1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		model = glm::mat4(1);

		//camera->updateViewMatrix();

		//shader->setMat4("view", camera->view);
		shader->setMat4("model", glm::value_ptr(model));

		drawCall();

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
}

void SceneManager::drawCall()
{
	float xi = -1.5;
	float offsetx = 0.7;

	float yi = -0.5;
	float offsety = 0.7;

	shader->setFloat("ka", 0.5); // ambiente
	shader->setFloat("kd", 0.45);// difusa 
	shader->setFloat("ks", 0.25);// especular

	float ns[5] = { 3.0, 5.0, 10.0, 27.0, 200.0 };
	float kss[3] = { 0.1, 0.25, 0.5 };

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 2*2);
	/*for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			shader->setFloat("ks", kss[i]);
			shader->setFloat("n", ns[j]);

			glm::mat4 model = glm::mat4(1);
			model = glm::translate(model, glm::vec3(xi + j * offsetx, yi + i * offsety, 0.0));
			model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
			shader->setMat4("model", model);

		}
	}*/
}

void SceneManager::processInput(GLFWwindow* window)
{
//	glfwPollEvents();
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		camera->moveForward();
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		camera->moveBackwards();
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		camera->moveToRight();
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		camera->moveToLeft();
}

void SceneManager::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)		glfwSetWindowShouldClose(window, GL_TRUE);
}

void SceneManager::cursorPos_callback(GLFWwindow* window, double xPos, double yPos)
{
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
//	float sensitivity = 0.05;
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	camera->yaw += xoffset;
//	camera->pitch += yoffset;
//
//	if (camera->pitch > 89.0f) camera->pitch = 89.0f;
//	if (camera->pitch < -89.0f) camera->pitch = -89.0f;
//
//	glm::vec3 front;
//
//	front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
//	front.y = sin(glm::radians(camera->pitch));
//	front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
//
//	camera->updateFront(front);
}
