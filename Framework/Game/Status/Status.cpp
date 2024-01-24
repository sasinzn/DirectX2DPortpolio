#include "Framework.h"
#include "Status.h"

Status::Status(int indexNo, int level)
	:indexNo(indexNo), level(level)
{
	tribe = new PokeDex();
	tribeValue = tribe->GetTribe(indexNo);
	indexName = tribe->GetIndexName(indexNo);
	entityValue.hp = rand() % 31;
	entityValue.atk = rand() % 31;
	entityValue.def = rand() % 31;
	entityValue.sAtk = rand() % 31;
	entityValue.sDef = rand() % 31;
	entityValue.spd = rand() % 31;
/*
능력치 계산법

- HP
 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) + 100 } x 레벨Lv/100 ] + 10

- ATK, DEF, sATK, sDEF, SPD
 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) } x 레벨Lv/100 + 5 [10]] x 성격보정d
*/
	
	float perLevel = (float)this->level / 100.0;

	stat.hp		= ((tribeValue.hp	* 2)		+ entityValue.hp	+ (effortValue.hp	/ 4) + 100)	* perLevel + 10 + this->level;
	stat.atk	= ((tribeValue.atk	* 2)		+ entityValue.atk	+ (effortValue.atk	/ 4))		* perLevel + 5;
	stat.def	= ((tribeValue.def	* 2)		+ entityValue.def	+ (effortValue.def	/ 4))		* perLevel + 5;
	stat.sAtk	= ((tribeValue.sAtk	* 2)		+ entityValue.sAtk	+ (effortValue.sAtk / 4))		* perLevel + 5;
	stat.sDef	= ((tribeValue.sDef	* 2)		+ entityValue.sDef	+ (effortValue.sDef / 4))		* perLevel + 5;
	stat.spd	= ((tribeValue.spd	* 2)		+ entityValue.spd	+ (effortValue.spd	/ 4))		* perLevel + 5;

	cout << "LEVEL : " << level << endl;
	cout << "HP : " << stat.hp << endl;
	cout << "ATK : " << stat.atk << endl;
	cout << "DEF : " << stat.def << endl;
	cout << "SATK : " << stat.sAtk << endl;
	cout << "SDEF : " << stat.sDef << endl;
	cout << "SPD : " << stat.spd << endl;
}

Status::~Status()
{
	SAFE_DELETE(tribe);
}


void Status::LevelUp()
{
	this->level ++;

	float perLevel = (float)this->level / 100.0;

	stat.hp = ((tribeValue.hp * 2) + entityValue.hp + (effortValue.hp / 4) + 100) * perLevel + 10 + this->level;
	stat.atk = ((tribeValue.atk * 2) + entityValue.atk + (effortValue.atk / 4)) * perLevel + 5;
	stat.def = ((tribeValue.def * 2) + entityValue.def + (effortValue.def / 4)) * perLevel + 5;
	stat.sAtk = ((tribeValue.sAtk * 2) + entityValue.sAtk + (effortValue.sAtk / 4)) * perLevel + 5;
	stat.sDef = ((tribeValue.sDef * 2) + entityValue.sDef + (effortValue.sDef / 4)) * perLevel + 5;
	stat.spd = ((tribeValue.spd * 2) + entityValue.spd + (effortValue.spd / 4)) * perLevel + 5;
}



void Status::LevelUp(int level)
{
	this->level += level;

	float perLevel = (float)this->level / 100.0;

	stat.hp = ((tribeValue.hp * 2) + entityValue.hp + (effortValue.hp / 4) + 100) * perLevel + 10 + this->level;
	stat.atk = ((tribeValue.atk * 2) + entityValue.atk + (effortValue.atk / 4)) * perLevel + 5;
	stat.def = ((tribeValue.def * 2) + entityValue.def + (effortValue.def / 4)) * perLevel + 5;
	stat.sAtk = ((tribeValue.sAtk * 2) + entityValue.sAtk + (effortValue.sAtk / 4)) * perLevel + 5;
	stat.sDef = ((tribeValue.sDef * 2) + entityValue.sDef + (effortValue.sDef / 4)) * perLevel + 5;
	stat.spd = ((tribeValue.spd * 2) + entityValue.spd + (effortValue.spd / 4)) * perLevel + 5;
}

void Status::SetStatus(int indexNo, int level)
{
	tribeValue = tribe->GetTribe(indexNo);
	indexName = tribe->GetIndexName(indexNo);
	entityValue.hp = rand() % 31;
	entityValue.atk = rand() % 31;
	entityValue.def = rand() % 31;
	entityValue.sAtk = rand() % 31;
	entityValue.sDef = rand() % 31;
	entityValue.spd = rand() % 31;
	/*
	능력치 계산법

	- HP
	 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) + 100 } x 레벨Lv/100 ] + 10

	- ATK, DEF, sATK, sDEF, SPD
	 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) } x 레벨Lv/100 + 5 [10]] x 성격보정d
	*/

	float perLevel = (float)this->level / 100.0;

	stat.hp = ((tribeValue.hp * 2) + entityValue.hp + (effortValue.hp / 4) + 100) * perLevel + 10 + this->level;
	stat.atk = ((tribeValue.atk * 2) + entityValue.atk + (effortValue.atk / 4)) * perLevel + 5;
	stat.def = ((tribeValue.def * 2) + entityValue.def + (effortValue.def / 4)) * perLevel + 5;
	stat.sAtk = ((tribeValue.sAtk * 2) + entityValue.sAtk + (effortValue.sAtk / 4)) * perLevel + 5;
	stat.sDef = ((tribeValue.sDef * 2) + entityValue.sDef + (effortValue.sDef / 4)) * perLevel + 5;
	stat.spd = ((tribeValue.spd * 2) + entityValue.spd + (effortValue.spd / 4)) * perLevel + 5;

	cout << "LEVEL : " << level << endl;
	cout << "HP : " << stat.hp << endl;
	cout << "ATK : " << stat.atk << endl;
	cout << "DEF : " << stat.def << endl;
	cout << "SATK : " << stat.sAtk << endl;
	cout << "SDEF : " << stat.sDef << endl;
	cout << "SPD : " << stat.spd << endl;

}
