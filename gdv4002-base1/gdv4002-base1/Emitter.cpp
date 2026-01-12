#include "Emitter.h"
#include "Engine.h"
#include "Snowflake.h"


using namespace std;


Emitter::Emitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0) {
	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;
	particleNumber = 0;
	for (int i = 0; i < 8; i++) {

		string path = "Resources\\Textures\\Snow\\snowflake" + to_string(i + 1) + string(".png");
		snowflakes[i] = loadTexture(path.c_str());

		if (snowflakes[i] > 0)
			cout << "successfully loaded texture " << path << endl;
		else
			cout << "failed to load texture " << path << endl;
	}
	// Obtain a seed for the random number engine
	random_device rd;

	// Standard mersenne_twister_engine seeded with rd() - mt19937 is a high-quality pseudo-random number generator
	gen = mt19937(rd());

	spriteDist = uniform_int_distribution<int>(0, 7);
	normDist = uniform_real_distribution<float>(-1.0f, 1.0f);
	massDist = uniform_real_distribution<float>(0.005f, 0.08f);
	scaleDist = uniform_real_distribution<float>(0.1f, 0.5f);
}
// override render but do nothing - we'll not render anything for the emitter 
void Emitter::render() {
}
void Emitter::update(double tDelta) {

	emitCounter += (float)tDelta;

	while (emitCounter >= emitTimeInterval) {

		// decrease emitCounter by emitTimeInterval - don't set to 0 as this would ignore the case where multiple particles are needed.
		emitCounter -= emitTimeInterval;

		// Create new particle
		float x = position.x + normDist(gen) * size.x;
		float y = position.y + normDist(gen) * size.y;
		float scale = scaleDist(gen);
		float mass = massDist(gen);
		float rotationSpeed = glm::radians(normDist(gen) * 45.0f);
		int spriteIndex = spriteDist(gen);

		Snowflake* s1 = new Snowflake(glm::vec2(x, y), 0.0f, glm::vec2(scale, scale), snowflakes[spriteIndex], mass, rotationSpeed);
		string key = string("snowflake");

		if (particleNumber > 0) { // first name in collection must not be numbered if using this approach

			// add value so unique anyway - not using engine mechanism
			key += to_string(particleNumber);
		}

		particleNumber++;

	}
}

