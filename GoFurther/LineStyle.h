#pragma once

#include "Vectors.h"

typedef struct LineStyle
{
	Vector3 color;
	int thickness;
	bool isRounded;
	bool isBackgroundLine;

	bool operator==(const LineStyle& otherLine)
	{
		return (
				this->color.x == otherLine.color.x &&
				this->color.y == otherLine.color.y &&
				this->color.z == otherLine.color.z &&
				this->thickness == otherLine.thickness &&
				this->isRounded == otherLine.isRounded &&
				this->isBackgroundLine == otherLine.isBackgroundLine
			);
	}
} LineStyle;