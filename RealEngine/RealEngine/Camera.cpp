#include "Camera.h"
#include "RealEngine.h"

RealEngine::Camera::Camera() 
{
	_position = Vector3f(0.0f, 0.0f, 3.0f);
	_front = Vector3f(0.0f, 0.0f, -1.0f);
	_up = Vector3f(0.0f, 1.0f, 0.0f);
}

RealEngine::Camera::~Camera() 
{
}

Matrix4 RealEngine::Camera::lookAt(Vector3f& position, Vector3f&target, Vector3f& worldUp) 
{
	Vector3f temp1 = position - target;
	Vector3f zaxis = Vector3f::normalize(temp1);

	Vector3f normUp = Vector3f::normalize(worldUp);
	Vector3f temp2 = Vector3f::cross(normUp, zaxis);
	Vector3f xaxis = Vector3f::normalize(temp2);


	Vector3f yaxis = Vector3f::cross(zaxis, xaxis);

	Matrix4 mat1 = Matrix4::IdentityMatrix();
	float* translation = mat1.data();

	translation[3] = -position.x;
	translation[7] = -position.y;
	translation[11] = -position.z;

	Matrix4 mat2 = Matrix4::IdentityMatrix();
	float* rotation = mat2.data();

	rotation[0] = xaxis.x;
	rotation[1] = xaxis.y;
	rotation[2] = xaxis.z;

	rotation[4] = yaxis.x;
	rotation[5] = yaxis.y;
	rotation[6] = yaxis.z;

	rotation[8] = zaxis.x;
	rotation[9] = zaxis.y;
	rotation[10] = zaxis.z;

	return mat2 * mat1;
}

Matrix4 RealEngine::Camera::getViewMatrix() 
{
	Vector3f target = _position + _front;
	Matrix4 view = this->lookAt(_position, target, _up);

	return view;
}

Matrix4 RealEngine::Camera::getProjectionMatrix()
{
	EConfig config;
	float width = config.Width;
	float height = config.Height;

	Matrix4 projection = Matrix4::Perspective(45.f, (float)width / height, 0.1f, 100.f);

	return projection;
}

Vector3f RealEngine::Camera::getViewPosition()
{
	return _position;
}