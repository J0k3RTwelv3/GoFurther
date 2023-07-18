#pragma once

#include "Line.h"

#include <vector>
#include <memory>

class LineStyleFactory
{
public:
	LineStyleFactory();
	~LineStyleFactory();
	
	LineStyle* RequestLineStyle(Vector3 color, int thickness, bool isRounded, bool isBackgroundLine);

private:
	std::vector<std::unique_ptr<LineStyle>> m_lineStyles;
};

