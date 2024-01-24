#pragma once

#include "Game\Map\Map.h"

class PMCenter : public Map
{
public:
	PMCenter();
	~PMCenter();

	void Update() override;
	void Render() override;

	bool OutPmc(BoundingBox* player);

	Direction ChangeMap(Vector3 playerPos);

protected:
	ID3D11ShaderResourceView* srv = nullptr;
	Texture2D* srcTex = nullptr;

};
