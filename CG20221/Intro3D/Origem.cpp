//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "Shader.h"
#include "SceneManager.h"

using namespace std;

//void loadGraphics();
//void setupWindow();

//void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void setRotation(int key, int action);
//void setView(int key, int action);

//int setupGeometry();

//GLFWwindow* window;
//Shader* shader;

//const GLuint WIDTH = 1000, HEIGHT = 1000;

//const int NUMERO_TRIANGULOS = 12;
//const int NUMERO_BYTES_VERTICE = 3 * sizeof(GLfloat);

//bool shouldRotate = false;
//
//glm::vec3 rotationAxis;
//
//enum squareSide { FRONT=GLFW_KEY_1, BACK=GLFW_KEY_2, LEFT=GLFW_KEY_3, RIGHT=GLFW_KEY_4, TOP=GLFW_KEY_5 };
//
//int viewID;
//
//glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 upDirectionVector;

int main()
{

	SceneManager* sceneManager = new SceneManager;

	sceneManager->initialize();
	/*loadGraphics();

	shader = new Shader();
	shader->use();

	setupWindow();

	GLuint VAO = setupGeometry();

	glm::mat4 model = glm::mat4(1);
	glm::mat4 view = glm::mat4(1);
	
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader->setMat4("model", glm::value_ptr(model));

	glEnable(GL_DEPTH_TEST);*/


	//while (!glfwWindowShouldClose(window))
	//{
	//	glfwPollEvents();

	//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	glLineWidth(10);
	//	glPointSize(20);

	//	float angle = (GLfloat) glfwGetTime();

	//	model = glm::mat4(1);
	//	view = glm::mat4(1);

	//	if (shouldRotate)
	//	{
	//		model = glm::rotate(model, angle, rotationAxis);
	//	}

	//	if (viewID != TOP)
	//	{
	//		upDirectionVector = glm::vec3(0.0f, 1.0f, 0.0f);
	//	}

	//	shader->setMat4("model", glm::value_ptr(model));

	//	// Visão de frente..  primeiro param = eye / posicao da cam, segundo = center / p onde esta olhando, 3º up = eixo topo
	//	view = glm::lookAt(camPosition, glm::vec3(0.0f, 0.0f, 0.0f), upDirectionVector);
	//	shader->setMat4("view", glm::value_ptr(view));

	//	glBindVertexArray(VAO);

	//							// 18 (total de vértices) = 6 triângulos * 3
	//	//glDrawArrays(GL_TRIANGLES, 0, 18);
	//	
	//							// 12 triângulos para o cubo
	//	glDrawArrays(GL_TRIANGLES, 0, NUMERO_TRIANGULOS * NUMERO_BYTES_VERTICE);

	//	glDrawArrays(GL_POINTS, 0, NUMERO_TRIANGULOS * NUMERO_BYTES_VERTICE);
	//	glBindVertexArray(0);

	//	glfwSwapBuffers(window);
	//}

	//glDeleteVertexArrays(1, &VAO);

	//glfwTerminate();
	return 0;
}

//void loadGraphics()
//{
//	glfwInit();
//
//	window = glfwCreateWindow(WIDTH, HEIGHT, "Ola, 3D!", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	glfwSetKeyCallback(window, keyboard_callback);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//	}
//
//	const GLubyte* renderer = glGetString(GL_RENDERER);
//	const GLubyte* version = glGetString(GL_VERSION);
//	cout << "Renderer: " << renderer << endl;
//	cout << "OpenGL version supported " << version << endl;
//}
//
//void setupWindow()
//{
//	int width, height;
//	glfwGetFramebufferSize(window, &width, &height);
//	glViewport(0, 0, width, height);
//}

//void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//
//	setRotation(key, action);
//	setView(key, action);
//}
//
//void setRotation(int key, int action)
//{
//	if (key == GLFW_KEY_X && action == GLFW_PRESS)
//	{
//		shouldRotate = true;
//		rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
//	}
//
//	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
//	{
//		shouldRotate = true;
//		rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
//	}
//
//	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
//	{
//		shouldRotate = true;
//		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
//	}
//}
//
//void setView(int key, int action)
//{
//	if (key == FRONT && action == GLFW_PRESS)
//	{
//		viewID = FRONT;
//		camPosition = glm::vec3(0.0f, 0.0f, -1.0f);
//	}
//
//	if (key == BACK && action == GLFW_PRESS)
//	{
//		viewID = BACK;
//		camPosition = glm::vec3(0.0f, 0.0f, 1.0f);
//	}
//
//	if (key == LEFT && action == GLFW_PRESS)
//	{
//		viewID = LEFT;
//		camPosition = glm::vec3(-1.0f, 0.0f, 0.0f);
//	}
//	
//	if (key == RIGHT && action == GLFW_PRESS)
//	{
//		viewID = RIGHT;
//		camPosition = glm::vec3(1.0f, 0.0f, 0.0f);
//	}
//	
//	if (key == TOP && action == GLFW_PRESS)
//	{
//		viewID = TOP;
//		camPosition = glm::vec3(0.0f, 1.0f, 0.0f);
//		upDirectionVector = glm::vec3(0.0f, 0.0f, 1.0f);
//	}
//}

//int setupGeometry()
//{
//
//	GLfloat vertices[] = {
//		// base-ok
//		-0.5, -0.5, -0.5,        1.0, 1.0, 0.0,
//		-0.5, -0.5,  0.5,        0.0, 1.0, 1.0,
//		 0.5, -0.5, -0.5,        1.0, 0.0, 1.0,
//       
//		-0.5, -0.5,  0.5,        1.0, 1.0, 0.0,
//		 0.5, -0.5, -0.5,        1.0, 0.0, 1.0,
//		 0.5, -0.5,  0.5,        0.0, 1.0, 1.0,
//		// base       
//       
//		// topo-ok       
//		 0.5, 0.5,  0.5,        1.0, 1.0, 0.0,
//		 0.5, 0.5, -0.5,        0.0, 1.0, 1.0,
//		-0.5, 0.5,  0.5,        1.0, 0.0, 1.0,
//       
//		 0.5, 0.5, -0.5,        1.0, 1.0, 0.0,
//		-0.5, 0.5, -0.5,        0.0, 1.0, 1.0,
//		-0.5, 0.5,  0.5,        1.0, 0.0, 1.0,
//		 // topo       
//       
//		 // trás- ok       
//		-0.5, -0.5, -0.5,        1.0, 1.0, 0.0,
//		 0.5, -0.5, -0.5,        1.0, 1.0, 0.0,
//		 0.5,  0.5, -0.5,        1.0, 1.0, 0.0,
//				         
//		-0.5, -0.5, -0.5,        1.0, 1.0, 0.0,
//		 0.5, -0.5, -0.5,        1.0, 1.0, 0.0,
//		-0.5,  0.5, -0.5,        1.0, 1.0, 0.0,
//		// trás       
//       
//		// direita -ok       
//		 0.5,  0.5, -0.5,        1.0, 1.0, 0.0,
//		 0.5, -0.5, -0.5,        1.0, 1.0, 0.0,
//		 0.5, -0.5,  0.5,        1.0, 0.0, 1.0,	   
//		       
//		 0.5, -0.5, -0.5,        1.0, 1.0, 0.0,
//		 0.5,  0.5, -0.5,        1.0, 1.0, 0.0,
//		 0.5,  0.5,  0.5,        1.0, 0.0, 1.0,
//		// direita       
//       
//		  // frente -ok       
//		-0.5, -0.5, 0.5,        1.0, 0.0, 1.0,		   
//		 0.5,  0.5, 0.5,        1.0, 0.0, 1.0,
//		-0.5,  0.5, 0.5,        0.0, 1.0, 1.0,
//		       
//		-0.5, -0.5, 0.5,        0.0, 1.0, 1.0,
//		 0.5,  0.5, 0.5,        1.0, 0.0, 1.0,
//		 0.5, -0.5, 0.5,        0.0, 1.0, 1.0,
//		// frente       
//		     
//		// esquerda-ok       
//		-0.5, -0.5,  0.5,        0.0, 1.0, 1.0,
//		-0.5,  0.5,  0.5,        0.0, 1.0, 1.0,
//		-0.5, -0.5, -0.5,        0.0, 1.0, 1.0,	
//		       
//		-0.5,  0.5, -0.5,        1.0, 1.0, 0.0,
//		-0.5,  0.5,  0.5,        0.0, 1.0, 1.0,
//		-0.5, -0.5, -0.5,        0.0, 1.0, 1.0,
//		// esquerda       
//		//-0.5, -0.5, -0.5, 1.0, 1.0, 0.0,
//		//-0.5, -0.5,  0.5, 0.0, 1.0, 1.0,
//		// 0.5, -0.5, -0.5, 1.0, 0.0, 1.0,
//
//		// -0.5, -0.5, 0.5, 1.0, 1.0, 0.0,
//		//  0.5, -0.5,  0.5, 0.0, 1.0, 1.0,
//		//  0.5, -0.5, -0.5, 1.0, 0.0, 1.0,
//
//		//  //
//		//  -0.5, -0.5, -0.5, 1.0, 1.0, 0.0,
//		//   0.0,  0.5,  0.0, 1.0, 1.0, 0.0,
//		//   0.5, -0.5, -0.5, 1.0, 1.0, 0.0,
//
//		//   -0.5, -0.5, -0.5, 1.0, 0.0, 1.0,
//		//   0.0,  0.5,  0.0, 1.0, 0.0, 1.0,
//		//   -0.5, -0.5, 0.5, 1.0, 0.0, 1.0,
//
//		//	-0.5, -0.5, 0.5, 1.0, 1.0, 0.0,
//		//   0.0,  0.5,  0.0, 1.0, 1.0, 0.0,
//		//   0.5, -0.5, 0.5, 1.0, 1.0, 0.0,
//
//		//	0.5, -0.5, 0.5, 0.0, 1.0, 1.0,
//		//   0.0,  0.5,  0.0, 0.0, 1.0, 1.0,
//		//   0.5, -0.5, -0.5, 0.0, 1.0, 1.0,
//	};
//
//	GLuint VBO, VAO;
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NUMERO_TRIANGULOS * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, NUMERO_TRIANGULOS * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	return VAO;
//}