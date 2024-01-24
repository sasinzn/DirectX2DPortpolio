#pragma once

class RectGameDemo : public IObject
{
public:
public:
	virtual void Init()	override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class RectGame* pPlayer;
	vector<class RectGame*> rEnemy;
};
