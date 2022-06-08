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


// TObject
//-----------------------------------------------------
ObjectType TObject::getType()
{
	return ObjectType::Object;
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