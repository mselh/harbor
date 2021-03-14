# makefile for harbor
# msh 13.03.2021


os = $(shell uname)

# gcc arm tools all have a prefix in common
# alas, it is os-dependent
#
ifeq ($(os), Darwin)
	arm = arm-none-eabi
else
	arm = gcc-arm-none-eabi
endif

# the key tools to make ELF
as = $(arm)-as
cc = $(arm)-gcc -mcpu=cortex-m3 -g
# arm-ld uses bfd according to the manual
ld = $(arm)-ld

# debugging tools
gdb = $(arm)-gdb



# // kernel.elf  //

# first compile the c program to object file
start.o: start.c
	$(cc) -c start.c -o build/start.o
rcc.o: rcc.c
	$(cc) -c rcc.c  -o build/rcc.o

# the output of entry.s 
entry.o: entry.s
	$(as) entry.s -o build/entry.o

# combine object files, with the linker, and make the ELF
kernel.elf: entry.o start.o rcc.o
	cd build; \
	$(ld) -T ../kernel.lds -o kernel.elf entry.o start.o rcc.o



# // Utilities //

# flashes openocd
flash: kernel.elf
	cd build; \
	 openocd -f /usr/local/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/local/share/openocd/scripts/target/stm32f1x.cfg -c "program kernel.elf verify reset exit"

prefix:
	echo $(arm)
