#include "LineStyleFactory.h"

LineStyleFactory::LineStyleFactory()
{
	m_lineStyles.clear();
}

LineStyleFactory::~LineStyleFactory()
{
}

LineStyle* LineStyleFactory::RequestLineStyle(Vector3 color, int thickness, bool isRounded, bool isBackgroundLine)
{
	LineStyle tmp = { color, thickness, isRounded, isBackgroundLine };

	for (const auto& lineStyle : m_lineStyles)
	{
		if (*lineStyle == tmp)
		{
			return lineStyle.get();
		}
	}

	m_lineStyles.emplace_back(std::move(new LineStyle{ color, thickness, isRounded, isBackgroundLine }));
	return m_lineStyles.back().get();
}
