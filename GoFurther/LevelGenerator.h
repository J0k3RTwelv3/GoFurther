#pragma once

#include <vector>
#include <memory>

#include "LevelWriter.h"
#include "LevelGenerationAlgorithm.h"

class LevelGenerator
{
public:
	LevelGenerator(LevelWriter* levelWriter, LevelGenerationAlgorithm* algorithm);
	~LevelGenerator();

	void Generate(unsigned int fgLines, unsigned int bgLines);
private:
	LevelWriter* m_levelWriter;
	LevelGenerationAlgorithm* m_algorithm;

	std::vector<std::unique_ptr<Line>> m_foregroundLines;
	std::vector<std::unique_ptr<Line>> m_backgroundLines;

};

