#include <stddef.h>
#include <stdint.h>

#include "VgaTextMode.hpp"

/* Check if the compiler thinks we are targeting the wrong operating system. */
// #if defined(__linux__)
// #error "You are not using a cross-compiler, you will most certainly run into trouble"
// #endif

/* This tutorial will only work for the 32-bit ix86 targets. */
// #if !defined(__i386__)
// #error "This tutorial needs to be compiled with a ix86-elf compiler"
// #endif
//

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
	/* Initialize terminal interface */
	VgaTextMode vgaText;
	
	/* Since there is no support for newlines in VgaTextMode::printChar
	 * yet, '\n' will produce some VGA specific character instead.
	 * This is normal.
	 */
	vgaText.printString("Hello, kernel World!\n");
}
