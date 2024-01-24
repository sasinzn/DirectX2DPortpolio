#include "Framework.h"
#include "HealingItem.h"

#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"

HealingItem::HealingItem()
{
	Texture2D* srcTex = new Texture2D(TextureMapMenuPath + L"HealingItem.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	healingItemClip = new AnimationClip(L"healingItemClip", srcTex, 23, { 0,0 }, texSize);

#pragma region Item name explain 

	// 1. �ص���
	name.push_back("�ص���");
	explain.push_back("�������̽��� ��.\n ���ϸ� 1������ �����¸� ȸ���Ѵ�");

	name.push_back("ȭ��ġ����");
	explain.push_back("�������̽��� ��.\n ���ϸ� 1������ ȭ�� ���¸� ȸ���Ѵ�.");

	name.push_back("��������ġ����");
	explain.push_back("�������̽��� ��.\n ���ϸ� 1������ ���� ���¸� ȸ���Ѵ�.");

	name.push_back("����¾�");
	explain.push_back("�������̽��� ��.\n ���ϸ� 1������ ��� ���¸� ȸ���Ѵ�.");

	name.push_back("����ġ����");
	explain.push_back("�������̽��� ��.\n ���ϸ� 1������ ���� ���¸� ȸ���Ѵ�.");

	name.push_back("ȸ����");
	explain.push_back("�������̽��� ��ó��.\n ���ϸ� 1������ HP�� �����̻��� ��� ȸ���Ѵ�.");

	name.push_back("Ǯȸ����");
	explain.push_back("�������̽��� ��ó��.\n ���ϸ� 1������ HP�� ��� ȸ���Ѵ�.");

	name.push_back("��ó��");
	explain.push_back("�������̽��� ��ó��.\n ���ϸ� 1������ HP�� 20��ŭ ȸ���Ѵ�.");

	name.push_back("��޻�ó��");
	explain.push_back("�������̽��� ��ó��.\n ���ϸ� 1������ HP�� 120��ŭ ȸ���Ѵ�.");

	name.push_back("������ó��");
	explain.push_back("�������̽��� ��ó��.\n ���ϸ� 1������ HP�� 60��ŭ ȸ���Ѵ�.");

	name.push_back("������ġ��");
	explain.push_back("�������̽��� ��.\n ���ϸ� 1������ ���� �̻��� ��� ȸ���Ѵ�.");

	name.push_back("���������");
	explain.push_back("������ ���� ���ϸ� 1������\n �ǰ��ϰ� �ϰ� HP�� ���ݱ��� ȸ���Ѵ�.");

	name.push_back("����ǵ��");
	explain.push_back("������ ���� ���ϸ� 1������\n �ǰ��ϰ� �ϰ� HP�� ��� ȸ���Ѵ�.");

	name.push_back("���ִ¹�");
	explain.push_back("�̳׶��� ������ ��.\n ���ϸ� 1������ HP�� 30��ŭ ȸ���Ѵ�.");

	name.push_back("�̳׶����̴�");
	explain.push_back("���ϰ� �� ��� ���̴�.\n ���ϸ� 1������ HP�� 50��ŭ ȸ���Ѵ�.");

	name.push_back("�ĸ�����ũ");
	explain.push_back("�ſ� ������ �꽺.\n ���ϸ� 1������ HP�� 70��ŭ ȸ���Ѵ�.");

	name.push_back("PP���̵�");
	explain.push_back("���ϸ��� ����ϰ� �ִ�\n ��� �� �ϳ��� PP�� 10ȸ���Ѵ�.");

	name.push_back("PPȸ��");
	explain.push_back("���ϸ��� ����ϰ� �ִ�\n ��� �� �ϳ��� PP�� ��� ȸ���Ѵ�.");

	name.push_back("PP���̴�");
	explain.push_back("���ϸ��� ����ϰ� �ִ�\n ��� ����� PP�� 10ȸ���Ѵ�.");

	name.push_back("PP�ƽ�");
	explain.push_back("���ϸ��� ����ϰ� �ִ�\n ��� ����� PP�� ��� ȸ���Ѵ�.");

	name.push_back("�̻��ѻ���");
	explain.push_back("�������� ������ ����.\n ���̸� ���ϸ� 1������ ������ 1��ŭ �ö󰣴�.");

#pragma endregion

}

HealingItem::~HealingItem()
{
}

int HealingItem::HealingNum(int indexNo)
{
	/*
	x0000 - ������ ī�װ�
	1xxxx - ȸ��
	2xxxx - �����̻�
	3xxxx - �ɷ�ġ
	4xxxx - 
	5xxxx - 
	6xxxx - 
	7xxxx - 
	8xxxx - 
	9xxxx - 

	0x000 - �������������
	x1000 - �����̻�
	x2000 - HP
	x3000 - PP 1��
	x4000 - PP ��ü
	x5000 - LV
	x6000 - �����̻�&HP
	x7000 - ����&HP
	x8000 -
	x9000 -
	*/

	switch (indexNo)
	{
	case 1:
		return 11199; //ȸ��-�����̻�-�ص���
		break;

	case 2:
		return 11299; //ȸ��-�����̻�-ȭ��ġ����
		break;
	case 3:
		return 11399; //ȸ��-�����̻�-��������ġ����
		break;

	case 4:
		return 11499; //ȸ��-�����̻�-����¾�
		break;
	case 5:
		return 11599; //ȸ��-�����̻�-����ġ����
		break;

	case 6:
		return 16999; //ȸ��-�����̻�&HP-Ǯȸ����
		break;

	case 7:
		return 12999; //ȸ��-HP-ȸ����
		break;

	case 8:
		return 12020; //ȸ��-HP-��ó��
		break;

	case 9:
		return 12120; //ȸ��-HP-��޻�ó��
		break;

	case 10:
		return 12060; //ȸ��-HP-������ó��
		break;
	case 11:
		return 11699; //ȸ��-�����̻�-������ġ��
		break;

	case 12:
		return 17000; // ��������� ����ȸ�� �� 50%ȸ��
		break;
	case 13:
		return 17999; // ����ǵ�� ����ȸ�� �� Ǯȸ��
		break;

	case 14:
		return 12030;
		break;
	case 15:
		return 12050;
		break;

	case 16:
		return 12070;
		break;
	case 17:
		return 13010;
		break;

	case 18:
		return 13999;
		break;
	case 19:
		return 14010;
		break;

	case 20:
		return 14999;
		break;
	case 21:
		return 35001;
		break;
	
	}

	return 0;



}
