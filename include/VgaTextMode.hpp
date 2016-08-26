/*
 * =====================================================================================
 *
 *       Filename:  VgaTextMode.hpp
 *
 *    Description:  
 *
 *        Created:  24/08/2016 08:56:00
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef VGATEXTMODE_HPP_
#define VGATEXTMODE_HPP_

#include <stddef.h>
#include <stdint.h>

class VgaTextMode {
	public:
		VgaTextMode();
		
		void putEntryAt(char c, uint8_t color, size_t x, size_t y);
		void printChar(char c);
		void printString(const char *str);
		
		static const uint8_t width = 80;
		static const uint8_t height = 25;
		
		/* Hardware text mode color constants. */
		enum Color {
			Black			= 0,
			Blue			= 1,
			Green			= 2,
			Cyan			= 3,
			Red				= 4,
			Magenta			= 5,
			Brown			= 6,
			LightGrey		= 7,
			DarkGrey		= 8,
			LightBlue		= 9,
			LightGreen		= 10,
			LightCyan		= 11,
			LightRed		= 12,
			LightMagenta	= 13,
			LightBrown		= 14,
			White			= 15,
		};
		
	private:
		uint8_t makeColor(Color fg, Color bg);
		uint16_t makeVgaEntry(char c, uint8_t color);
		
		// Size in characters
		size_t m_row = 0;
		size_t m_column = 0;
		
		uint8_t m_color;
		uint16_t *m_buffer = (uint16_t *)0xB8000;
};

#endif // VGATEXTMODE_HPP_
