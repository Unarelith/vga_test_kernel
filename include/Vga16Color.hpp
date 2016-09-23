/*
 * =====================================================================================
 *
 *       Filename:  Vga16Color.hpp
 *
 *    Description:  
 *
 *        Created:  26/08/2016 11:16:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef VGA16COLOR_HPP_
#define VGA16COLOR_HPP_

#include <stdint.h>

class Vga16Color {
	public:
		Vga16Color();
		
		void setupAttributeControllerRegs();
		void setupCrtControllerRegs();
		void setupSequencerRegs();
		void setupGraphicsControllerRegs();
		
		void setupPalette();
		void setColor(uint8_t paletteIndex, uint32_t color);
		
		void clearScreen();
		
		void putPixel(uint16_t x, uint16_t y, uint8_t paletteIndex);
		void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t paletteIndex);
		
		void printChar(uint16_t x, uint16_t y, char letter, uint8_t paletteIndex);
		void printString(uint16_t x, uint16_t y, const char *str, uint8_t paletteIndex);
		
		static const uint16_t width = 640;
		static const uint16_t height = 480;
		
	private:
		uint8_t *m_buffer = (uint8_t *)0xA0000;
};

#endif // VGA16COLOR_HPP_
