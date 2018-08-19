#pragma once

#include "State.h"

class MainMenuState : public State
{

public:
	void Init() = 0;

	void HandleInput();
	void Update(float dt0);
	void Draw(float dt);

	void Pause() { }
	void Resume() { }
};