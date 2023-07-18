#pragma once

#include <random>
#include <math.h>

#include "LevelGenerationAlgorithm.h"

class SimpleLevelGenerationAlgorithm final : public LevelGenerationAlgorithm
{
public:
	SimpleLevelGenerationAlgorithm(Vector2 yValueRange);
	~SimpleLevelGenerationAlgorithm();
	Line* GetNextLine() override;
private:
	Vector2 m_lastLineEnd;
	Vector2 m_yValueRange;
	
	std::default_random_engine* m_randomNumberGenerator;

	void InitializeRandomNumberGenerator();
};

