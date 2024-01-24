#include "Framework.h"
#include "PokeDex.h"


//엑셀에서 csv 파일로 저장 불러오기로 로드
PokeDex::PokeDex()
{
    //포켓몬 종족값,도감명 로드
    Load("../_Resources/pokedex.csv");

    //스프라이트 로드
#pragma region Pokemon Sprite Load 

    // 001 이상해씨 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"001Bulbasaur.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"001Bulbasaur.png"));
    frontAni[0] = new AnimationClip(L"이상해씨", frontSrcTex[0], 11, { 0,0 }, { frontSrcTex[0]->GetWidth() ,frontSrcTex[0]->GetHeight() });
    backAni[0] = new AnimationClip(L"이상해씨", backSrcTex[0], 12, { 0,0 }, { backSrcTex[0]->GetWidth() ,backSrcTex[0]->GetHeight() });

    // 002 이상해풀 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"002Ivysaur.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"002Ivysaur.png"));
    frontAni[1] = new AnimationClip(L"이상해풀", frontSrcTex[1], 30, { 0,0 }, { frontSrcTex[1]->GetWidth() ,frontSrcTex[1]->GetHeight() });
    backAni[1] = new AnimationClip(L"이상해풀", backSrcTex[1], 31, { 0,0 }, { backSrcTex[1]->GetWidth() ,backSrcTex[1]->GetHeight() });

    // 003 이상해꽃 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"003Venusaur.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"003Venusaur.png"));
    frontAni[2] = new AnimationClip(L"이상해꽃", frontSrcTex[2], 18, { 0,0 }, { frontSrcTex[2]->GetWidth() ,frontSrcTex[2]->GetHeight() });
    backAni[2] = new AnimationClip(L"이상해꽃", backSrcTex[2], 24, { 0,0 }, { backSrcTex[2]->GetWidth() ,backSrcTex[2]->GetHeight() });

    //004 파이리 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"004Charmander.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"004Charmander.png"));
    frontAni[3] = new AnimationClip(L"파이리", frontSrcTex[3], 27, { 0,0 }, { frontSrcTex[3]->GetWidth() ,frontSrcTex[3]->GetHeight() });
    backAni[3] = new AnimationClip(L"파이리", backSrcTex[3], 22, { 0,0 }, { backSrcTex[3]->GetWidth() ,backSrcTex[3]->GetHeight() });

    //005 리자드 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"005Charmeleon.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"005Charmeleon.png"));
    frontAni[4] = new AnimationClip(L"리자드", frontSrcTex[4], 46, { 0,0 }, { frontSrcTex[4]->GetWidth() ,frontSrcTex[4]->GetHeight() });
    backAni[4] = new AnimationClip(L"리자드", backSrcTex[4], 47, { 0,0 }, { backSrcTex[4]->GetWidth() ,backSrcTex[4]->GetHeight() });

    //006 리자몽 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"006Charizard.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"006Charizard.png"));
    frontAni[5] = new AnimationClip(L"리자몽", frontSrcTex[5], 18, { 0,0 }, { frontSrcTex[5]->GetWidth() ,frontSrcTex[5]->GetHeight() });
    backAni[5] = new AnimationClip(L"리자몽", backSrcTex[5], 18, { 0,0 }, { backSrcTex[5]->GetWidth() ,backSrcTex[5]->GetHeight() });

    //007 꼬부기 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"007Squirtle.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"007Squirtle.png"));
    frontAni[6] = new AnimationClip(L"꼬부기", frontSrcTex[6], 5, { 0,0 }, { frontSrcTex[6]->GetWidth() ,frontSrcTex[6]->GetHeight() });   
    backAni[6] = new AnimationClip(L"꼬부기", backSrcTex[6], 5, { 0,0 }, { backSrcTex[6]->GetWidth() ,backSrcTex[6]->GetHeight() });

    //008 어니부기 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"008Wartortle.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"008Wartortle.png"));
    frontAni[7] = new AnimationClip(L"어니부기", frontSrcTex[7], 9, { 0,0 }, { frontSrcTex[7]->GetWidth() ,frontSrcTex[7]->GetHeight() });
    backAni[7] = new AnimationClip(L"어니부기", backSrcTex[7], 10, { 0,0 }, { backSrcTex[7]->GetWidth() ,backSrcTex[7]->GetHeight() });

    //009 거북왕 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"009Blastoise.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"009Blastoise.png"));
    frontAni[8] = new AnimationClip(L"거북왕", frontSrcTex[8], 15, { 0,0 }, { frontSrcTex[8]->GetWidth() ,frontSrcTex[8]->GetHeight() });
    backAni[8] = new AnimationClip(L"거북왕", backSrcTex[8], 14, { 0,0 }, { backSrcTex[8]->GetWidth() ,backSrcTex[8]->GetHeight() });

    //010 캐터피 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"010Caterpie.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"010Caterpie.png"));
    frontAni[9] = new AnimationClip(L"캐터피", frontSrcTex[9], 8, { 0,0 }, { frontSrcTex[9]->GetWidth() ,frontSrcTex[9]->GetHeight() });
    backAni[9] = new AnimationClip(L"캐터피", backSrcTex[9], 8, { 0,0 }, { backSrcTex[9]->GetWidth() ,backSrcTex[9]->GetHeight() });

    //011 단데기 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"011Metapod.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"011Metapod.png"));
    frontAni[10] = new AnimationClip(L"단데기", frontSrcTex[10], 14, { 0,0 }, { frontSrcTex[10]->GetWidth() ,frontSrcTex[10]->GetHeight() });
    backAni[10] = new AnimationClip(L"단데기", backSrcTex[10], 14, { 0,0 }, { backSrcTex[10]->GetWidth() ,backSrcTex[10]->GetHeight() });

    //012 버터플 로드
    frontSrcTex.push_back(new Texture2D(TexturePmFrontPath + L"012Butterfree.png"));
    backSrcTex.push_back(new Texture2D(TexturePmBackPath + L"012Butterfree.png"));
    frontAni[11] = new AnimationClip(L"버터플", frontSrcTex[11], 30, { 0,0 }, { frontSrcTex[11]->GetWidth() ,frontSrcTex[11]->GetHeight() });
    backAni[11] = new AnimationClip(L"버터플", backSrcTex[11], 15, { 0,0 }, { backSrcTex[11]->GetWidth() ,backSrcTex[11]->GetHeight() });

#pragma endregion


  
   
}

PokeDex::~PokeDex()
{
    for (int i = 0; i < 12; i++)
    {
        SAFE_DELETE(frontAni[i]);
        SAFE_DELETE(backAni[i]);
    }

    for (Texture2D* r : frontSrcTex)
        SAFE_DELETE(r);

    for (Texture2D* r : backSrcTex)
        SAFE_DELETE(r);
}

void PokeDex::Load(string path)
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
        for (int j = 0; j < 26; j++)
        {
            fin.getline(temp, 256);
            string t;
            int flag = 0;
            for (int i = 0; i < 256; i++)
            {
                if (temp[i] != ',' && temp[i] != '\0')
                    t += temp[i];
                else if (temp[i] == '\0')
                    break;
                else
                {
                    if (flag == 0)
                    {
                        tribe[count].hp = stoi(t);    // string to int
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 1)
                    {
                        tribe[count].atk = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 2)
                    {
                        tribe[count].def = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 3)
                    {
                        tribe[count].sAtk = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 4)
                    {
                        tribe[count].sDef = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 5)
                    {
                        tribe[count].spd = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 6)
                    {
                        indexName.push_back(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 7)
                    {
                        PokemonType[count] = ConvertTypePM(stoi(t));
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 8)
                    {
                        if (stoi(t) == 1)
                            revolution[count] = true;
                        else
                            revolution[count] = false;

                        t.clear();
                        ++flag;
                    }
                    else if (flag == 9)
                    {
                        revolutionLevel[count] = stoi(t);
                        t.clear();
                        ++flag;
                    }
                    else if (flag == 10)
                    {
                        nextIndexNo[count] = stoi(t);
                        t.clear();
                        ++flag;
                    }

                    else if (flag > 11)
                    {
                        studySkills[count].skills.push_back(stoi(t));
                        t.clear();
                        ++flag;
                        
                    }
                    continue;
                }
            }
            ++count;
        }
        
    } // End pokedex data read

}


PmType PokeDex::ConvertTypePM(int num)
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