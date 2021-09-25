#pragma once
#include <string>
#include "Logger.h"

bool isChar(char tmp);

bool isNormalKey(char key[32]);

bool isTypeKey(char key[32]);

void scanner(std::string contents);

void parser(std::string contents);