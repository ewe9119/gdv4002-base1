#include "Player.h"
#include "Keys.h"
#include "Engine.h"
#include <bitset>

extern std::bitset<5> keys;
extern glm::vec2 gravity;
Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f); // default to 0 velocity
}

void Player::update(double tDelta) {

    float halfWidth = getViewplaneWidth() / 2.0f;
    float halfHeight = getViewplaneHeight() / 2.0f;

    // Clamp X
    if (position.x - size.x / 2 < -halfWidth)
        position.x = -halfWidth + size.x / 2;

    if (position.x + size.x / 2 > halfWidth)
        position.x = halfWidth - size.x / 2;

    // Clamp Y
    if (position.y - size.y / 2 < -halfHeight)
        position.y = -halfHeight + size.y / 2;

    if (position.y + size.y / 2 > halfHeight)
        position.y = halfHeight - size.y / 2;

    glm::vec2 F = glm::vec2(0.0f, 0.0f);
    glm::vec2 inputDir = glm::vec2(0.0f, 0.0f);
    orientation = atan2(inputDir.y, inputDir.x);

    const float thrust = 2.0f;

    // 1. accumulate forces + track direction
    if (keys.test(Key::W)) {
        F += glm::vec2(0.0f, thrust);
        inputDir.y += 1.0f;
    }
    if (keys.test(Key::S)) {
        F += glm::vec2(0.0f, -thrust);
        inputDir.y -= 1.0f;
    }
    if (keys.test(Key::A)) {
        F += glm::vec2(-thrust, 0.0f);
        inputDir.x -= 1.0f;
    }
    if (keys.test(Key::D)) {
        F += glm::vec2(thrust, 0.0f);
        inputDir.x += 1.0f;
    }

    // Apply gravity OUTSIDE key input 
    F += gravity;

    // add impulse force (bounce)
    if (position.y < -getViewplaneHeight() / 2.0f) {
        F += glm::vec2(0.0f, 20.0f);
    }

    //Rotate player to face movement direction
    if (inputDir != glm::vec2(0.0f)) {
        inputDir = glm::normalize(inputDir);
        orientation = atan2(inputDir.y, inputDir.x);
    }

    // 2. calculate acceleration
    glm::vec2 a = F * (1.0f / mass);

    // 3. integrate velocity
    velocity = velocity + (a * (float)tDelta);

    // 4. integrate position
    position = position + (velocity * (float)tDelta);

    // ===== SCREEN COLLIDER =====


    float halfSizeX = size.x * 0.5f;
    float halfSizeY = size.y * 0.5f;

    // Left / Right
    if (position.x - halfSizeX < -halfWidth)
    {
        position.x = -halfWidth + halfSizeX;
        velocity.x = 0.0f; // optional: stop movement
    }

    if (position.x + halfSizeX > halfWidth)
    {
        position.x = halfWidth - halfSizeX;
        velocity.x = 0.0f;
    }

    // Bottom / Top
    if (position.y - halfSizeY < -halfHeight)
    {
        position.y = -halfHeight + halfSizeY;
        velocity.y = 0.0f;
    }

    if (position.y + halfSizeY > halfHeight)
    {
        position.y = halfHeight - halfSizeY;
        velocity.y = 0.0f;
    }
}
