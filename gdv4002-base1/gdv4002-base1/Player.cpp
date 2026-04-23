#include "Player.h"
#include "Keys.h"
#include "Engine.h"
#include "Enemy.h"
#include <bitset>

extern std::bitset<5> keys;
extern glm::vec2 gravity;
Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;

	this->size = initSize;

	velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
}

void Player::update(double tDelta) {

    float halfWidth = getViewplaneWidth() / 2.0f;
    float halfHeight = getViewplaneHeight() / 2.0f;

    size = glm::vec2(1.0f, 1.0f);

    glm::vec2 accel(0.0f, 0.0f);
    glm::vec2 inputDir(0.0f);

    const float thrust = 15.0f;

    // Input
    if (keys[Key::W]) { accel.y += thrust; inputDir.y += 1.0f; }
    if (keys[Key::S]) { accel.y -= thrust; inputDir.y -= 1.0f; }
    if (keys[Key::A]) { accel.x -= thrust; inputDir.x -= 1.0f; }
    if (keys[Key::D]) { accel.x += thrust; inputDir.x += 1.0f; }

    // Gravity (ONLY when player is moving or already has velocity)
    if (keys[Key::W] || keys[Key::A] || keys[Key::S] || keys[Key::D]) {
        accel += gravity * 0.5f;
    }
    else {
        //fully stop drifting when no input
        accel = glm::vec2(0.0f, 0.0f);
    }

    // Rotation
    if (inputDir != glm::vec2(0.0f)) {
        inputDir = glm::normalize(inputDir);
        orientation = atan2(inputDir.y, inputDir.x);
    }

    // Physics
    velocity += accel * (float)tDelta;
    position += velocity * (float)tDelta;

    // Player collision
    GameObjectCollection enemies = getObjectCollection("enemy");

     for (int i = 0; i < enemies.objectCount; i++) {

         Enemy* enemy = (Enemy*)enemies.objectArray[i];

         glm::vec2 diff = position - enemy->position;
         float dist = glm::length(diff);

         float minDist = (size.x / 2.0f) + (enemy->size.x / 2.0f);
         if (dist < minDist && dist > 0.0001f) {
             glm::vec2 pushDir = diff / dist;

             // push apart
             position += pushDir * (minDist - dist);
			 // knockback
             velocity += pushDir * 2.0f;
         }
	 }

    // Smooth slowdown
    velocity *= 0.92f;


    // Collision
    float halfSizeX = size.x * 0.5f;
    float halfSizeY = size.y * 0.5f;

    if (position.x - halfSizeX < -halfWidth) {
        position.x = -halfWidth + halfSizeX;
        velocity.x = 0.0f;
    }

    if (position.x + halfSizeX > halfWidth) {
        position.x = halfWidth - halfSizeX;
        velocity.x = 0.0f;
    }

    if (position.y - halfSizeY < -halfHeight) {
        position.y = -halfHeight + halfSizeY;
        velocity.y = 0.0f;
    }

    if (position.y + halfSizeY > halfHeight) {
        position.y = halfHeight - halfSizeY;
        velocity.y = 0.0f;
    }
}