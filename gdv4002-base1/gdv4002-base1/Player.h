#pragma once
#include "GameObject2D.h"

class Player : public GameObject2D {

private:
	float playerSpeed;


public:
	Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPlayerSpeed);

	void update(double tDelta) override;



};
