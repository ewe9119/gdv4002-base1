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
    size = glm::vec2(1.0f, 1.0f);
    glm::vec2 F = glm::vec2(0.0f, 0.0f);
    glm::vec2 inputDir = glm::vec2(0.0f, 0.0f);

    const float thrust = 2.0f;

    // Input
    if (keys.test(Key::W)) { F.y += thrust; inputDir.y += 1.0f; }
    if (keys.test(Key::S)) { F.y -= thrust; inputDir.y -= 1.0f; }
    if (keys.test(Key::A)) { F.x -= thrust; inputDir.x -= 1.0f; }
    if (keys.test(Key::D)) { F.x += thrust; inputDir.x += 1.0f; }

    F += gravity;

    // Rotation
    if (inputDir != glm::vec2(0.0f)) {
        inputDir = glm::normalize(inputDir);
        orientation = atan2(inputDir.y, inputDir.x);
    }

    // Physics
    glm::vec2 a = F * (1.0f / mass);
    velocity += a * (float)tDelta;
    position += velocity * (float)tDelta;

    // ===== COLLISION =====
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