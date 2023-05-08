#ifndef __CUTSCENEMANAGER_H__
#define __CUTSCENEMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "Point.h"
#include "List.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class CutScene : public Module
{
public:

	CutScene();
	
	virtual ~CutScene();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void StartCutScene(bool startTP, int fadeSpeed, int x, int y, int speed, bool bordered, int time );

	void EndCutScene();

public:
	bool CutsceneStarted = false;
private:
	float X, Xdif, Xsum, Y, Ydif, Ysum, Speed, Time;
	bool Border = false, TimeStart = false, BorderAnimation = false, StartTP = false;

	//Fading
	int fading = 0, fadingS = 5;
	bool faded = false;

	float Timer1, Timer2;
	int Upperborder = 0, Yoffset = 0;
};

#endif // __CUTSCENEMANAGER_H__