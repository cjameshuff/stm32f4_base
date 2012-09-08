
Toolchain: https://github.com/esden/summon-arm-toolchain
stlink programmer/debugger: https://github.com/texane/stlink

The makefile takes a full path to each source file, and places each object file in an analogous location in ROOT/obj, with a suffix that depends on the source file type. For example, src/foo/bar.c compiles to obj/src/foo/bar.c.o, and src/delay.s compiles to obj/src/delay.s.o, thus avoiding naming conflicts.
The `make disasm` target similarly puts disassembly output for each file and for the binary in ROOT/disasm.
A .map file is automatically generated as $(EXECNAME).map.
