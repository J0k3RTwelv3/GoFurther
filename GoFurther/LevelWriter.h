#pragma once

#include "Line.h"

class LevelWriter
{
public:
	virtual void WriteForegroundLineCount(unsigned int count) = 0;
	virtual void WriteBackgroundLineCount(unsigned int count) = 0;
	virtual void WriteLine(Line* line) = 0;
	virtual void Save() = 0;
};