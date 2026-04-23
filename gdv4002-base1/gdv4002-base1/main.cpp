#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Enemy.h"
#include "Emitter.h"
#include "glPrint.h"
#include <bitset>


// Function prototypes
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
// Delete functions
void deleteSnowlakes(GLFWwindow* window, double tDelta);
void myRender(GLFWwindow* window);

// Snowflake gravity
glm::vec2 gravity = glm::vec2(0.0f, -2.0f);

std::bitset<5> keys{ 0x0 };

int main(void) {
	GLuint myFontNormal = 0;
	GLuint myFontUnderline = 0;

	// Engine initialisation 
	int initResult = engineInit("GDV4002 - Applied Maths for Games - Base 1", 800, 600, 5.0f);
	setViewplaneWidth(10.0f);

	//If engine initialisation failed, exit program
	if (initResult != 0) {
		printf("Cannot setup game window\n");
		return initResult;
	}

	// Snowflake emitter
	Emitter* emitter = new Emitter(
		glm::vec2(0.0f, getViewplaneHeight() / 2.0f), // spawn at top of screen
		glm::vec2(getViewplaneWidth() / 2.0f, 0.0f),
		0.05f
	);

	addObject("emitter", emitter);

	// Loading background
	GLuint bgTexture = loadTexture("Resources\\Textures\\background.png");

	GameObject2D* background = new GameObject2D(
		glm::vec2(0.0f, 0.0f),
		0.0f,
		glm::vec2(10.0f, 10.0f),
		bgTexture
	);

	addObject("background", background);

	myFontNormal = glBuildFont(L"Consolas", 24);
	myFontUnderline = glBuildFont(L"Aptos", 24, GLFONT_STYLE::BOLD | GLFONT_STYLE::UNDERLINE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_ALWAYS);

	// Player
	GLuint playerTexture = loadTexture("Resources\\Textures\\player2_ship.png");

	Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 1.0f);
	addObject("player", mainPlayer);

	// Enemies
	GLuint enemyTexture = loadTexture("Resources\\Textures\\alien02.png");

	Enemy* enemy1 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(45.0f));
	Enemy* enemy2 = new Enemy(glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(90.0f));
	Enemy* enemy3 = new Enemy(glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(60.0f));
	Enemy* enemy4 = new Enemy(glm::vec2(3.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(60.0f));
	Enemy* enemy5 = new Enemy(glm::vec2(4.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(60.0f));

	addObject("enemy1", enemy1);
	addObject("enemy2", enemy2);
	addObject("enemy3", enemy3);
	addObject("enemy4", enemy4);
	addObject("enemy5", enemy5);

	// Callbacks
	setKeyboardHandler(myKeyboardHandler);

	setKeyboardHandler(myKeyboardHandler);
	// setRenderFunction(myRender);

	// Main loop
	engineMainLoop();

	engineShutdown();
	return 0;
}


void deleteSnowlakes(GLFWwindow* window, double tDelta) {

	GameObjectCollection snowflakes = getObjectCollection("snowflake");

	for (int i = 0; i < snowflakes.objectCount; i++) {

		if (snowflakes.objectArray[i]->position.y < -(getViewplaneHeight() / 2.0f)) {

			deleteObject(snowflakes.objectArray[i]);
		}
	}
}


// Keyboard inputs
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
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
	else if (action == GLFW_RELEASE) {
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

void myRender(GLFWwindow* window)
{
}
