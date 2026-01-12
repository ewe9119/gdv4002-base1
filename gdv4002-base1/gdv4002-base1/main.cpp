#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Enemy.h"
#include <bitset>


// Function prototypes
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);



// Global Variables
std::bitset<5> keys{ 0x0 };

int main(void) {
// main function body

//Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games - Base 1", 800, 600);
	
	//If engine initialisation failed, exit program
	if (initResult != 0) {
	printf("Cannot setup game window\n");

		return initResult;
	}
	// Loading and creating player object

	GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png");

	Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 1.0f);

	addObject("player", mainPlayer);

	// 1. Load enemy texture 
	GLuint enemyTexture = loadTexture("Resources\\Textures\\alien01.png");

	// 2. Create enemy objects
	Enemy* enemy1 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(45.0f));

	Enemy* enemy2 = new Enemy(glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(90.0f));

	Enemy* enemy3 = new Enemy(glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(60.0f));

	// Add enemy objects to the engine
	addObject("enemy1", enemy1);
	addObject("enemy2", enemy2);
	addObject("enemy3", enemy3);


	//
	// Set callback functions
	//
	setKeyboardHandler(myKeyboardHandler);
	
	//This hanles the update and render calls
	engineMainLoop();

	// When we quit, like closing the window, this will clean up engine resources
	engineShutdown();

	return 0;	
		

}



void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if the key was just pressed
	if (action == GLFW_PRESS) {

		// now check which key was pressed...
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// If escape is pressed tell GLFW we want to close the window(and quit)
				glfwSetWindowShouldClose(window, true);
			break;
		case GLFW_KEY_W:
			keys[Key::W] = true;
			break;
		case GLFW_KEY_A:
			keys[Key::A] = true;
			break;
		case GLFW_KEY_S:
			keys[Key::S] = true;
			break;
		case GLFW_KEY_D:
			keys[Key::D] = true;
			break;

		}
	}
	// If not pressed, check the key has just been released
	else if (action == GLFW_RELEASE) {

		// handle key release events
		// handle key release events
		switch (key)
		{
		case GLFW_KEY_W:
			keys[Key::W] = false;
			break;
		case GLFW_KEY_A:
			keys[Key::A] = false;
			break;
		case GLFW_KEY_S:
			keys[Key::S] = false;
			break;
		case GLFW_KEY_D:
			keys[Key::D] = false;
			break;


		}

	}
}
