#include "glmCamera.h"
#include "RealEngine.h"
#include "InputManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

RealEngine::glmCamera::glmCamera()
{
	_position = glm::vec3(0.f, 0.f, 3.f);

	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);

	_lastCursorPosition = Vector2d(960, 540);
}

RealEngine::glmCamera::~glmCamera()
{
}

void RealEngine::glmCamera::update(float deltaTime)
{
	float glmCameraSpeed = 0.05f;
	InputManager& pManager = InputManager::getInstance();
	if (pManager.isPressed(GLFW_KEY_W))
	{
		_position += _front * glmCameraSpeed;
	}
	else if (pManager.isPressed(GLFW_KEY_S))
	{
		_position -= _front * glmCameraSpeed;
	}
	else if (pManager.isPressed(GLFW_KEY_A))
	{
		_position -= glm::normalize(glm::cross(_front, _up)) * glmCameraSpeed;
	}
	else if (pManager.isPressed(GLFW_KEY_D))
	{
		_position += glm::normalize(glm::cross(_front, _up)) * glmCameraSpeed;
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

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front = glm::normalize(front);
}

Matrix4 RealEngine::glmCamera::lookAt(const Vector3f& position, const Vector3f&target, const Vector3f& worldUp)
{
	//Vector3f zaxis = Vector3f::normalize(target - position);
	//Vector3f xaxis = Vector3f::normalize(Vector3f::cross(zaxis, worldUp));
	//Vector3f yaxis = Vector3f::cross(xaxis, zaxis);

	//Matrix4 mat = Matrix4::IdentityMatrix();
	//float* result = mat.data();
	//result[0] = xaxis.x;
	//result[4] = xaxis.y;
	//result[8] = xaxis.z;

	//result[1] = yaxis.x;
	//result[5] = yaxis.y;
	//result[9] = yaxis.z;

	//result[2] = -zaxis.x;
	//result[6] = -zaxis.y;
	//result[10] = -zaxis.z;

	//result[12] = -Vector3f::dot(xaxis, position);
	//result[13] = -Vector3f::dot(yaxis, position);
	//result[14] = Vector3f::dot(zaxis, position);

	//return mat;


	Vector3f zaxis = Vector3f::normalize(position - target);
	Vector3f xaxis = Vector3f::normalize(Vector3f::cross(Vector3f::normalize(worldUp), zaxis));
	Vector3f yaxis = Vector3f::cross(zaxis, xaxis);

	Matrix4 mat1 = Matrix4::IdentityMatrix();
	float* rotation = mat1.data();
	rotation[0] = xaxis.x;
	rotation[1] = xaxis.y;
	rotation[2] = xaxis.z;

	rotation[4] = yaxis.x;
	rotation[5] = yaxis.y;
	rotation[6] = yaxis.z;

	rotation[8] = zaxis.x;
	rotation[9] = zaxis.y;
	rotation[10] = zaxis.z;

	Matrix4 mat2 = Matrix4::IdentityMatrix();
	float* translate = mat2.data();
	translate[3] = -position.x;
	translate[7] = -position.y;
	translate[11] = -position.z;

	return mat1 * mat2;
}

Matrix4 RealEngine::glmCamera::getViewMatrix()
{
	glm::mat4 glmView = glm::lookAt(_position, _position + _front, _up);
	auto _datas = glm::value_ptr(glmView);

	Matrix4 view;
	for (auto i = 0; i < 16; ++i)
	{
		auto datas = view.data();
		datas[i] = _datas[i];
	}

	return view;
}

Matrix4 RealEngine::glmCamera::getProjectionMatrix()
{
	EConfig config;
	float width = config.Width;
	float height = config.Height;

	//Matrix4 projection = Matrix4::Perspective(45.f, width / height, 0.1f, 100.f);

	glm::mat4 glmProjection = glm::perspective(glm::radians(45.f), width / height, 0.1f, 100.f);
	auto _datas = glm::value_ptr(glmProjection);

	Matrix4 projection;
	for (auto i = 0; i < 16; ++i)
	{
		auto datas = projection.data();
		datas[i] = _datas[i];
	}

	return projection;
}

Vector3f RealEngine::glmCamera::getViewPosition()
{
	Vector3f vec(_position.x, _position.y, _position.z);
	return vec;
}