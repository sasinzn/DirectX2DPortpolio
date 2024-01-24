#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	: filePath(filePath)
{
	Textures::Load(this);
	
}

Texture2D::~Texture2D()
{

}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	texture->GetDesc(&srcDesc);

	D3D11_TEXTURE2D_DESC destDesc;
	Zero(destDesc);

	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srcDesc.Format;
	destDesc.SampleDesc = srcDesc.SampleDesc;
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);
	CHECK(hr);
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	int pixelNum = destDesc.Width * destDesc.Height;

	Color* colors = new Color[pixelNum];

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResource);
	{
		memcpy(colors, subResource.pData, sizeof(UINT) * pixelNum);
	}
	DC->Unmap(destTex, 0);

	UINT* red = new UINT[pixelNum];
	UINT* green = new UINT[pixelNum];
	UINT* blue = new UINT[pixelNum];
	UINT* alpha = new UINT[pixelNum];

	for (int i = 0; i < pixelNum; i++)
	{
		red[i] = (colors[i] & 0xFF000000);
		green[i] = (colors[i] & 0x00ff0000);
		blue[i] = (colors[i] & 0x0000ff00);
		alpha[i] = (colors[i] & 0x000000ff);

		red[i] = colors[i] >> 16;
		blue[i] = colors[i] << 16;

		// 모든 배열의 i번째 원소를 or 연산하여 colors 배열에 저장
		colors[i] = alpha[i] | red[i] | green[i] | blue[i];
	}

	// pixels 벡터에 colors 배열의 데이터를 할당
	pixels->assign(&colors[0], &colors[pixelNum-1]); // 배열 할당중 오류 발생
	
	
	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(destTex);
}


void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);

	
}

void Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// texture 객체의 filePath 속성에서 이미지 파일의 확장자를 얻어온다
	wstring ext = Path::GetExtension(texture->filePath);

	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	UINT width = metaData.width;
	UINT height = metaData.height;

	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	// 텍스처 중복 검사
	TextureDesc exist;
	bool bExist = false;

	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	// 이미 텍스처가 존재한다면 srv를 그걸로 설정해줌
	if (bExist == true)
	{
		texture->srv = exist.srv;
		texture->metaData = metaData;
	}
	else  
	{

		// 이미지 파일로부터 텍스처 데이터를 읽고 쓰기 위해서 사용
		ScratchImage image;

		// 확장자 검색 후 확장자에 맞는 함수를 호출하여 이미지 파일을 읽고 image 객체에 저장
		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		// image 객체로부터 셰이더 리소스 뷰를 생성하고 srv 포인터에 할당
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		SRV::Get()->AddSRV(String::ToString(texture->filePath.c_str()), srv);
		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
}
