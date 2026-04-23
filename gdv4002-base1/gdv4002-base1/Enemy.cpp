#include "Enemy.h"

Enemy::Enemy(
	glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float initialPhase,
	float initialPhaseVelocity)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	phaseAngle = initialPhase;
	phaseVelocity = initialPhaseVelocity;

	velocity = glm::vec2(0.0f, 0.0f);
}
void Enemy::update(double tDelta) {

	// RANDOM DRIFT 
	velocity.x += ((rand() % 100) / 100.0f - 0.5f) * 0.01f;
	velocity.y += ((rand() % 100) / 100.0f - 0.5f) * 0.01f;

	// LIMIT SPEED 
	float maxSpeed = 2.0f;


	// free movement
	position += velocity * (float)tDelta;

	// keep your sine motion BUT apply it properly
	position.y += sinf(phaseAngle) * 0.01f;

	// update phase
	phaseAngle += phaseVelocity * tDelta;
}
