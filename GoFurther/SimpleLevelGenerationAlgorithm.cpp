#include "SimpleLevelGenerationAlgorithm.h"

/*

This is a very simple level generation algorithm.

It picks a random y point based on previous line y end in some range
and then extends next line by a random x value.

This can be used as a reference on how to implement
custom level generation algorithms.

*/

SimpleLevelGenerationAlgorithm::SimpleLevelGenerationAlgorithm(Vector2 yValueRange)
{
	m_lastLineEnd = { 0.0, 0.0 };
	m_yValueRange = yValueRange;
	InitializeRandomNumberGenerator();
}

SimpleLevelGenerationAlgorithm::~SimpleLevelGenerationAlgorithm()
{
	delete m_randomNumberGenerator;
}

Line* SimpleLevelGenerationAlgorithm::GetNextLine()
{
	Line* nextLine = new Line{ {0.0, 0.0}, {0.0, 0.0}, nullptr };

	std::uniform_real_distribution<double> xDistribution(25.0, 500.0);
	std::uniform_real_distribution<double> yDistribution(m_yValueRange.x * 0.5, m_yValueRange.y * 0.5);
	std::uniform_real_distribution<double> colorChannelDistribution(0.0, 1.0);

	nextLine->closerLineEnd = m_lastLineEnd;

	nextLine->furtherLineEnd.x = m_lastLineEnd.x + xDistribution(*m_randomNumberGenerator);
	nextLine->furtherLineEnd.y = std::clamp<double>(m_lastLineEnd.y + yDistribution(*m_randomNumberGenerator), m_yValueRange.x, m_yValueRange.y);
	
	m_lastLineEnd = nextLine->furtherLineEnd;

	nextLine->lineStyle->color.x = colorChannelDistribution(*m_randomNumberGenerator);
	nextLine->lineStyle->color.y = colorChannelDistribution(*m_randomNumberGenerator);
	nextLine->lineStyle->color.z = colorChannelDistribution(*m_randomNumberGenerator);

	return nextLine;

}

void SimpleLevelGenerationAlgorithm::InitializeRandomNumberGenerator()
{
	std::random_device randomDevice;
	unsigned int randomData[10];

	for (auto& n : randomData)
	{
		n = randomDevice();
	}

	std::seed_seq seed{ randomData + 0, randomData + 10 };

	m_randomNumberGenerator = new std::default_random_engine(seed);
}
