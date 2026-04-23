#include "Enemy.h"
#include "Engine.h"

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

	// random drifting 
	velocity.x += ((rand() % 100) / 100.0f - 0.5f) * 0.01f;
	velocity.y += ((rand() % 100) / 100.0f - 0.5f) * 0.01f;

	// max speed 
	float maxSpeed = 2.0f;

	// clamp speed
	if (glm::length(velocity) > maxSpeed) {
		velocity = glm::normalize(velocity) * maxSpeed;
	}

	//  movement
	position += velocity * (float)tDelta;

	//enemy collision
	GameObjectCollection enemies = getObjectCollection("enemy");

	for (int i = 0; i < enemies.objectCount; i++) {

		Enemy* other = (Enemy*)enemies.objectArray[i];

		if (other == this) continue;

		glm::vec2 diff = position - other->position;
		float dist = glm::length(diff);

		float minDist = (size.x / 2.0f) + (other->size.x / 2.0f);

		if (dist < minDist && dist > 0.0f) {

			glm::vec2 pushDir = glm::normalize(diff);
			float overlap = minDist - dist;

			// push apart
			position += pushDir * (overlap * 0.5f);
			other->position -= pushDir * (overlap * 0.5f);

			// smooth bounce
			velocity += pushDir * 0.5f;
			other->velocity -= pushDir * 0.5f;
		}
	}

	// motion
	position.y += sinf(phaseAngle) * 0.01f;

	// update phase
	phaseAngle += phaseVelocity * tDelta;


	float halfWidth = getViewplaneWidth() / 2.0f;
	float halfHeight = getViewplaneHeight() / 2.0f;

	// left
	if (position.x - size.x / 2 < -halfWidth) {
		position.x = -halfWidth + size.x / 2;
		velocity.x *= -1.0f; // enemy bounce
	}

	// right
	if (position.x + size.x / 2 > halfWidth) {
		position.x = halfWidth - size.x / 2;
		velocity.x *= -1.0f; // enemy bounce
	}

	// bottom
	if (position.y - size.y / 2 < -halfHeight) {
		position.y = -halfHeight + size.y / 2;
		velocity.y *= -1.0f; // enemy bounce
	}

	// top
	if (position.y + size.y / 2 > halfHeight) {
		position.y = halfHeight - size.y / 2;
		velocity.y *= -1.0f; // enemy bounce
	}
}

