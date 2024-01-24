#pragma once

#include "Game\Map\Map.h"

class TaechoTown : public Map
{
public:
	TaechoTown();
	~TaechoTown();
	
	void Update() override;
	void Render() override;

	
	
	Direction ChangeMap(Vector3 playerPos);

protected:
	ID3D11ShaderResourceView* srv = nullptr;
	Texture2D* srcTex = nullptr;
	
};
