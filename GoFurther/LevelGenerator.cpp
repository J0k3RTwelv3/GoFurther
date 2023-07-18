#include "LevelGenerator.h"

LevelGenerator::LevelGenerator(LevelWriter* levelWriter, LevelGenerationAlgorithm* algorithm)
{
	m_levelWriter = levelWriter;
	m_algorithm = algorithm;
}

LevelGenerator::~LevelGenerator()
{
	delete m_levelWriter;
	delete m_algorithm;
}

void LevelGenerator::Generate(unsigned int fgLines, unsigned int bgLines)
{
	m_levelWriter->WriteForegroundLineCount(fgLines);
	m_levelWriter->WriteBackgroundLineCount(bgLines);

	for (unsigned int i = 0; i < fgLines + bgLines; ++i)
	{
		std::unique_ptr<Line> nextLine = std::unique_ptr<Line>(m_algorithm->GetNextLine());
		if (nextLine->lineStyle->isBackgroundLine)
		{
			m_backgroundLines.emplace_back(std::move(nextLine));
		}
		else
		{
			m_foregroundLines.emplace_back(std::move(nextLine));
		}
	}

	for (const auto& line : m_foregroundLines)
	{
		m_levelWriter->WriteLine(line.get());
	}

	for (const auto& line : m_backgroundLines)
	{
		m_levelWriter->WriteLine(line.get());
	}

	m_levelWriter->Save();
}
