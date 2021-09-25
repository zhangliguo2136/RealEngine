#include "Object.h"

// TValue
//-----------------------------------------------------
ObjectType TValue::getType()
{
	return ObjectType::Value;
}
//-----------------------------------------------------

// TFunction
//-----------------------------------------------------
ObjectType TFunction::getType()
{
	return ObjectType::Function;
}
//-----------------------------------------------------

// TClass
//-----------------------------------------------------
ObjectType TClass::getType()
{
	return ObjectType::Class;
}

TObject TClass::createTObject()
{
	TObject outObject;

	// copy value
	for (auto& pair : valueMaps)
	{
		outObject.valueMaps[pair.first] = pair.second;
	}

	// copy func
	for (auto& pair : funcMaps)
	{
		outObject.funcMaps[pair.first] = pair.second;
	}

	// copy class object
	for (auto& pair : classMaps)
	{
		outObject.objectMaps[pair.first] = pair.second.createTObject();
	}

	return outObject;
}
//-----------------------------------------------------

// TObject
//-----------------------------------------------------
ObjectType TObject::getType()
{
	return ObjectType::Object;
}

TClass TObject::getClass()
{
	return m_Class;
}

void TObject::setClass(TClass inClass)
{
	m_Class = inClass;
}

TValue TObject::getValue(std::string name)
{
	return valueMaps[name];
}
void TObject::setValue(std::string name, TValue value)
{
	valueMaps[name] = value;
}

TFunction TObject::getFunction(std::string name) 
{
	return funcMaps[name];
}
void TObject::setFunction(std::string name, TFunction func) 
{
	funcMaps[name] = func;
}
//-----------------------------------------------------

static TClass createTClass(std::string filepath)
{
	std::string content = "Class TestClass = {TValue value1;TValue value2 = 100;TFunction func(TValue inValue);} TestClass:func(TValue inValue){print(inValue);}";
}