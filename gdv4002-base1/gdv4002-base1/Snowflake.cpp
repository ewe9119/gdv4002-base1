#include "Snowflake.h"
#include "Engine.h"
extern glm::vec2 gravity;

Snowflake::Snowflake(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);

	this->angleChangePerSecond = angleChangePerSecond;
}
void Snowflake::update(double tDelta) {

    // Physics 

    // slow falling
	position.y -= mass * 0.0001f * (float)tDelta;

    // Apply gravity
    glm::vec2 accel = gravity / mass;

    // Update velocity
    velocity += accel * 0.2f * (float)tDelta;

    // Update position
    position += velocity * (float)tDelta;

    // Rotation
    orientation += angleChangePerSecond * (float)tDelta;

    //Drifting snow
	position.x += sinf(glfwGetTime()) * 0.1f * (float)tDelta;


    //
    float halfHeight = getViewplaneHeight() / 2.0f;

    if (position.y < -halfHeight) {
        position.y = halfHeight;   // send back to top
        velocity.y = 0.002f;         // reset fall speed
    }
}
