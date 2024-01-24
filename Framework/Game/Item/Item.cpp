#include "Framework.h"
#include "Item.h"

#include "PokeBall.h"
#include "HealingItem.h"
#include "KeyItem.h"
#include "Game/Actor/Pokemon.h"

Item::Item()
{

	balls = new PokeBall();
	healings = new HealingItem();
	keyitems = new Keyitem();

	for (int i = 0; i < 17; i++)
	{
		ballsNum[i] = i + 10;
	}

	for (int i = 0; i < 21 ; i++)
	{
		healingNum[i] = i + 1;
	}
}

Item::~Item()
{
	SAFE_DELETE(balls);

}

void Item::UseItems(int indexNo, Pokemon* pokemon)
{
	switch (indexNo)
	{
	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	case 4:

		break;

	case 5:

		break;

	case 6:
		pokemon->Healing(999);

		break;
	case 7:
		pokemon->Healing(999);
		break;

	case 8:
		pokemon->Healing(20);
		break;

	case 9:
		pokemon->Healing(120);

		break;

	case 10:
		pokemon->Healing(60);

		break;

	case 11:

		break;
	case 12:

		break;
	case 13:

		break;
	case 14:
		pokemon->Healing(30);
		break;
	case 15:
		pokemon->Healing(50);
		break;
	case 16:
		pokemon->Healing(70);
		break;
	case 17:

		break;
	case 18:

		break;
	case 19:

		break;
	case 20:

		break;
	case 21:
		pokemon->StrangeCandyEat();
		break;

	default:
		break;
	}


}
