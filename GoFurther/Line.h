#pragma once

#include "LineStyle.h"

typedef struct Line
{
	Vector2 closerLineEnd;
	Vector2 furtherLineEnd;
	LineStyle* lineStyle;
} Line;