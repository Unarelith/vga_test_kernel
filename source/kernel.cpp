/*
 * =====================================================================================
 *
 *       Filename:  kernel.cpp
 *
 *    Description:  
 *
 *        Created:  29/08/2016 11:49:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Vga16Color.hpp"
#include "VgaTextMode.hpp"

#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
# error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
	// VgaTextMode vgaText;
	// vgaText.printString("Hello, kernel World!\n");
	
	Vga16Color vga16;
	vga16.clearScreen();
	
	vga16.drawRect(45, 45, 200, 60, 0xb);
	vga16.printString(50, 50, "Hello, kernel World!\nHow are u today?", 0xf);
}

