#include "CutSceneManager.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Window.h"

CutScene::CutScene()
{
	name.Create("CUT");
	LOG("CREATING CUTSCENE MANAGER");
}

CutScene::~CutScene() {

}

bool CutScene::Awake() {


	return true;
}

bool CutScene::Start() {

	return true;
}

bool CutScene::Update()
{
	if (CutsceneStarted == true) {
		//Border animation
		if (Border == true) {
			app->render->DrawRectangle({ -app->render->camera.x,(app->render->camera.y - 400 + Upperborder + 2 * Yoffset),1280,400 }, 0, 0, 0);
			app->render->DrawRectangle({ -app->render->camera.x,(app->render->camera.y + 720 - Upperborder + 2 * Yoffset),1280,400 }, 0, 0, 0);
			if (Upperborder != 80) {
				Upperborder += 2;
			}
			if (Upperborder == 80) {
				BorderAnimation = true;
			}
		}
		if (StartTP == false) {
			//If border animation is done, start moving
			if (BorderAnimation == true) {
				//Start counting miliseconds
				if (TimeStart == false) {
					Timer1 = SDL_GetTicks();
					TimeStart = true;
					Xdif = app->render->camera.x - X;
					Ydif = app->render->camera.y - Y;
					Xsum = Xdif / Speed;
					Ysum = Ydif / Speed;
				}
				Timer2 = SDL_GetTicks();
				if (app->render->camera.x != X) {
					app->render->camera.x -= Xsum;
				}
				if (app->render->camera.y != Y) {
					app->render->camera.y -= Ysum;
					Yoffset += Ysum;
				}
				if (app->render->camera.x >= X + 5 && app->render->camera.x <= X - 5) {
					app->render->camera.x = X;
				}
				if (app->render->camera.y >= Y + 5 && app->render->camera.y <= Y - 5) {
					app->render->camera.y = Y;
				}
				if (Timer2 >= Timer1 + Time) {
					app->render->camera.x = X;
					app->render->camera.y = Y;
				}
			}
		}
		if (StartTP == true) {
			app->render->DrawRectangle({ -1000, -1000,5000,5000 }, 0, 0, 0, fading);
			//Fade in
			if (faded == false && fading != 255) {
				fading += fadingS;
				if (fading >= 255) {
					fading = 255;
					faded = true;
				}
			}
			//TP
			if (faded == true && fading != 0) {
				Border = false;
				app->render->camera.x = X;
				app->render->camera.y = Y;
				fading -= fadingS;
				if (fading <= 0) {
					fading = 0;
					StartTP = false;
					BorderAnimation = true;
				}
			}
		}
	}

	return true;
}
void CutScene::StartCutScene(bool startTP, int fadingspeed, int x, int y, int speed = 100, bool bordered = true, int time = 10000)
{
	X = x;
	Y = y;
	Speed = speed;
	Border = bordered;
	if (Border == false) {
		BorderAnimation = true;
	}
	Time = time;
	CutsceneStarted = true;
	StartTP = startTP;
	fadingS = fadingspeed;
}

void CutScene::EndCutScene() 
{
	CutsceneStarted = false;
	TimeStart = false;
	BorderAnimation = false;
	fading = 0;
	faded = false;
	Border = false;
	Upperborder = 0;
	Yoffset = 0;
}


bool CutScene::CleanUp()
{
	return true;
}
