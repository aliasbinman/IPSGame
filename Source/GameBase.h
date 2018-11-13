// Game definition
#pragma once


class GameBase
{
public:

	virtual int Init()	=0;
	virtual int Shutdown() =0;
	virtual void Render() =0;
	virtual void Update() =0;
};
