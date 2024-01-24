#pragma once

class CollisionDemo : public IObject
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
	class Rect* r1;
	class Rect* r2;
	class Texture2D* map;
	class TextureRect* TaechoTown_01;
};
