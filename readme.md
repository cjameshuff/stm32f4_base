
STM32F4DISCOVERY evaluation board: http://www.st.com/internet/evalboard/product/252419.jsp

Toolchain: https://github.com/esden/summon-arm-toolchain

stlink programmer/debugger: https://github.com/texane/stlink

The makefile takes a full path to each source file, and places each object file in an analogous location in ROOT/obj, with a suffix that depends on the source file type. For example, src/foo/bar.c compiles to obj/src/foo/bar.c.o, and src/delay.s compiles to obj/src/delay.s.o, thus avoiding naming conflicts.
The `make disasm` target similarly puts disassembly output for each file and for the complete binary in ROOT/disasm.
A .map file is automatically generated as $(EXECNAME).map.
The `make flash` target flashes a board using the stlink tool.

The linker script assigns the 64 kB core-coupled SRAM block for the main memory, allowing code to run without competing with peripherals on the AHB bus. The 112 kB and 16 kB blocks of system SRAM are given sections sram112k and sram16k, and buffers to be accessed via DMA must be placed in these sections.
The 4 kB of battery backup SRAM is given the section bkpsram. 


# LICENSE

Unless noted otherwise, all code is released under the MIT license. Two exceptions are the CMSIS code, which is under the license described in CMSIS END USER LICENCE AGREEMENT.pdf, and the support code under [ST's license](http://www.st.com/software_license_agreement_liberty_v2). 
