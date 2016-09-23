/*
 * =====================================================================================
 *
 *       Filename:  asm.cpp
 *
 *    Description:  
 *
 *        Created:  26/08/2016 10:59:32
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "asm.hpp"

void write_vga_reg(uint16_t port, uint8_t index, uint8_t val) {
	if(port != 0x3c0) {
		asm_out<uint16_t>(port, val << 8 | index);
	} else {
		asm_out<uint8_t>(port, index);
		asm_out<uint8_t>(port, val);
	}
}

template<typename T>
void asm_out(uint16_t port, T val) {
	asm volatile("out %1, %0" : : "a"(val), "Nd"(port));
}

template<typename T>
T asm_in(uint16_t port) {
	T ret;
	asm volatile("in %0, %1" : "=a"(ret) : "Nd"(port));
	return ret;
}

template void asm_out(uint16_t port, uint8_t val);
template uint8_t asm_in(uint16_t port);
