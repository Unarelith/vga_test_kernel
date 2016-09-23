/*
 * =====================================================================================
 *
 *       Filename:  asm.hpp
 *
 *    Description:  
 *
 *        Created:  26/08/2016 10:59:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef ASM_HPP_
#define ASM_HPP_

#include <stdint.h>

void write_vga_reg(uint16_t port, uint8_t index, uint8_t val);

template<typename T>
void asm_out(uint16_t port, T val);

template<typename T>
T asm_in(uint16_t port);

#endif // ASM_HPP_
