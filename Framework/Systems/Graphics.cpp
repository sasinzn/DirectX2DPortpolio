#include "Framework.h"
#include "Graphics.h"


//����ü���� ���� �����ϰ�, ���� Ÿ�� ��� ����Ʈ�� ������Ʈ
void Graphics::Resize(const UINT & width, const UINT & height)
{

	//������ ������ RTV ����
	DeleteSurface();

	//���� ũ�� ����
	{
		HRESULT hr = swapChain->ResizeBuffers
		(
			0,									// �� ������ ��
			width,								// �� ������ �ʺ�
			height,								// �� ������ ����
			DXGI_FORMAT_UNKNOWN,				// �� ������ ����
			0									// �� ������ �Ӽ�
		);
		assert(SUCCEEDED(hr));					// �������� ������ ��� ���α׷� ����
	}
	CreateRenderTargetView();					// ���ο� �� ���ۿ� ���� RTV ����
	SetViewport(width, height);					// ����Ʈ�� ���ο� ũ�⿡ �°� ����

}

// ����Ʈ ����
void Graphics::SetViewport(const UINT & width, const UINT & height)
{
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}
void Graphics::InitViewport()
{
	deviceContext->RSSetViewports(1, &viewport);
}
// ������ ���� �� �ʿ��� �ʱ�ȭ �۾� ����
void Graphics::Begin()
{
	// ���� Ÿ�� ����
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
	// ����Ʈ ����
	deviceContext->RSSetViewports(1, &viewport);
	// RTV ����� ClearColor�� ������ ä��
	deviceContext->ClearRenderTargetView(rtv, clearColor);
}

// ������ ������ ȭ�鿡 ��� ���
void Graphics::End()
{

	// �� ���۸� ��� �ϰ� ȭ�� ���ſ� ���� ������� ���θ�  bVsync�� ����
	HRESULT hr = swapChain->Present(bVsync == true ?  1 : 0, 0);
	assert(SUCCEEDED(hr));
}

// GUI ����
void Graphics::GUI()
{
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ 0, 15 });
	ImGui::SetNextWindowSize(ImVec2(200, 30)); // ���� â ũ�� ����
	ImGui::Begin
	(
		"Vstnc", 
		&bOpen,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar
	);
	{
		ImGui::Checkbox("##Vsync", &bVsync);
	}
	ImGui::End();
}

// ����ü�� ����
void Graphics::CreateSwapchain()
{

	// ������ �Ҵ�� �޸� ����
	{
		SAFE_RELEASE(device);
		SAFE_RELEASE(deviceContext);
		SAFE_RELEASE(swapChain);
	}
		
	// ����ü�� ����ü �ʱ�ȭ
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// �ʺ�� ���� ����
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;

	// ��������ȭ�� ����� ��� ������ ����Ʈ ����
	{
		if (bVsync)
		{
			desc.BufferDesc.RefreshRate.Numerator = adapterInfos[0]->outputInfo->numerator;
			desc.BufferDesc.RefreshRate.Denominator = adapterInfos[0]->outputInfo->denominator;
		}
		else
		{
			desc.BufferDesc.RefreshRate.Numerator = 0;
			desc.BufferDesc.RefreshRate.Denominator = 1;
		}
	}
	
	// ������ ���Ӽ��� ���ؼ� ����
	{
		// ������ ���� ���� ����
		desc.BufferDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
		
		// �����ϸ��� ��ĵ���� ����
		desc.BufferDesc.Scaling				= DXGI_MODE_SCALING_UNSPECIFIED;
		desc.BufferDesc.ScanlineOrdering	= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		
		// ���� ü���� ���� ����, �뵵 , MSAA ǰ�� ����
		desc.BufferCount					= 1;
		desc.BufferUsage					= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count				= 1;
		desc.SampleDesc.Quality				= 0;
		
		// ��� â �ڵ�, â ���, ���� ü�� ȿ�� ����
		desc.OutputWindow					= handle;
		desc.Windowed						= true;
		desc.SwapEffect						= DXGI_SWAP_EFFECT_DISCARD;

	}
	

	
	// ��� ������ D3D ��� ������ ��Ÿ���� D3D_FEATURE_LEVEL �迭 ����
	vector<D3D_FEATURE_LEVEL> featureLevel
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};


	// ���� VRAM�� ū ��͸� �����Ͽ� selectedAdapterIndex�� �Ҵ�
	UINT maxVRam = 0;
	for (UINT i = 0; i < adapterInfos.size(); i++)
	{
		if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVRam)
		{
			selectedAdapterIndex = i;
			maxVRam = adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
		}
	}

	// CMD â ���
	{
		for (int i = 0; i < adapterInfos.size(); i++)
		{
			gpuName = adapterInfos[i]->adapterDesc.Description;
			wcout << "GPU Name : " << adapterInfos[i]->adapterDesc.Description << endl;
			cout << "VRAM : " << adapterInfos[i]->adapterDesc.DedicatedVideoMemory << endl;
			cout << endl;
		}

		wcout << "Selected GPU Name : "
			<< adapterInfos[selectedAdapterIndex]->
			adapterDesc.Description << endl;
	}

	
	// ����̽��� ����ü�� ����
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		adapterInfos[selectedAdapterIndex]->adapter,		// �ִ� VRAM �뷮�� ���� �׷��� ��ġ ����
		D3D_DRIVER_TYPE_UNKNOWN,							// ����̹� Ÿ�� ( �ڵ� )
		nullptr,											// ����Ʈ���� ������ ( ��� ���� )
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,					// ������ �� �ʿ��� �÷��� ����
		featureLevel.data(),								// ����� Direct3D ��� ����
		featureLevel.size(),								// ����� Direct3D ��� ������ ����
		D3D11_SDK_VERSION,									// Directx SDK ����
		&desc,												// ����ü���� ������ �� ����� ����ü
		&swapChain,											// ������ ����ü�� ��ü�� ��ȯ
		&device,											// ������ ����̽� ��ü�� ��ȯ
		nullptr,											// ������
		&deviceContext										// ������ ����̽� ���ý�Ʈ ��ü�� ��ȯ
	);
	assert(SUCCEEDED(hr));

	// ������ �缳��
	Resize(WinMaxWidth, WinMaxHeight);

	// cmdâ ���
	{
		for (int i = 0; i < adapterInfos.size(); i++)
		{
			gpuName = adapterInfos[i]->adapterDesc.Description;
			wcout << "GPU Name : " << adapterInfos[i]->adapterDesc.Description << endl;
			cout << "VRAM : " << adapterInfos[i]->adapterDesc.DedicatedVideoMemory << endl;
			cout << endl;
		}

		wcout << "Selected GPU Name : "
			<< adapterInfos[selectedAdapterIndex]->
			adapterDesc.Description << endl;

	}
}

// ����ü�ο��� �� ���۸� ������ RTV ����
void Graphics::CreateRenderTargetView()
{
	// �� ���� ��������
	ID3D11Texture2D* backbuffer = nullptr;
	HRESULT hr = swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backbuffer
	);
	assert(SUCCEEDED(hr));

	// �� ���۷� RTV ����
	hr = device->CreateRenderTargetView
	(
		backbuffer,
		nullptr,
		&rtv
	);
	assert(SUCCEEDED(hr));

	// �� ���� ����
	SAFE_RELEASE(backbuffer);
}
// RTV ����
void Graphics::DeleteSurface()
{
	SAFE_RELEASE(rtv);
}
// ����� ���� �� ����ü�� ����
Graphics::Graphics()
{
	EnumerateAdapters();
	CreateSwapchain();
}

// ������ �ڿ� ����
Graphics::~Graphics()
{
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}

// �׷��� ��͸� ã�� ���� ����
void Graphics::EnumerateAdapters()
{
	// DXGI ��ü�� �����ϴ� �Լ��� ������ �������̽�
	IDXGIFactory1* factory;
	// ���丮 ����
	if(FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
		return; //���н� ����

	UINT index = 0;
	while (true)
	{
		IDXGIAdapter1* adapter = nullptr;
		// ��� ����
		HRESULT hr = factory->EnumAdapters1(index, &adapter);
		
		// ���̻� ��Ͱ� ������ ����
		if (hr == DXGI_ERROR_NOT_FOUND)
			break;
		// ������ �����ϸ� ���α׷� ����
		assert(SUCCEEDED(hr));

		D3DEnumAdapterInfo* adapterInfo = new D3DEnumAdapterInfo();
		ZeroMemory(adapterInfo, sizeof(D3DEnumAdapterInfo));
		// ����� �ε��� ����
		adapterInfo->adapterOrdinal = index;
		// ����� ���� ����
		adapter->GetDesc1(&adapterInfo->adapterDesc);
		// ��� ���� ����
		adapterInfo->adapter = adapter;

		// ����� ��� ��ġ ����
		EnumerateAdapterOutput(adapterInfo);
		// ��� ���� ����
		adapterInfos.push_back(adapterInfo);

		// ���� ��ͷ� �̵�
		index++;
	}
	SAFE_RELEASE(factory);
}

// ��Ϳ��� �����ϴ� ��� ��带 �������� ����, ��� �󵵸� ����
bool Graphics::EnumerateAdapterOutput(D3DEnumAdapterInfo * adapterInfo)
{
	IDXGIOutput* output = nullptr;
	// ����� ��� ��ġ ����
	HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &output);


	// ��� ��ġ�� ������ �Լ� ����
	if (DXGI_ERROR_NOT_FOUND == hr)
		return false;
	// ������ �����ϸ� ���α׷� ����
	assert(SUCCEEDED(hr));

	D3DEnumOutputInfo* outputInfo = new D3DEnumOutputInfo();
	ZeroMemory(outputInfo, sizeof(D3DEnumOutputInfo));

	output->GetDesc(&outputInfo->outputDesc);			// �����ġ�� ���� ����
	outputInfo->output = output;						// �����ġ ��ü ����

	UINT numModes = 0;
	DXGI_MODE_DESC* displayModes = nullptr;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ��� ��ġ�� ���÷��� ��� ���� Ȯ��
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	assert(SUCCEEDED(hr));

	displayModes = new DXGI_MODE_DESC[numModes];

	// ��� ��ġ�� ���÷��� ��� ���� ����
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes);
	assert(SUCCEEDED(hr));

	for (UINT i = 0; i < numModes; i++)
	{
		bool bCheck = true;
		bCheck &= displayModes[i].Width == WinMaxWidth;			// ���÷��� ����� �ʺ� �ִ� �ʺ�� ������ Ȯ��
		bCheck &= displayModes[i].Height == WinMaxHeight;		// ���÷��� ����� ���̰� �ִ� ���̿� ������ Ȯ��

		if (bCheck == true)
		{
			// ���÷��� ����� �������� ���� ����
			outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
			outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
		}
	}

	// �����ġ ���� ����
	adapterInfo->outputInfo = outputInfo;
	SAFE_DELETE_ARRAY(displayModes);
	return true;
}

D3DEnumAdapterInfo::~D3DEnumAdapterInfo()
{
	SAFE_RELEASE(adapter);
	SAFE_DELETE(outputInfo);
}

D3DEnumOutputInfo::~D3DEnumOutputInfo()
{
	SAFE_RELEASE(output);
}



/*
Graphic Pipeline
- 3D �׷����� ��� ����� �����ϱ� ���� ���� �ܰ踦 ��ó ó���ϴ� ����
- CPU�� GPU�� �������� �̷������

01. IA (�Է� �����, Input Assembler)
- ���� ���ۿ� �ε��� ���۸� ����Ͽ� �⺻ ����(������Ƽ��)�� ����

02. VS (���� ���̴�, Vertex Shader)
- IA���� ������ ������Ƽ�꿡 ���� ���ؽ� �����͸� ó��
- ������ ���ؽ��� ���� ��ġ, �ؽ�ó ��ǥ, ��� ���� ���� ������ ������ �ִ�
- �̷��� ������ �������� ���̴��� �� ���ؽ��� ���� ��ġ�� ���

03. HS (�� ���̴�, Hull Shader)
- ���� ���� �ܰ� �� �ϳ���, ���� �� ǥ���� ȿ�������� ���� �ﰢ������ ������
- �� �Է� ��ġ (�簢��, �ﰢ�� �Ǵ� ��)�� �ش��ϴ� ���� ���� ��ġ (�� ��ġ ���)�� ����
-  �� ���̴��� ��ġ�� �� �� ȣ��Ǿ�, ���� ������ ǥ���� �����ϴ� �Է� �������� ��ġ�� �����ϴ� ���������� ��ȯ

04. TS (���ұ�, Tessellator)
- �׼����̼� �ܰ�� �ϵ����� �׼����̼��� ����
- �׷��� ������������ ���� ������ (���� �ٰ��� ��) ���� ���ϰ� �� ���� �����Ϸ� ������ �� �� �ִ�
- �� ���� ������ ǥ���� Direct3D �׷��� ���������� ������ �ڼ��� �������� ���� ���� �ﰢ������ ��ȯ�ϴ� �� �Բ� �۵�

05. DS (������ ���̴�, Domain Shader)
- ��� ��ġ�� ����ȭ�� ������ ������ ��ġ�� ���
- �׼����̼ǿ��� ������ ��ġ ������ �޾Ƽ�, ���� �����ϴ� ������ ����

06. GS (������Ʈ�� ���̴�, Geometry Shader)
- ������ ���̴����� ������ ���� ������ ������ �߰����� ��ȯ�� �����ϰų�, �������� ����� �������ϴ�.

07. SO (��Ʈ�� ���, Stream Output)
- ���� �����͸� ĸó�ϰ� �����մϴ�.

08. RS (�����Ͷ�����, Rasterizer)
- 3D �������� ���ǵ� 3D ���� 2D ȭ������ ��ȯ�ϴ� ����
- �� 3D �������� 2D �ȼ��� ��ȯ�ϰ�, �� �ȼ��� ���� ����(����, ���� ��)�� ����Ͽ� RTV�� ���

09. PS (�ȼ� ���̴�, Pixel Shader)
- ȭ�鿡 ��µǴ� �� �ȼ��� ���� ����(����, ���� ��)�� ���
- ���� ȭ�鿡�� �����ϴ� �ȼ��� ������ŭ �ȼ� ���̴��� ����
- ����, �׸���, ���� ���� ����Ͽ� ȭ�鿡 ���

10. OM (��� ���ձ�, Output Merger)
- �������� �ȼ��� ������ ���ۿ� �����մϴ�.
*/