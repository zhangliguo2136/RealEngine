#include "ScriptEngine.h"
#include "FileUtil.h"

ScriptEngine::ScriptEngine() 
{
}

ScriptEngine::~ScriptEngine() 
{
}

void ScriptEngine::runScript(std::string headFile)
{
	std::string fileContent = getFileContents(headFile);

	std::string s = "if (1000 > 0){ print(1000) }";

	exec(Statement(s));
}