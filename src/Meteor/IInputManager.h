// @author	Lee JinWoo (2013.10.20)
#pragma once

#include "InputState.h"

class IInputManager
{
public:
	virtual ~IInputManager() {};

	virtual InputState GetKeyState( int key ) = 0;
	virtual InputState GetMouseState() = 0;
};
