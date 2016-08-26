/*
 * =====================================================================================
 *
 *       Filename:  vga.cpp
 *
 *    Description:  
 *
 *        Created:  26/08/2016 10:59:32
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "vga.hpp"

static inline void asm_out(uint16_t port, uint32_t val) {
	asm volatile("out %0, %1" : : "a"(val), "Nd"(port));
	/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
	 * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
	 * The  outb  %al, %dx  encoding is the only option for all other cases.
	 * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint32_t asm_in(uint16_t port) {
	uint8_t ret;
	asm volatile("in %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

