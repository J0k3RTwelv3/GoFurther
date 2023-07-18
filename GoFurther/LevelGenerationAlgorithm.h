#pragma once

#include "Line.h"

class LevelGenerationAlgorithm
{
public:
	virtual Line* GetNextLine() = 0;
};