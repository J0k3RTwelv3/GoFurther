#include "GroundLineGenerationAlgorithm.h"

constexpr double PI = 3.141592653589793238463;

GroundLineGenerationAlgorithm::GroundLineGenerationAlgorithm(Vector2 yValueRange, int groundThickness, Vector3 topLinesColor, Vector3 groundLinesColor)
{
	m_lastLineEnd = { 0.0, 0.0 };
	m_yValueRange = yValueRange;
	m_nextLineEnd = { -9999.0, -9999.0 };
	m_rightAngle = 0.0;
	m_topLinesColor = topLinesColor;
	m_groundLinesColor = groundLinesColor;
	m_groundThickness = groundThickness;
	m_lastGeneratedLine = { {0.0, 0.0}, {0.0, 0.0}, nullptr };
	m_getGroundLine = true;
	m_shouldExtendLeftEnd = false;
	m_shouldExtendRightEnd = false;

	InitializeRandomNumberGenerator();

	m_lineStyleFactory = new LineStyleFactory();
}

GroundLineGenerationAlgorithm::~GroundLineGenerationAlgorithm()
{
	delete m_randomNumberGenerator;
	delete m_lineStyleFactory;
}

Line* GroundLineGenerationAlgorithm::GetNextLine()
{
	Line* nextLine = new Line{ {0.0, 0.0}, {0.0, 0.0}, nullptr };

	if (m_getGroundLine)
	{
		std::uniform_real_distribution<double> xDistribution(25.0, 500.0);
		std::uniform_real_distribution<double> yDistribution(m_yValueRange.x * 0.5, m_yValueRange.y * 0.5);
		std::uniform_real_distribution<double> colorChannelDistribution(0.0, 1.0);

		m_lastGeneratedLine.closerLineEnd = m_lastLineEnd;

		m_lastGeneratedLine.furtherLineEnd.x = m_nextLineEnd.x != -9999.0 ? m_nextLineEnd.x : m_lastLineEnd.x + xDistribution(*m_randomNumberGenerator);
		m_lastGeneratedLine.furtherLineEnd.y = m_nextLineEnd.y != -9999.0 ? m_nextLineEnd.y : std::clamp<double>(m_lastLineEnd.y + yDistribution(*m_randomNumberGenerator), m_yValueRange.x, m_yValueRange.y);

		m_nextLineEnd.x = m_lastGeneratedLine.furtherLineEnd.x + xDistribution(*m_randomNumberGenerator);
		m_nextLineEnd.y = std::clamp<double>(m_lastGeneratedLine.furtherLineEnd.y + yDistribution(*m_randomNumberGenerator), m_yValueRange.x, m_yValueRange.y);

		m_lastLineEnd = m_lastGeneratedLine.furtherLineEnd;

		double currentLineAngle = std::atan2(m_lastGeneratedLine.furtherLineEnd.y - m_lastGeneratedLine.closerLineEnd.y, m_lastGeneratedLine.furtherLineEnd.x - m_lastGeneratedLine.closerLineEnd.x);
		double nextLineAngle = std::atan2(m_nextLineEnd.y - m_lastGeneratedLine.furtherLineEnd.y, m_nextLineEnd.x - m_lastGeneratedLine.furtherLineEnd.x);

		if (nextLineAngle < currentLineAngle)
		{
			m_shouldExtendRightEnd = true;
		}

		//m_lastGeneratedLine.color.x = colorChannelDistribution(*m_randomNumberGenerator);
		//m_lastGeneratedLine.color.y = colorChannelDistribution(*m_randomNumberGenerator);
		//m_lastGeneratedLine.color.z = colorChannelDistribution(*m_randomNumberGenerator);

		m_lastGeneratedLine.lineStyle = m_lineStyleFactory->RequestLineStyle(m_topLinesColor, 10, true, false);

		double diffrenceX = m_lastGeneratedLine.furtherLineEnd.x - m_lastGeneratedLine.closerLineEnd.x;
		double diffrenceY = m_lastGeneratedLine.furtherLineEnd.y - m_lastGeneratedLine.closerLineEnd.y;
		Vector2 lineNormal = { -diffrenceY, diffrenceX };
		NormalizeVector(&lineNormal);

		nextLine->lineStyle = m_lineStyleFactory->RequestLineStyle(m_groundLinesColor, m_groundThickness, false, true);

		nextLine->closerLineEnd.x = m_lastGeneratedLine.closerLineEnd.x + (lineNormal.x * (m_groundThickness / 2));
		nextLine->closerLineEnd.y = m_lastGeneratedLine.closerLineEnd.y + (lineNormal.y * (m_groundThickness / 2));
		nextLine->furtherLineEnd.x = m_lastGeneratedLine.furtherLineEnd.x + (lineNormal.x * (m_groundThickness / 2));
		nextLine->furtherLineEnd.y = m_lastGeneratedLine.furtherLineEnd.y + (lineNormal.y * (m_groundThickness / 2));
		
		Vector2 lineDiffrenceNormalized = { diffrenceX, diffrenceY };
		NormalizeVector(&lineDiffrenceNormalized);

		if (m_shouldExtendLeftEnd)
		{
			Vector2 lineDiffrenceNormalized = { diffrenceX, diffrenceY };
			NormalizeVector(&lineDiffrenceNormalized);

			nextLine->closerLineEnd.x += -lineDiffrenceNormalized.x * std::abs(m_rightAngle * m_groundThickness);
			nextLine->closerLineEnd.y += -lineDiffrenceNormalized.y * std::abs(m_rightAngle * m_groundThickness);

			m_shouldExtendLeftEnd = false;
		}
		if (m_shouldExtendRightEnd)
		{
			Vector2 lineDiffrenceNormalized = { diffrenceX, diffrenceY };
			NormalizeVector(&lineDiffrenceNormalized);

			nextLine->furtherLineEnd.x += lineDiffrenceNormalized.x * std::abs(currentLineAngle * m_groundThickness);
			nextLine->furtherLineEnd.y += lineDiffrenceNormalized.y * std::abs(currentLineAngle * m_groundThickness);

			m_rightAngle = nextLineAngle;
			m_shouldExtendLeftEnd = true;
			m_shouldExtendRightEnd = false;
		}

		//nextLine.color.x = colorChannelDistribution(*m_randomNumberGenerator);
		//nextLine.color.y = colorChannelDistribution(*m_randomNumberGenerator);
		//nextLine.color.z = colorChannelDistribution(*m_randomNumberGenerator);

		m_getGroundLine = false;
	}
	else
	{
		*nextLine = m_lastGeneratedLine;

		m_getGroundLine = true;
	}

	return nextLine;
}

void GroundLineGenerationAlgorithm::InitializeRandomNumberGenerator()
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

void GroundLineGenerationAlgorithm::NormalizeVector(Vector2* vector)
{
	double normalLength = std::sqrt(std::pow(vector->x, 2) + std::pow(vector->y, 2));
	vector->x /= normalLength;
	vector->y /= normalLength;
}

double GroundLineGenerationAlgorithm::ToDegrees(double radians)
{
	return radians * (180.0 / PI);
}
