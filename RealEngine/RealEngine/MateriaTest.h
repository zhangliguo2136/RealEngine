#pragma once
#include<memory>

#include "Image.h"
#include "Vector.h"

/*
��������ֵ�����߲�����ͼ
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

// ���ʶ���
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


// ���պ���
typedef float (AttenFunc)(float/*Intensity*/, float/*Distance*/);
// ���ն���
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
// �����
class OmnLight : public Light 
{
public:
	using Light::Light;
};
// ���
class SpotLight : public Light
{
protected:
	float m_fConeAngle;
	float m_fPenumbraAngle;
public:
	using Light::Light;
};