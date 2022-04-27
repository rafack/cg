#include "SceneManager.h"

using namespace std;

int main()
{
	SceneManager* sceneManager = new SceneManager;

	sceneManager->initialize();
	sceneManager->setupMesh("Pikachu.obj");
	sceneManager->run();
	
	return 0;
}