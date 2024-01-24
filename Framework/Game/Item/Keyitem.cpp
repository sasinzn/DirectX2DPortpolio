#include "Framework.h"
#include "Keyitem.h"

#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"

Keyitem::Keyitem()
{
	Texture2D* srcTex = new Texture2D(TextureMapMenuPath + L"KeyItem.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	KeyitemClip = new AnimationClip(L"KeyitemClip", srcTex, 10, { 0,0 }, texSize);

#pragma region Item name explain 

	// 1. ����������
	name.push_back("����������");
	explain.push_back("       ���ϸ� Ÿ������ ���Ǵ� �����̴�.      ");

	name.push_back("��Ʋ��");
	explain.push_back("         �������� �Ҿ���� Ʋ��.           ");

	name.push_back("��");
	explain.push_back("�ణ �����ϰ� ������ ��Ⱑ ���� ��.\n ������ ���� ����������.");

	name.push_back("��Ƽ���� ����");
	explain.push_back("     ������Ƽ ü���� ���� ��Ƽ���� ����.     ");

	name.push_back("Ÿ���");
	explain.push_back("          ���������� �����̴�.       ");

	name.push_back("�¼�Ƽ��");
	explain.push_back("��Ӽ� ��Ʈ�Ӵ�ȣ�� Ż �� �ʿ��� �¼�Ƽ��.\n �� �׸��� �׷��� �ִ�.");

	name.push_back("�����ٹ���");
	explain.push_back("��Ͻ�Ƽ �����鸮�� �������Լ�\n ���ڻ翡�� �ǳ��ֵ��� ��Ź���� ����.");

	name.push_back("����� ����");
	explain.push_back("ȫ��ü������ ���� ����\n �ʿ��� �����̴�.");

	name.push_back("ī��Ű");
	explain.push_back("�����ֽ�ȸ�翡�� ����ϴ�\n ������ ī��Ű.");

	name.push_back("���������� Ű");
	explain.push_back("���ϴ� ����Ʈ�� ���������͸�\n �̿��Ҽ� �ִ� �����̴�.");



#pragma endregion

}

Keyitem::~Keyitem()
{
}
