#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#define CC "arm-none-eabi-gcc"

int main(int argc, char** argv) {

	NOB_GO_REBUILD_URSELF(argc, argv);
	
	Cmd cmd = {0};

	cmd_append(&cmd, CC, "main.c", "startup_stm32f103xb.s", "system_stm32f1xx.c", "-T", "STM32F102X6_FLASH.ld", "-o", "build.elf", "-I/usr/arm-none-eabi/include", "-ICMSIS/Core/Include", "-ICMSIS/STM32F1/Include", "-mcpu=cortex-m3", "-mthumb", "-nostdlib", "-DSTM32F103x6");
	if (!cmd_run(&cmd)) return 0;

	cmd_append(&cmd, "arm-none-eabi-objcopy", "-O", "binary", "build.elf", "build.bin");
	if (!cmd_run(&cmd)) return 0;

	cmd_append(&cmd, "st-flash", "write", "build.bin", "0x08000000");
	if (!cmd_run(&cmd)) return 0;

	return 0;
}
