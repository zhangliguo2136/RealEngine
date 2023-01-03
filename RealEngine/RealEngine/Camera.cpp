#include "Camera.h"
#include "RealEngine.h"
#include "InputManager.h"

#include "REKey.h"

RealEngine::Camera::Camera() 
{
	_position = Vector3f(0.f, 0.f, 3.f);

	_front = Vector3f(0.0f, 0.0f, -1.0f);
	_up = Vector3f(0.0f, 1.0f, 0.0f);

	_lastCursorPosition = Vector2d(960, 540);
}

RealEngine::Camera::~Camera() 
{
}

void RealEngine::Camera::update(float deltaTime)
{
	float cameraSpeed = 0.05f;
	InputManager& pManager = InputManager::getInstance();
	if (pManager.isPressed(REKey::REKEY_KEY_W))
	{
		_position = _position + _front * cameraSpeed;
	}
	else if (pManager.isPressed(REKey::REKEY_KEY_S))
	{
		_position = _position - _front * cameraSpeed;
	}
	else if (pManager.isPressed(REKey::REKEY_KEY_A))
	{
		_position = _position - Vector3f::normalize(Vector3f::cross(_front, _up)) * cameraSpeed;
	}
	else if (pManager.isPressed(REKey::REKEY_KEY_D))
	{
		_position = _position + Vector3f::normalize(Vector3f::cross(_front, _up)) * cameraSpeed;
	}

	float sensitivity = 0.05f;
	auto cursorPosition = pManager.getCursorPosition();
	float xoffset = cursorPosition.x - _lastCursorPosition.x;
	float yoffset = _lastCursorPosition.y - cursorPosition.y;
	_lastCursorPosition = cursorPosition;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	Vector3f front;
	front.x = cos(Math::radians(yaw)) * cos(Math::radians(pitch));
	front.y = sin(Math::radians(pitch));
	front.z = sin(Math::radians(yaw)) * cos(Math::radians(pitch));
	_front = Vector3f::normalize(front);
}

Matrix4 RealEngine::Camera::lookAt(const Vector3f& position, const Vector3f&target, const Vector3f& worldUp) 
{
	Vector3f zaxis = Vector3f::normalize(target - position);
	Vector3f xaxis = Vector3f::normalize(Vector3f::cross(zaxis, worldUp));
	Vector3f yaxis = Vector3f::cross(xaxis, zaxis);

	Matrix4 mat = Matrix4::IdentityMatrix();
	float* result = mat.data();
	result[0] = xaxis.x;
	result[4] = xaxis.y;
	result[8] = xaxis.z;

	result[1] = yaxis.x;
	result[5] = yaxis.y;
	result[9] = yaxis.z;

	result[2] = -zaxis.x;
	result[6] = -zaxis.y;
	result[10] = -zaxis.z;

	result[12] = -Vector3f::dot(xaxis, position);
	result[13] = -Vector3f::dot(yaxis, position);
	result[14] = Vector3f::dot(zaxis, position);

	return mat;
}

Matrix4 RealEngine::Camera::getViewMatrix() 
{
	Matrix4 view = this->lookAt(_position, _position + _front, _up);
	return view;
}

Matrix4 RealEngine::Camera::getProjectionMatrix()
{
	EConfig config;
	float width = config.Width;
	float height = config.Height;

	Matrix4 projection = Matrix4::Perspective(Math::radians(45.f), width / height, 0.1f, 100.f);

	return projection;
}

Vector3f RealEngine::Camera::getViewPosition()
{
	return _position;
}