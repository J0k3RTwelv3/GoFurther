#include "ClassicLevelWriter.h"

ClassicLevelWriter::ClassicLevelWriter(const std::filesystem::path outputLevelPath)
{
	m_totalLineCount = 0;
	m_foregroundLineCount = 0;
	m_backgroundLineCount = 0;
	m_writtenLineCountTracker = 0;

	m_levelFileStream = new std::ofstream(outputLevelPath);
	*m_levelFileStream << "0\n";
}

ClassicLevelWriter::~ClassicLevelWriter()
{
	if (m_levelFileStream->is_open())
	{
		m_levelFileStream->flush();
		m_levelFileStream->close();
	}

	delete m_levelFileStream;
}

void ClassicLevelWriter::WriteForegroundLineCount(unsigned int count)
{
	m_foregroundLineCount = count;

	*m_levelFileStream << std::to_string(m_foregroundLineCount) << "\n";

	m_totalLineCount = m_foregroundLineCount + m_backgroundLineCount;
}

void ClassicLevelWriter::WriteBackgroundLineCount(unsigned int count)
{
	m_backgroundLineCount = count;

	*m_levelFileStream << std::to_string(m_backgroundLineCount) << "\n";

	m_totalLineCount = m_foregroundLineCount + m_backgroundLineCount;
}

void ClassicLevelWriter::WriteLine(Line* line)
{
	if (m_writtenLineCountTracker >= m_totalLineCount)
	{
		throw std::length_error("Attempted to write too many lines.");
	}

	if (line->lineStyle->isRounded)
	{
		*m_levelFileStream << std::format("{0} {1} {2} {3} {4} {5}\n", line->closerLineEnd.x, line->lineStyle->color.x, line->lineStyle->color.y, line->lineStyle->color.z, line->lineStyle->thickness, line->lineStyle->thickness / 2);
	}
	else
	{
		*m_levelFileStream << std::format("{0} {1} {2} {3} {4}\n", line->closerLineEnd.x, line->lineStyle->color.x, line->lineStyle->color.y, line->lineStyle->color.z, line->lineStyle->thickness);
	}

	*m_levelFileStream << std::format("{0}\n{1}\n{2}\n", line->closerLineEnd.y, line->furtherLineEnd.x, line->furtherLineEnd.y);

	++m_writtenLineCountTracker;
}

void ClassicLevelWriter::Save()
{
	// Default values for the rest of things after line chunks.
	*m_levelFileStream
		<< "350.0\n"
		"50.0\n"
		"200.0\n"
		"194.0\n"
		"1\n"
		"1\n"
		"0\n"
		"0\n"
		"0\n"
		"0\n"
		"50.0\n"
		"50.0\n"
		"z 0\n"
		"c 0\n"
		"0\n"
		"0\n"
		"0\n"
		"0\n"
		"0\n"
		"v 1\n"
		"m 0 3\n\n"
		"f 1.000 1.000 1.000\n"
		"d9.4\n";

	m_levelFileStream->flush();
	m_levelFileStream->close();
}



