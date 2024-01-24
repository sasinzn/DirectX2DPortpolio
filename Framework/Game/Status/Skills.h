#pragma once

class Skill
{
public:
	Skill();
	~Skill();

	void Load(string path);

	PmType ConvertTypePM(int num);
	SkillType ConvertSkillType(int num);
	SkillData* GetSkillData(int skillindex) { return &data[skillindex]; }

private:
	SkillData data[817];
	vector<string>skillname;


};