/*
 * =====================================================================================
 *
 *       Filename:  VgaTextMode.cpp
 *
 *    Description:  
 *
 *        Created:  24/08/2016 08:58:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "VgaTextMode.hpp"

VgaTextMode::VgaTextMode() {
	m_color = makeColor(Color::LightGrey, Color::Black);
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			const size_t index = y * width + x;
			m_buffer[index] = makeVgaEntry(' ', m_color);
		}
	}
}

void VgaTextMode::putEntryAt(char c, uint8_t color, size_t x, size_t y) {
	m_buffer[x + y * width] = makeVgaEntry(c, color);
}

void VgaTextMode::printChar(char c) {
	putEntryAt(c, m_color, m_column, m_row);
	if (++m_column == width) {
		m_column = 0;
		if (++m_row == height) {
			m_row = 0;
		}
	}
}

void VgaTextMode::printString(const char *str) {
	while(*str) {
		printChar(*str);
		++str;
	}
}

uint8_t VgaTextMode::makeColor(Color fg, Color bg) {
	return fg | bg << 4;
}

uint16_t VgaTextMode::makeVgaEntry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

