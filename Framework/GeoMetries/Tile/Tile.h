#pragma once

class Tile
{
public:
    Vector3 GetPosition() { return position; }
    void SetPosition(Vector3 position) { this->position = position; }

    Color GetColor() { return color; }
    void SetColor(Color color) { this->color = color; }

    Vector2 GetStartUV() { return startUV; }
    void SetStartUV(Vector2 startUV) { this->startUV = startUV; }

    Vector2 GetEndUV() { return endUV; }
    void SetEndUV(Vector2 endUV) { this->endUV = endUV; }

    ID3D11ShaderResourceView* GetSRV() { return srv; }
    void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

    uint GetIndex() { return index; }
    void SetIndex(uint index) { this->index = index; }

private:
    Vector3 position = Values::ZeroVec3;
    Color color = Values::Black;

    Vector2 startUV = Values::ZeroVec2;
    Vector2 endUV = Values::ZeroVec2;

    ID3D11ShaderResourceView* srv = nullptr;

    uint index = -1;
};