/*
 * Copyright (c) 2016, Xilinx Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

#define PLATFORM_FLAVOR_ID_zc702	0
#define PLATFORM_FLAVOR_ID_zc706	1
#define PLATFORM_FLAVOR_IS(flav) \
	(PLATFORM_FLAVOR_ID_ ## flav == PLATFORM_FLAVOR)

/* Make stacks aligned to data cache line length */
#define STACK_ALIGNMENT		64
#define HEAP_SIZE		(24 * 1024)

#ifdef CFG_WITH_PAGER
#error "Pager not supported for zynqmp"
#endif

#if PLATFORM_FLAVOR_IS(zc702) || PLATFORM_FLAVOR_IS(zc706)

#define UART0_BASE		0xE0000000
#define UART1_BASE		0xE0001000
#define SCU_BASE		0xF8F00000
#define GIC_BASE		0xF8F00100
#define PL310_BASE		0xF8F02000

#define IT_UART0		59
#define IT_UART1		82

#define UART0_CLK_IN_HZ		100000000
#define UART1_CLK_IN_HZ		100000000
#define CONSOLE_UART_BASE	UART1_BASE
#define IT_CONSOLE_UART		IT_UART1
#define CONSOLE_UART_CLK_IN_HZ	UART1_CLK_IN_HZ

#define DRAM0_BASE		0
#define DRAM0_SIZE		0x40000000

/* Location of trusted dram */
#define TZDRAM_BASE		0x30000000
#define TZDRAM_SIZE		0x08000000

#define CFG_SHMEM_START		0x38000000
#define CFG_SHMEM_SIZE		0x08000000

#define GICC_OFFSET		0
#define GICD_OFFSET		0xf00
#define GIC_DIST_BASE		(GIC_BASE + GICD_OFFSET)
#define GIC_CPU_BASE		(GIC_BASE + GICC_OFFSET)

#else
#error "Unknown platform flavor"
#endif

#define CFG_TEE_CORE_NB_CORE	2

#define CFG_TEE_RAM_VA_SIZE	(1024 * 1024)

#ifndef CFG_TEE_LOAD_ADDR
#define CFG_TEE_LOAD_ADDR	CFG_TEE_RAM_START
#endif

/*
 * Assumes that either TZSRAM isn't large enough or TZSRAM doesn't exist,
 * everything is in TZDRAM.
 * +------------------+
 * |        | TEE_RAM |
 * + TZDRAM +---------+
 * |        | TA_RAM  |
 * +--------+---------+
 */
#define CFG_TEE_RAM_PH_SIZE	CFG_TEE_RAM_VA_SIZE
#define CFG_TEE_RAM_START	TZDRAM_BASE
#define CFG_TA_RAM_START	ROUNDUP((TZDRAM_BASE + CFG_TEE_RAM_VA_SIZE), \
					CORE_MMU_DEVICE_SIZE)
#define CFG_TA_RAM_SIZE		ROUNDDOWN((TZDRAM_SIZE - CFG_TEE_RAM_VA_SIZE), \
					  CORE_MMU_DEVICE_SIZE)

#define DEVICE0_PA_BASE		ROUNDDOWN(CONSOLE_UART_BASE, CORE_MMU_DEVICE_SIZE)
#define DEVICE0_VA_BASE		DEVICE0_PA_BASE
#define DEVICE0_SIZE		CORE_MMU_DEVICE_SIZE
#define DEVICE0_TYPE		MEM_AREA_IO_SEC

#define DEVICE1_PA_BASE		ROUNDDOWN(SCU_BASE, CORE_MMU_DEVICE_SIZE)
#define DEVICE1_VA_BASE		DEVICE1_PA_BASE
#define DEVICE1_SIZE		CORE_MMU_DEVICE_SIZE
#define DEVICE1_TYPE		MEM_AREA_IO_SEC

#ifndef UART_BAUDRATE
#define UART_BAUDRATE		115200
#endif
#ifndef CONSOLE_BAUDRATE
#define CONSOLE_BAUDRATE	UART_BAUDRATE
#endif

#endif /*PLATFORM_CONFIG_H*/
