#include "Framework.h"
#include "ShadedTexture.h"

ShadedTexture::ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	:TextureRect(position,size,rotation,path)
{
	sb = new ShadedBuffer();
}

ShadedTexture::~ShadedTexture()
{
	SAFE_DELETE(sb);
}

void ShadedTexture::Render()
{
	sb->SetPSBuffer(0);
	TextureRect::Render();
}

void ShadedTexture::GUI()
{
	ImGui::Begin("Shaded");
	{
		ImGui::RadioButton("Nomal", sb->GetselectionPtr(), 1);
		ImGui::RadioButton("AM", sb->GetselectionPtr(), 2);
		ImGui::RadioButton("Sepia", sb->GetselectionPtr(), 3);
		ImGui::RadioButton("Negative", sb->GetselectionPtr(), 4);
		ImGui::RadioButton("Psterize", sb->GetselectionPtr(), 5);

	}
	ImGui::End();
}
