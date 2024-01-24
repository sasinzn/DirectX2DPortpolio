#pragma once

#include "Game\Map\Map.h"


class Route01 : public Map
{
public:
	Route01();
	~Route01();

	void Update() override;
	void Render() override;



	Direction ChangeMap(Vector3 playerPos);
	bool Battle(BoundingBox* player, bool isBattle);

protected:
	ID3D11ShaderResourceView* srv = nullptr;
	Texture2D* srcTex = nullptr;
	
};
