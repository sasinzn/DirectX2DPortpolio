#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//�̸� �����ϵ� ���.
//pch pre compiled header

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <fstream>

using namespace std;

//DirectX
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex/DirectXTex.lib")

#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")
//////////////////////////////////////////

#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//////////////////////////////////////////
//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")

//////////////////////////////////////////
//FMOD
#include "FMOD/inc/fmod.hpp"
#ifdef _WIN64
#pragma comment(lib, "FMOD/lib/x64/fmod_vc.lib")
#else
#pragma comment(lib, "FMOD/lib/x86/fmod_vc.lib")
#endif
//////////////////////////////////////////
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX  Matrix;
typedef D3DXCOLOR   Color;
typedef UINT		uint;


#include "Interfaces/IObject.h"

#include "Utilities/SingletonBase.h"

#include "Systems/Graphics.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"
#include "Systems/Sounds.h"
#include "Systems/SRV.h"
#include "Systems/Text.h"

#include "Utilities/Gui.h"


#define DEVICE Graphics::Get()->GetDevice()
#define DC     Graphics::Get()->GetDC()

#define CHECK(p) assert(SUCCEEDED(p))
#define Zero(p) ZeroMemory(&p, sizeof(p))


#define SAFE_DELETE(p)		 { if(p) { delete(p);	   (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p);	   (p) = nullptr; } }
#define SAFE_RELEASE(p)		 { if(p) { (p)->Release(); (p) = nullptr; } }


#include "Utilities/DirectHelper.h"

#include "Renders/Resources/VertexTypes.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"
#include "Renders/Resources/Texture2D.h"

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"
#include "Renders/States.h"

#include "Utilities/BoundingBox.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"

#include "Systems/Camera.h"

//GameHeader
#include "Game/AI/State/BaseState.h"
#include "Game/AI/State/AttackState.h"
#include "Game/AI/State/IdleState.h"
#include "Game/AI/State/FSM.h"

#define WinMaxWidth 1280
#define WinMaxHeight 720

const wstring ShaderPath				= L"../_Shaders/";
const wstring TexturePath				= L"../_Resources/_Textures/";
const wstring TextureMapCityPath		= L"../_Resources/_Textures/Map/City/";
const wstring TextureMapRoadPath		= L"../_Resources/_Textures/Map/Road/";
const wstring TextureMapMenuPath		= L"../_Resources/_Textures/Map/Menu/";
const wstring TextureMapBattlePath		= L"../_Resources/_Textures/Map/Battle/";
const wstring TextureNPCDialogPath		= L"../_Resources/_Textures/Map/NPC/Dialog/";
const wstring TextureNPCPath			= L"../_Resources/_Textures/Map/NPC/";
const wstring TextureMapPath			= L"../_Resources/_Textures/Map/";
const wstring SoundPath					= L"../_Resources/_Sounds/";
const string TilePath					= "../_Resources/_TileData/";
const wstring TexturePmFrontPath		= L"../_Resources/_Textures/Pokemon/Front/";
const wstring TexturePmBackPath			= L"../_Resources/_Textures/Pokemon/Back/";

extern HWND handle;

#define CAMERA Camera::Get()
#define GRAPHICS Graphics::Get()
#define KEYBOARD Keyboard::Get()
#define MOUSE Mouse::Get()
#define SOUND Sounds::Get()
#define TIME Time::Get()

enum SelectMove
{
	FIGHT = 0,
	BAG,
	POKEMON,
	RUN,
	BagItem,
	BagKeyItem,
	BagPokeBalls,
};

enum Direction
{
	EAST = 0,
	WEST,
	SOUTH,
	NORTH,
	STAY,
};

enum PmType
{
	TypeNull = 0,
	NormalType,			//��� Ÿ��
	FireType,			//�� Ÿ��
	WaterType,			//�� Ÿ��
	LeafType,			//Ǯ Ÿ��
	ElectricType,		//���� Ÿ��
	IceType,			//���� Ÿ��
	FightingType,		//���� Ÿ��
	PoisonType,			//�� Ÿ��
	GroundType,			//�� Ÿ��
	FlyingType,			//���� Ÿ��
	PsychicType,		//������ Ÿ��
	BugType,			//���� Ÿ��
	RockType,			//���� Ÿ��
	GhostType,			//��Ʈ Ÿ��
	DragonType,			//�巡�� Ÿ��
	DarkType,			//�� Ÿ��
	SteelType,			//��ö Ÿ��
	FairyType,			//�� Ÿ��
};

enum SkillType
{
	PhysicsType=0,
	SpecialType,
	ChangeType,
};

enum MenuTree
{
	TopMenu = 0,
	SubMenu,

};

enum BattleSequence
{
	BattleEnd = 0,
	TurnEnd,
	ResultPop,
	GotchaPokemon,
	UsingPokeball,
	UsingItem,
	SwitchingPokemon,
	TextRendering,
	DamageCalc,
	SelectSkill,
	TurnStart,
	Wait,
};

enum ItemType
{
	ItemNull = 0,			// null��
	Promote,				// ����
	Feild,					// �ʵ�
	Evolution,				// ��ȭ
	Heal,					// ġ��
	MonsterBall,			// ���ͺ�
	BattleItem,				// ��Ʋ������
	Fruit,					// ��������
	TechnicalMachine,		// ����ӽ�
	VisionMachine,			// �����ӽ�
	TechnicalRecord,		// ������ڵ�
	Treasure,				// ����
	ImportantArticle,		// �߿��ѹ���
	PokemonDex,				// ���ϸ󵵰�
	MainInstrument,			// �ֿ���
};
/*
enum BallList
{
	MonsterBall=0,
	SuperBall,
	HyperBall,
	MasterBall,
	SafariBall,
	SportBall,
	LevelBall,
	FriendBall,
	LureBall,
	MoonBall,
	LoveBall,
	SpeedBall,
	HeavyBall,
	PremierBall,
	NetBall,
	DiveBall,
	NestBall,
	TimerBall,
	RepeatBall,
	LuxuryBall,
	CherishBall,
	HealBall,
	DuskBall,
	QuickBall,
	ParkBall,
	DreamBall,
	StrangeBall,
};
*/

struct StatusData
{
	int hp;		// ü��
	int atk;	// ����
	int def;	// ���
	int sAtk;	// Ư������
	int sDef;	// Ư�����
	int spd;	// ���ǵ�
};

struct SkillData
{
	PmType ptype;			// �Ӽ� Ÿ��
	string name;			// ��ų �̸�
	SkillType stype;		// ��ų Ÿ��
	int power;				// ��ų ����
	int accuracy;			// ��ų ���߷�
	int pp;					// ��ų Ƚ��
};