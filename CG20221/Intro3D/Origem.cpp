#include "SceneManager.h"

using namespace std;

int main()
{
	SceneManager* sceneManager = new SceneManager;

	sceneManager->initialize();
	sceneManager->setupCube();
	sceneManager->run();
	
	return 0;
}