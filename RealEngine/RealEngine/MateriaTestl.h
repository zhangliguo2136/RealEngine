#pragma once
#include<memory>

#include "Image.h"
#include "Vector.h"

/*
材质属性值，或者材质贴图
*/
template<typename T>
struct ParameterMap 
{
	bool bUsingSingleValue = true;

	union _ParameterMap 
	{
		T value;
		std::shared_ptr<Image> map;
	};
};

typedef ParameterMap<Vector4f> Color;
typedef ParameterMap<Vector3f> Normal;
typedef ParameterMap<float> Parameter;

// 材质定义
class MaterialTest
{
protected:
	Color		m_baseColor;
	Parameter	m_Metallic;
	Parameter	m_Roughness;
	Normal		m_Normal;
	Parameter	m_Specular;
	Parameter	m_AmbientOcclusion;
};


// 光照函数
typedef float (AttenFunc)(float/*Intensity*/, float/*Distance*/);
// 光照定义
class LightTest
{
protected:
	Color		m_LightColor;
	float		m_Intensity;
	AttenFunc	m_LightAttenuation;
	float		m_fNearClipDistance;
	float		m_fFarClipDistance;
	bool		m_bCastShadows;
};
// 泛光灯
class OmnLight : public Light 
{
public:
	using Light::Light;
};
// 射灯
class SpotLight : public Light
{
protected:
	float m_fConeAngle;
	float m_fPenumbraAngle;
public:
	using Light::Light;
};