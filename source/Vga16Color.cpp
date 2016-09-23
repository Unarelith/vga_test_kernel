/*
 * =====================================================================================
 *
 *       Filename:  Vga16Color.cpp
 *
 *    Description:  
 *
 *        Created:  26/08/2016 11:17:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <stddef.h>

#include "asm.hpp"
#include "font_data.hpp"
#include "Vga16Color.hpp"

Vga16Color::Vga16Color() {
	asm_out<uint8_t>(0x3c2, 0x67); // Miscellaneous Output Register
	
	setupPalette();
	setupAttributeControllerRegs();
	setupCrtControllerRegs();
	setupSequencerRegs();
	setupGraphicsControllerRegs();
}

void Vga16Color::setupAttributeControllerRegs() {
	write_vga_reg(0x3c0, 0x10, 0x01); // Mode Control
	write_vga_reg(0x3c0, 0x11, 0x00); // Overscan Register
	write_vga_reg(0x3c0, 0x12, 0x0f); // Color Plane Enable
	write_vga_reg(0x3c0, 0x13, 0x00); // Horizontal Panning
	write_vga_reg(0x3c0, 0x14, 0x00); // Color Select
	asm_out<uint8_t>(0x3c0, 0x20);
}

void Vga16Color::setupCrtControllerRegs() {
	write_vga_reg(0x3d4, 0x00, 0x5f); // Horizontal Total
	write_vga_reg(0x3d4, 0x01, 0x4f); // Horizontal Display Enable End
	write_vga_reg(0x3d4, 0x02, 0x50); // Horizontal Blank Start
	write_vga_reg(0x3d4, 0x03, 0x82); // Horizontal Blank End
	write_vga_reg(0x3d4, 0x04, 0x54); // Horizontal Retrace Start
	write_vga_reg(0x3d4, 0x05, 0x80); // Horizontal Retrace End
	write_vga_reg(0x3d4, 0x06, 0x0b); // Vertical Total
	write_vga_reg(0x3d4, 0x07, 0x3e); // Overflow Register
	write_vga_reg(0x3d4, 0x08, 0x00); // Preset row scan
	write_vga_reg(0x3d4, 0x09, 0x40); // Maximum Scan Line
	write_vga_reg(0x3d4, 0x0a, 0x00); // Cursor start
	write_vga_reg(0x3d4, 0x0b, 0x00); // Cursor end
	write_vga_reg(0x3d4, 0x0c, 0x00); // Start Address High
	write_vga_reg(0x3d4, 0x0d, 0x00); // Start Address Low
	write_vga_reg(0x3d4, 0x0e, 0x00); // Cursor Location High
	write_vga_reg(0x3d4, 0x0f, 0x00); // Cursor Location Low
	write_vga_reg(0x3d4, 0x10, 0xea); // Vertical Retrace Start
	write_vga_reg(0x3d4, 0x11, 0x8c); // Vertical Retrace End
	write_vga_reg(0x3d4, 0x12, 0xdf); // Vertical Display Enable End
	write_vga_reg(0x3d4, 0x13, 0x28); // Logical Width
	write_vga_reg(0x3d4, 0x14, 0x00); // Underline Location
	write_vga_reg(0x3d4, 0x15, 0xe7); // Vertical Blank Start
	write_vga_reg(0x3d4, 0x16, 0x04); // Vertical Blank End
	write_vga_reg(0x3d4, 0x17, 0xe3); // Mode Control
	write_vga_reg(0x3d4, 0x18, 0xff); // Line compare
}

void Vga16Color::setupSequencerRegs() {
	write_vga_reg(0x3c4, 0x00, 0x00); // Reset
	write_vga_reg(0x3c4, 0x01, 0x01); // Clock Mode Register
	write_vga_reg(0x3c4, 0x02, 0x0f); // Map mask Register
	write_vga_reg(0x3c4, 0x03, 0x00); // Character select
	write_vga_reg(0x3c4, 0x04, 0x06); // Memory Mode Register
}

void Vga16Color::setupGraphicsControllerRegs() {
	write_vga_reg(0x3ce, 0x00, 0x00); // Set/Reset
	write_vga_reg(0x3ce, 0x01, 0x00); // Enable Set/Reset
	write_vga_reg(0x3ce, 0x02, 0x00); // Color compare
	write_vga_reg(0x3ce, 0x03, 0x00); // Function select
	write_vga_reg(0x3ce, 0x04, 0x00); // Read map select
	write_vga_reg(0x3ce, 0x05, 0x0a); // Mode Register
	write_vga_reg(0x3ce, 0x06, 0x05); // Miscellaneous Register
	write_vga_reg(0x3ce, 0x07, 0x0f); // Color Don't Care
	write_vga_reg(0x3ce, 0x08, 0xff); // Bitmask
}

void Vga16Color::setupPalette() {
	write_vga_reg(0x3c4, 0x07, 0x00);
	
	asm_out<uint8_t>(0x3c6, 0xff);
	
	for(uint32_t i = 0 ; i <= 0x3f ; i++) {
		setColor(i, (i << 16) | (i << 8) | i);
	}
	
	asm_in<uint8_t>(0x3da);
	
	for(uint8_t j = 0 ; j <= 0xf ; j++) {
		write_vga_reg(0x3c0, j, j * 8);
	}
}

void Vga16Color::setColor(uint8_t paletteIndex, uint32_t color) {
	uint16_t r = (color & 0xff0000) >> 16;
	uint16_t g = (color & 0x00ff00) >> 8;
	uint16_t b = color & 0x0000ff;
	
	asm_out<uint8_t>(0x3c8, paletteIndex);
	
	asm_out<uint8_t>(0x3c9, r); // * 0x3f / 0xff);
	asm_out<uint8_t>(0x3c9, g); // * 0x3f / 0xff);
	asm_out<uint8_t>(0x3c9, b); // * 0x3f / 0xff);
}

void Vga16Color::clearScreen() {
	for(uint16_t y = 0 ; y < height ; y++)
		for(uint16_t x = 0 ; x < width ; x++)
			putPixel(x, y, 0x0);
}

void Vga16Color::putPixel(uint16_t x, uint16_t y, uint8_t paletteIndex) {
	write_vga_reg(0x3ce, 0x02, 0x0f); // Color compare
	write_vga_reg(0x3ce, 0x07, 0x00); // Color Don't Care
	
	write_vga_reg(0x3ce, 0x08, 1 << (7 - (x % 8))); // Bitmask
	
	volatile uint8_t tmp = m_buffer[x / 8 + y * width / 8]; (void)tmp;
	m_buffer[x / 8 + y * width / 8] = paletteIndex;
}

void Vga16Color::drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t paletteIndex) {
	for(uint16_t j = y ; j < y + height ; j++) {
		for(uint16_t i = x ; i < x + width ; i++) {
			putPixel(i, j, paletteIndex);
		}
	}
}

void Vga16Color::printChar(uint16_t x, uint16_t y, char letter, uint8_t paletteIndex) {
	int c = letter * 8;
	if(c > 255 * 8) {
		c = 63;
	}
	
	for(uint8_t i = 0 ; i < 8 ; i++) {
		int k = lcdFontData[c + i];
		for(uint8_t j = 0 ; j < 8 ; j++) {
			if(k & 1) {
				putPixel(x + j, y + i, paletteIndex);
			}
			
			k >>= 1;
		}
	}
}

void Vga16Color::printString(uint16_t x, uint16_t y, const char *str, uint8_t paletteIndex) {
	uint16_t origX = x;
	
	for(size_t i = 0 ; str[i] ; i++) {
		if(str[i] == '\n') {
			y += lcdFontCharHeight + 2;
			x = origX;
			continue;
		}
		
		printChar(x, y, str[i], paletteIndex);
		
		x += lcdFontCharWidth;
	}
}

