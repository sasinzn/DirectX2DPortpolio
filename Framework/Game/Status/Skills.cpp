#include "Framework.h"
#include "Skills.h"

Skill::Skill()
{
    Load("../_Resources/skills.csv");


}

Skill::~Skill()
{
}

void Skill::Load(string path)
{
    ifstream fin(path);

    if (fin.fail())
    {
        cout << "Wrong File" << endl;
        return;
    }


    char temp[256];
    int count = 0;

    // Hp Atk Def sAtk sDef Spd
    {
        for (int j = 0; j < 817; j++)
        {
            fin.getline(temp, 256);
            string t;
            int flag = 0;
            for (int i = 0; i < 256; i++)
            {
                if (temp[i] != ',' && temp[i] != '\0')
                    t += temp[i];
                else
                {
                    if (flag == 0)
                    {
                        data[count].ptype = ConvertTypePM(stoi(t));    // string to int
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 1)
                    {
                        skillname.push_back(t);
                        data[count].name = skillname[count];
                        t.clear();
                        ++flag;
                       
                    }
                    else if (flag == 2)
                    {
                        data[count].stype = ConvertSkillType(stoi(t));
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 3)
                    {
                        data[count].power = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 4)
                    {
                        data[count].accuracy = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 5)
                    {
                        data[count].pp = stoi(t);
                        t.clear();
                        ++flag;
                    }

                    continue;
                }
            }
            ++count;
        }

    } // End SkillLibrary
}

SkillType Skill::ConvertSkillType(int num)
{
    switch (num)
    {
    case 0:
        return PhysicsType;
        break;
    case 1:
        return SpecialType;
        break;
    case 2:
        return ChangeType;
        break;
    default:
        break;
    }
}

PmType Skill::ConvertTypePM(int num)
{
    switch (num)
    {
    case 1:
        return NormalType;
        break;
    case 2:
        return FireType;
        break;
    case 3:
        return WaterType;
        break;
    case 4:
        return LeafType;
        break;
    case 5:
        return ElectricType;
        break;
    case 6:
        return IceType;
        break;
    case 7:
        return FightingType;
        break;
    case 8:
        return PoisonType;
        break;
    case 9:
        return GroundType;
        break;
    case 10:
        return FlyingType;
        break;
    case 11:
        return PsychicType;
        break;
    case 12:
        return BugType;
        break;
    case 13:
        return RockType;
        break;
    case 14:
        return GhostType;
        break;
    case 15:
        return DragonType;
        break;
    case 16:
        return DarkType;
        break;
    case 17:
        return SteelType;
        break;
    case 18:
        return FairyType;
        break;
    }

    return TypeNull;
}

/*
TypeNull = 0,
NormalType,			//노멀 타입
FireType,			//불 타입
WaterType,			//물 타입
LeafType,			//풀 타입
ElectricType,		//전기 타입
IceType,			//얼음 타입
FightingType,		//격투 타입
PoisonType,			//독 타입
GroundType,			//땅 타입
FlyingType,			//비행 타입
PsychicType,		//에스퍼 타입
BugType,			//벌래 타입
RockType,			//바위 타입
GhostType,			//고스트 타입
DragonType,			//드래곤 타입
DarkType,			//악 타입
SteelType,			//강철 타입
FairyType,			//페어리 타입
*/
