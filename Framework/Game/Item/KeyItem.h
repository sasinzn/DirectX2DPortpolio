#pragma once

class Keyitem
{
public:
	Keyitem();
	~Keyitem();

	class AnimationClip* GetKeyitemClip() { return KeyitemClip; }
	string GetName(int indexNo) { return name[indexNo - 1]; }
	string GetExplan(int indexNo) { return explain[indexNo - 1]; }

private:
	class AnimationClip* KeyitemClip = nullptr;
	vector<string> name;
	vector<string> explain;


};