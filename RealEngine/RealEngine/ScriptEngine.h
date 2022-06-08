#pragma once

#include "Parser.h"

class ScriptEngine
{
public:
	ScriptEngine();
	~ScriptEngine();

	static ScriptEngine& getInstance()
	{
		static ScriptEngine instance;
		return instance;
	}

	ScriptEngine(const ScriptEngine&) = delete;
	ScriptEngine& operator = (const ScriptEngine&) = delete;

public:
	void runScript(std::string file);
};