#pragma once
#include "VoxelLib.h"

static enum CHUNKLAYOUT {
	NONE = 0,
	PYRAMID,
	GARDEN,
};

class ChunkLayout {
public:
	ChunkLayout()
	{
	}
	~ChunkLayout()
	{
	}

	int* Generate(CHUNKLAYOUT layout)
	{
		if (layout == CHUNKLAYOUT::NONE) {
			m_Layout = {
				0, 0, 0, 0,  0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0,
			};
			return m_Layout.data();
		}else if (layout == CHUNKLAYOUT::PYRAMID) {
			m_Layout = {
				1, 1, 1, 1,  1, 1, 1, 1,
				1, 2, 2, 2,  2, 2, 2, 1,
				1, 2, 3, 3,  3, 3, 2, 1,
				1, 2, 3, 4,  4, 3, 2, 1,

				1, 2, 3, 4,  4, 3, 2, 1,
				1, 2, 3, 3,  3, 3, 2, 1,
				1, 2, 2, 2,  2, 2, 2, 1,
				1, 1, 1, 1,  1, 1, 1, 1,
			};
			//m_Layout = pyramid;
			return m_Layout.data();
		}
		else if (layout == CHUNKLAYOUT::GARDEN) {
			m_Layout = {
				1, 1, 1, 1,  1, 1, 1, 1,
				1, 0, 0, 0,  0, 0, 0, 1,
				1, 0, 0, 0,  0, 0, 0, 1,
				1, 0, 0, 0,  0, 0, 0, 1,

				1, 0, 0, 0,  0, 0, 0, 1,
				1, 0, 0, 0,  0, 0, 0, 1,
				1, 0, 0, 0,  0, 0, 0, 1,
				1, 1, 1, 1,  1, 1, 1, 1,
			};
			return m_Layout.data();
		}

		return 0;
	};
private:
	std::array<int, 64> m_Layout;
};


