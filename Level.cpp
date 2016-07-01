#include <fstream>
#include <Windows.h>
#include <stdlib.h>


#include "Level.h"



Level::Level():
	m_width(0), m_height(0)
{
	load();
}

void Level::load() {
	m_width = 20;
	m_height = 30;

	m_data.resize(m_height);
	std::vector <FT::FieldType> fullRow;
	fullRow.resize(m_width);
	for (int i = 0; i < m_width; i++) {
		fullRow.at(i) = FT::PlatformStone;
	}
	m_data.at(0) = fullRow;

	for (size_t i = 1; i < m_height; i++) {
		m_data.at(i) = generateNewRow(i);
	}
}

FT::FieldType Level::Field(size_t x, size_t y) {
	if (x >= m_width) {
		return FT::None;
	}
	if (y >= m_height) {
		m_height = y+1;
		m_data.resize(m_height);
		m_data.at(y) = generateNewRow(y);
	}
	if (y <= m_data.size())
	try {
		return m_data.at(y).at(x);
	}
	catch (std::out_of_range& ex) {
		return m_data.at(0).at(x);
	}
}

std::vector<FT::FieldType> Level::generateNewRow(size_t y) {
	std::vector <FT::FieldType> row;
	row.resize(m_width);
	if (y % 3 != 0) {
		
		for (int i = 0; i < m_width; i++) {
			row.at(i) = FT::None;
		}
	}
	else {
		if (y % 150 == 0) {
			std::vector <FT::FieldType> fullRow;
			fullRow.resize(m_width);
			for (int i = 0; i < m_width; i++) {
				fullRow.at(i) = FT::PlatformStone;
			}
			return fullRow;
		}
		else {
			int start = rand() % (m_width - 3);
			int end = start + 3 + rand() % 5;
			if (end >= m_width)
				end = m_width - 1;

			for (int i = 0; i < start; i++) {
				row.at(i) = FT::None;
			}
			row.at(start) = FT::PlatformRightEnd;
			for (int i = start + 1; i < end; i++) {
				row.at(i) = FT::PlatformMidPart;
			}
			row.at(end) = FT::PlatformLeftEnd;
			for (int i = end + 1; i < m_width; i++) {
				row.at(i) = FT::None;
			}
		}
	}
	return row;
}

Aabb Level::GetFieldAabb(size_t x, size_t y) const {
	Aabb box = Aabb(x, y, x + 1, y+1);
	return box;
}



