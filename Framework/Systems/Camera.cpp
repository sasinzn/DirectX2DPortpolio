#include "Framework.h"
#include "Camera.h"

void Camera::Update()
{
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move()
{
	auto key = Keyboard::Get();
	float delta = Time::Get()->Delta();

/*
if (key->Press(VK_UP))
		position.y += cameraSpeed * delta;

	else if (key->Press(VK_DOWN))
		position.y -= cameraSpeed * delta;

	if (key->Press(VK_LEFT))
		position.x -= cameraSpeed * delta;

	else if (key->Press(VK_RIGHT))
		position.x += cameraSpeed * delta;
*/
	

	UpdateView();
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH
	(
		&view,
		&position,
		&(position + Values::FwdVec),
		&Values::UpVec
	);

	vpb->SetView(view);

}
void Camera::CameraPick(Vector3 _position)
{
	
	position.x = _position.x - (WinMaxWidth / 2);
	position.y = _position.y - (WinMaxHeight / 2);

	UpdateView();

}

void Camera::CameraMove(Vector3 _position, float imageWidth, float imageHeight)
{
	position.x = _position.x - (WinMaxWidth / 2);
	position.y = _position.y - (WinMaxHeight / 2);

	if (position.x >= (imageWidth / 2 - WinMaxWidth / 2))
		position.x = imageWidth / 2 - WinMaxWidth / 2;
	if(position.x <= (WinMaxWidth / 2 - imageWidth / 2))
		position.x =  WinMaxWidth / 2 - imageWidth / 2;

	if (position.y >= (imageHeight / 2 - WinMaxHeight / 2))
		position.y = imageHeight / 2 - WinMaxHeight / 2;
	if (position.y <= (WinMaxHeight / 2 - imageHeight / 2))
		position.y = WinMaxHeight / 2 - imageHeight / 2;

	UpdateView();
}



void Camera::UnProjection(Vector3* out, Vector3 source, Matrix world) // ������� ����
{
	Vector3 position = source;

	out->x = (position.x * 2.f / WinMaxWidth) - 1.f;
	out->x = (position.y * 2.f / WinMaxHeight) - 1.f;
	out->z = position.z;

	Matrix wvp = world * view * proj;
	D3DXMatrixInverse(&wvp, nullptr, &wvp);
	D3DXVec3TransformCoord(out, out, &wvp);

}

Camera::Camera()
{
	vpb = new VPBuffer;

	// view ��� ����
	D3DXMatrixLookAtLH
	(
		&view,
		&Vector3(0, 0, 0),
		&Vector3(0, 0, 1),
		&Vector3(0, 1, 0)
	);

	// Projection ��� ����
	D3DXMatrixOrthoOffCenterLH
	(
		&proj,
		0.0f,							// ���� ���� ��ġ
		(float)WinMaxWidth,				// ������ ���� ��ġ
		0.0f,							// �Ʒ��� ���� ��ġ
		(float)WinMaxHeight,			// ���� ���� ��ġ
		0,								// ����� ��
		1								// �ָ� �ִ� ��
	);

	// ���� ����
	vpb->SetView(view);
	vpb->SetProj(proj);
}

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}
