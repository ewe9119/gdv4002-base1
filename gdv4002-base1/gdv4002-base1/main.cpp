#include "Engine.h"


// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);
//void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);



// Global Variables


int main(void) {
// main function body

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}
	else {

		printf("Window setup okay!\n");

	}

	//
	// Setup game scene objects here

	// addObject("player", glm::vec2(1.0f, 1.0f), glm::radians(45.0f), glm::vec2(0.5f, 1.0f), "Resources\\Textures\\mcblock01.png", TextureProperties::NearestFilterTexture());
	addObject("player1", glm::vec2(1.5f, 1.0f), glm::radians(-30.0f), glm::vec2(1.0f, 1.0f), "Resources\\Textures\\bumblebee.png");

	addObject("player2", glm::vec2(1.5f, 1.0f), glm::radians(45.0f), glm::vec2(1.0f, 1.0f), "Resources\\Textures\\bumblebee.png");

	GameObject2D* player1Object = getObject("player1");

	if (player1Object != nullptr) {

		//update player1 here
		player1Object->position = glm::vec2(-1.0f, 1.0f);
		player1Object->orientation = glm::radians(-30.0f);
		player1Object->textureID=loadTexture("Resources\\Textures\\bumblebee.png");
		
	}
	GameObject2D* player2Object = getObject("player2");
	
	if (player2Object != nullptr) {

		player2Object->position = glm::vec2(1.5f, 1.0f);
		player2Object->orientation = glm::radians(45.0f);
	}

	//
	// Set callback functions
	//
	
	//setUpdateFunction(myUpdate);
	//setKeyboardHandler(myKeyboardHandler);

	//listGameObjectKeys();
	//listObjectCounts();


	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// Whe0n we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}
void myUpdate(GLFWwindow* window, double tDelta) {
	float player1RotationSpeed = glm::radians(90.0f);
	GameObject2D* player1 = getObject("player1");
	player1->orientation += player1->orientation + glm::radians(1.5);
}
dfgbvcfgd