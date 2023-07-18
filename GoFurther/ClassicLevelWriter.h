#pragma once

#include <filesystem>
#include <fstream>

#include "LevelWriter.h"

class ClassicLevelWriter final : public LevelWriter
{
public:
	ClassicLevelWriter(const std::filesystem::path outputLevelPath);
	~ClassicLevelWriter();
	void WriteForegroundLineCount(unsigned int count) override;
	void WriteBackgroundLineCount(unsigned int count) override;
	void WriteLine(Line* line) override;
	void Save() override;
private:
	std::ofstream* m_levelFileStream;
	unsigned int m_totalLineCount;
	unsigned int m_foregroundLineCount;
	unsigned int m_backgroundLineCount;
	unsigned int m_writtenLineCountTracker;
};

