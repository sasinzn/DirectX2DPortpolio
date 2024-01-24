#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"
#include "Demos/01_RectDemo.h"
#include "Demos/02_StarDemo.h"
#include "Demos/03_TextureDemo.h"
#include "Demos/04_ShadedDemo.h"
#include "Demos/05_BlurDemo.h"
#include "Demos/06_RenderingTargetDemo.h"
#include "Demos/07_CollisionDemo.h"
#include "Demos/08_RectGameDemo.h"
#include "Demos/09_AnimationDemo.h"
#include "Demos/10_PlayerDemo.h"
#include "Demos/11_TileMapDemo.h"

#include "99.MainGame/MainGame.h"

void Program::Init()
{
	States::Create();
	Camera::Create();


//	Push(new RectDemo);
//	Push(new StarDemo);
//  Push(new TextureDemo);
//	Push(new ShadedDemo);
//	Push(new BlurDemo);
//	Push(new RenderingTargetDemo);
//	Push(new CollisionDemo);
//	Push(new RectGameDemo);
//	Push(new AnimationDemo);
//	Push(new PlayerDemo);
//	Push(new TileMapDemo);
	Push(new MainGame);
}

void Program::Destroy()
{
	Camera::Delete();


	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();
	Camera::Get()->Move();
	Camera::Get()->Update();
}

void Program::Render()
{
	Camera::Get()->Render();

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
