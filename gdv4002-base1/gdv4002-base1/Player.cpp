#include "Player.h"
#include "Keys.h"
#include "Engine.h"
#include "Enemy.h"
#include <bitset>

extern std::bitset<5> keys;
extern glm::vec2 gravity;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass)
    : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

    this->mass = mass;
    this->size = initSize;

    velocity = glm::vec2(0.0f, 0.0f);
}

void Player::update(double tDelta) {

    float halfWidth = getViewplaneWidth() / 2.0f;
    float halfHeight = getViewplaneHeight() / 2.0f;

    size = glm::vec2(1.0f, 1.0f);

    glm::vec2 accel(0.0f, 0.0f);
    glm::vec2 inputDir(0.0f);

    const float thrust = 60.0f;

    // Input
    if (keys[Key::W]) { accel.y += thrust; inputDir.y += 1.0f; }
    if (keys[Key::S]) { accel.y -= thrust; inputDir.y -= 1.0f; }
    if (keys[Key::A]) { accel.x -= thrust; inputDir.x -= 1.0f; }
    if (keys[Key::D]) { accel.x += thrust; inputDir.x += 1.0f; }

    // Rotation
    if (inputDir != glm::vec2(0.0f)) {
        inputDir = glm::normalize(inputDir);
        orientation = atan2(inputDir.y, inputDir.x);
    }

    // Physics 
    velocity += accel * (float)tDelta;

    float maxSpeed = 4.5f;
    if (glm::length(velocity) > maxSpeed) {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    // Smooth slowdown
    velocity *= 0.985f;

    position += velocity * (float)tDelta;

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