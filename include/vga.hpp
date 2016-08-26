/*
 * =====================================================================================
 *
 *       Filename:  vga.hpp
 *
 *    Description:  
 *
 *        Created:  26/08/2016 10:59:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef VGA_HPP_
#define VGA_HPP_

#include <stdint.h>

static inline void asm_out(uint16_t port, uint32_t val);
static inline uint32_t asm_in(uint16_t port);

#endif // VGA_HPP_
