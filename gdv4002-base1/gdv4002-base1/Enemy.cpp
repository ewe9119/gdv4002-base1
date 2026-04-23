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

    // wander system
    float angle = (float(rand()) / RAND_MAX) * 6.2831853f;
    wanderDir = glm::vec2(cos(angle), sin(angle));
    wanderTimer = 0.0f;
}

void Enemy::update(double tDelta) {

    // enemies wandering
    wanderTimer += (float)tDelta;

    if (wanderTimer > 1.0f) {

        glm::vec2 newDir(
            (float(rand()) / RAND_MAX) * 2.0f - 1.0f,
            (float(rand()) / RAND_MAX) * 2.0f - 1.0f
        );

        if (glm::length(newDir) > 0.0f) {
            wanderDir = glm::normalize(newDir);
        }

        wanderTimer = 0.0f;
    }

    //  continuous movement force
    velocity += wanderDir * 0.4f;

	//enemy separation
    GameObjectCollection enemies = getObjectCollection("enemy");

    for (int i = 0; i < enemies.objectCount; i++) {

        Enemy* other = (Enemy*)enemies.objectArray[i];

        if (other == this) continue;

        glm::vec2 diff = position - other->position;
        float dist = glm::length(diff);

        float minDist = size.x;

        if (dist > 0.0001f && dist < minDist) {

            glm::vec2 pushDir = diff / dist;

            float strength = (minDist - dist) * 0.8f;

            velocity += pushDir * strength;
        }
    }


    //stability
    
    velocity *= 0.99f;

    float maxSpeed = 2.0f;

    if (glm::length(velocity) > maxSpeed) {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    // movement
    position += velocity * (float)tDelta;

    phaseAngle += phaseVelocity * tDelta;

    float halfWidth = getViewplaneWidth() / 2.0f;
    float halfHeight = getViewplaneHeight() / 2.0f;

    // soft bounce movement
    if (position.x - size.x / 2 < -halfWidth) {
        position.x = -halfWidth + size.x / 2;
        velocity.x = abs(velocity.x) * 0.5f;
    }

    if (position.x + size.x / 2 > halfWidth) {
        position.x = halfWidth - size.x / 2;
        velocity.x = -abs(velocity.x) * 0.5f;
    }

    if (position.y - size.y / 2 < -halfHeight) {
        position.y = -halfHeight + size.y / 2;
        velocity.y = abs(velocity.y) * 0.5f;
    }

    if (position.y + size.y / 2 > halfHeight) {
        position.y = halfHeight - size.y / 2;
        velocity.y = -abs(velocity.y) * 0.5f;
    }
}

