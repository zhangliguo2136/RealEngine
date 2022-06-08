#pragma once
#include <string>
#include <vector>
#include <map>
#include "Parser.h"


enum ObjectType :int
{
	Value		= 1 << 1,
	Function	= 1 << 2,
	Class		= 1 << 3,
	Object		= 1 << 4,
};

enum ValueType :int
{
	IntValue = 1 << 1,
	FloatValue = 1 << 2,
	DoubleValue = 1 << 3,
	BoolValue = 1 << 4,
	CharValue = 1 << 5,
	StringValue = 1 << 6,
};


// 统一类型接口
class TypeInterface
{
public:
	virtual ObjectType getType() = 0;
};

// 基础类型
class TValue :public TypeInterface
{
public:
	virtual ObjectType getType() override;

public:
	std::string name;
	
	ValueType _valueType;
	union _value
	{
		int i;
		float f;
		double d;
		char c;
	};
};

// 函数类型
class TFunction :public TypeInterface
{
public:
	virtual ObjectType getType() override;

public:
	std::string name;
	std::string funcBody;
	std::vector<TypeInterface*> args;
};

// 对象类型
class TObject :public TypeInterface
{
public:
	virtual ObjectType getType() override;

public:
	std::string name;

	std::map<std::string, TValue> valueMaps;
	std::map<std::string, TObject> objectMaps;
	std::map<std::string, TFunction> funcMaps;

	TValue getValue(std::string name);
	void setValue(std::string name, TValue value);

	TFunction getFunction(std::string name);
	void setFunction(std::string name, TFunction func);
};