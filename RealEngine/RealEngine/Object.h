#pragma once
#include <string>
#include <vector>
#include <map>

enum ObjectType :int
{
	Value		= 1 << 1,
	Function	= 1 << 2,
	Class		= 1 << 3,
	Object		= 1 << 4,
};


// ͳһ���ͽӿ�
class TypeInterface
{
public:
	virtual ObjectType getType() = 0;
};

// ��ֵ����
class TValue :public TypeInterface
{
public:
	virtual ObjectType getType() override;

public:
	double value;
};

// ��������
class TFunction :public TypeInterface
{
public:
	virtual ObjectType getType() override;

public:
	std::string funcBody;

	std::vector<TypeInterface*> args;

	std::vector<TypeInterface*> upvalues;
};

class TObject;
// �����
class TClass :public TypeInterface
{
public:
	virtual ObjectType getType() override;

public:
	std::map<std::string, TValue> valueMaps;
	std::map<std::string, TFunction> funcMaps;
	std::map<std::string, TClass> classMaps;

public:
	TObject createTObject();
};

// �������
class TObject :public TypeInterface
{
public:
	virtual ObjectType getType() override;

public:
	std::map<std::string, TValue> valueMaps;
	std::map<std::string, TObject> objectMaps;
	std::map<std::string, TFunction> funcMaps;

	TValue getValue(std::string name);
	void setValue(std::string name, TValue value);

	TFunction getFunction(std::string name);
	void setFunction(std::string name, TFunction func);

public:
	TClass getClass();
	void setClass(TClass inClass);
private:
	TClass m_Class;
};

static TClass createTClass(std::string filepath);