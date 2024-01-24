#pragma once

#include "Game/Actor/Character.h"
#include "Game\UI\ProgressBar.h"
#include "GeoMetries\TextureRect.h"





class PMCenterNPC : public Character
{
public:
	PMCenterNPC(Vector3 position, Vector3 size);
	~PMCenterNPC();

	virtual void Update() override;
	virtual void Render() override;

	Vector3 GetPos() { return animRect->GetPosition(); }
	BoundingBox* GetCollision() { return collision; }
	bool InterActionNPC(BoundingBox* player);
	void Question();
	void Reset();
	
	void SetHold() { holding = true; }
	void SetMove() { holding = false; }


private:
	BoundingBox* collision;
	class ProgressBar* select = nullptr;		// ����â Y or N
	class ProgressBar* dialog = nullptr;		// �⺻ �λ�â
	class ProgressBar* dialogN1 = nullptr;		// ����â���� N ���ý�
	class ProgressBar* dialogY1 = nullptr;		// ����â���� Y ���ý�
	class ProgressBar* dialogY2 = nullptr;		// Y������ �����ð���
	class ProgressBar* dialogY3 = nullptr;		// Y������ �����ð���
	class ProgressBar* selectN = nullptr;		// N���� ȭ��ǥ
	class ProgressBar* selectY = nullptr;		// Y���� ȭ��ǥ
	class TextureRect* monsterBall1 = nullptr;
	class TextureRect* monsterBall2 = nullptr;
	class TextureRect* monsterBall3 = nullptr;
	class TextureRect* monsterBall4 = nullptr;
	class TextureRect* monsterBall5 = nullptr;
	class TextureRect* monsterBall6 = nullptr;
	class TextureRect* ballLight = nullptr;



	bool holding;								// �÷��̾� �̵��Ұ� �Ǻ�
	bool interaction;	// NPC��ȣ�ۿ� ����
	bool textrending;	// �ؽ�Ʈ ��� ����
	bool healing;		// ü��ȸ�� ����
	int textnum;		// �ؽ�Ʈ ����
	bool selectArrow;	// ����ȭ��ǥ
	bool selectHealing;	// ȸ�� ����
	float deltatime;

};
