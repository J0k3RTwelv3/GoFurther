#pragma once

#include <random>

#include "LevelGenerationAlgorithm.h"
#include "LineStyleFactory.h"

class GroundLineGenerationAlgorithm final : public LevelGenerationAlgorithm
{
public:
	GroundLineGenerationAlgorithm(Vector2 yValueRange, int groundThickness, Vector3 topLinesColor, Vector3 groundLinesColor);
	~GroundLineGenerationAlgorithm();
	Line* GetNextLine() override;
private:
	Vector2 m_lastLineEnd;
	Vector2 m_yValueRange;
	Vector2 m_nextLineEnd;
	Vector3 m_topLinesColor;
	Vector3 m_groundLinesColor;
	double m_rightAngle;
	int m_groundThickness;
	Line m_lastGeneratedLine;
	bool m_getGroundLine;
	bool m_shouldExtendLeftEnd;
	bool m_shouldExtendRightEnd;

	std::default_random_engine* m_randomNumberGenerator;
	LineStyleFactory* m_lineStyleFactory;

	void InitializeRandomNumberGenerator();
	void NormalizeVector(Vector2* vector);
	double ToDegrees(double radians);
};

