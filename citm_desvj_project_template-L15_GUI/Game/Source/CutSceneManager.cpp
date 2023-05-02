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
		if (Border == true) {
			app->render->DrawRectangle({ -app->render->camera.x ,(app->render->camera.y - 400 + Upperborder + 2*Yoffset),1280,400 }, 0, 0, 0);
			app->render->DrawRectangle({ -app->render->camera.x ,(app->render->camera.y + 720 - Upperborder + 2*Yoffset),1280,400 }, 0, 0, 0);
			if (Upperborder != 80) {
				Upperborder += 2;
			}
			if (Upperborder == 80) {
				BorderAnimation = true;
			}
		}
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

	return true;
}
void CutScene::StartCutScene(int x, int y, int speed = 100, bool bordered = true, int time = 10000)
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
}

void CutScene::EndCutScene() 
{
	CutsceneStarted = false;
	TimeStart = false;
	BorderAnimation = false;
}


bool CutScene::CleanUp()
{
	return true;
}
