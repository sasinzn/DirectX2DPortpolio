#pragma once

class Camera : public SingletonBase<Camera>
{
public:
	friend class SingletonBase<Camera>;

	void Update();
	void Render();

	void Move();
	void UpdateView();
	void CameraMove(Vector3 _position, float imageWidth, float imageHeight);
	void CameraPick(Vector3 _position);

	void UnProjection(Vector3* out, Vector3 source, Matrix world);

	const Vector3 GetPosition() { return position; };
private:
	Camera();
	~Camera();

	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;
	float cameraSpeed = 150.f;


};
