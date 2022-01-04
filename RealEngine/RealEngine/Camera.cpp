#include "Camera.h"
#include "RealEngine.h"
#include "InputManager.h"

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
	if (pManager.isPressed(GLFW_KEY_W))
	{
		_position = _position + _front * cameraSpeed;
	}
	else if (pManager.isPressed(GLFW_KEY_S))
	{
		_position = _position - _front * cameraSpeed;
	}
	else if (pManager.isPressed(GLFW_KEY_A))
	{
		_position = _position - Vector3f::normalize(Vector3f::cross(_front, _up)) * cameraSpeed;
	}
	else if (pManager.isPressed(GLFW_KEY_D))
	{
		_position = _position + Vector3f::normalize(Vector3f::cross(_front, _up)) * cameraSpeed;
	}

	//float sensitivity = 0.05f;
	//auto cursorPosition = pManager.getCursorPosition();
	//float xoffset = cursorPosition.x - _lastCursorPosition.x;
	//float yoffset = _lastCursorPosition.y - cursorPosition.y;
	//_lastCursorPosition = cursorPosition;

	//yaw += xoffset;
	//pitch += yoffset;

	//if (pitch > 89.0f)
	//	pitch = 89.0f;
	//if (pitch < -89.0f)
	//	pitch = -89.0f;

	//using namespace RealEngine::Math;
	//Vector3f front;
	//front.x = cos(radians(yaw)) * cos(radians(pitch));
	//front.y = sin(radians(pitch));
	//front.z = sin(radians(yaw)) * cos(radians(pitch));
	//_front = Vector3f::normalize(front);
}

Matrix4 RealEngine::Camera::lookAt(Vector3f& position, Vector3f&target, Vector3f& worldUp) 
{
	Vector3f zaxis = Vector3f::normalize(position - target);
	Vector3f xaxis = Vector3f::normalize(Vector3f::cross(Vector3f::normalize(worldUp), zaxis));
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