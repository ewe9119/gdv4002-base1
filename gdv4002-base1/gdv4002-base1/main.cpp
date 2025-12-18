#include "Engine.h"


// Function prototypes


// Global Variables


int main(void) {

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
	//
	// addObject("player", glm::vec2(1.0f, 1.0f), glm::radians(45.0f), glm::vec2(0.5f, 1.0f), "Resources\\Textures\\mcblock01.png", TextureProperties::NearestFilterTexture());
	addObject("player1");

	addObject("player2");

	GameObject2D* player1Object = getObject("player1");

	if (player1Object != nullptr) {

		//update player1 here
		player1Object->position = glm::vec2(-1.0f, 1.0f);
	}
	GameObject2D* player2Object = getObject("player2");
	
	if (player2Object != nullptr) {

		player2Object->position = glm::vec2(1.5f, 1.0f);
	}

	//
	// Set callback functions
	//
	

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}
