// Game definition
#pragma once

#include "GameBase.h"
class ExampleGame : public GameBase
{
public:
	virtual int Init();
	virtual int Shutdown();
	virtual void Render();
	virtual void  Update();
};

