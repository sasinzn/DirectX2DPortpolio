#pragma once

#include "Game\Map\Map.h"

class SangrokCity : public Map
{
public:
	SangrokCity();
	~SangrokCity();

	void Update() override;
	void Render() override;

	bool MovingPMC(BoundingBox* player);

	Direction ChangeMap(Vector3 playerPos);

protected:
	ID3D11ShaderResourceView* srv = nullptr;
	Texture2D* srcTex = nullptr;

};
