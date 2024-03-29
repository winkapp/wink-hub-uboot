/*
 * (C) Copyright 2010
 * Texas Instruments Incorporated.
 * Aneesh V       <aneesh@ti.com>
 * Steve Sakoman  <steve@sakoman.com>
 *
 * TI OMAP4 common configuration settings
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_TI_OMAP4_COMMON_H
#define __CONFIG_TI_OMAP4_COMMON_H

/*
 * High Level Configuration Options
 */
#define CONFIG_OMAP44XX		1	/* which is a 44XX */
#define CONFIG_OMAP4430		1	/* which is in a 4430 */
#define CONFIG_MISC_INIT_R
#define CONFIG_ARCH_CPU_INIT
#define CONFIG_DISPLAY_CPUINFO		1
#define CONFIG_DISPLAY_BOARDINFO	1

#define CONFIG_SYS_THUMB_BUILD

#ifndef CONFIG_SYS_L2CACHE_OFF
#define CONFIG_SYS_L2_PL310		1
#define CONFIG_SYS_PL310_BASE	0x48242000
#endif
#define CONFIG_SYS_CACHELINE_SIZE	32

/* Get CPU defs */
#include <asm/arch/cpu.h>
#include <asm/arch/omap.h>

/* Use General purpose timer 1 */
#define CONFIG_SYS_TIMERBASE		GPT2_BASE

/*
 * Total Size Environment - 128k
 */
#define CONFIG_ENV_SIZE			(128 << 10)

/*
 * For the DDR timing information we can either dynamically determine
 * the timings to use or use pre-determined timings (based on using the
 * dynamic method.  Default to the static timing infomation.
 */
#define CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS
#ifndef CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS
#define CONFIG_SYS_AUTOMATIC_SDRAM_DETECTION
#define CONFIG_SYS_DEFAULT_LPDDR2_TIMINGS
#endif

#include <configs/ti_armv7_common.h>

/*
 * Hardware drivers
 */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		48000000
#define CONFIG_CONS_INDEX		3
#define CONFIG_SYS_NS16550_COM3		UART3_BASE

/* TWL6030 */
#ifndef CONFIG_SPL_BUILD
#define CONFIG_TWL6030_POWER		1
#endif

/* USB */
#define CONFIG_MUSB_UDC			1
#define CONFIG_USB_OMAP3		1

/* USB device configuration */
#define CONFIG_USB_DEVICE		1
#define CONFIG_USB_TTY			1
#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1

/* Per-Soc commands */
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS

/*
 * Environment setup
 */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x82000000\0" \
	"console=ttyO2,115200n8\0" \
	"fdt_high=0xffffffff\0" \
	"fdtaddr=0x80f80000\0" \
	"fdtfile=undefined\0" \
	"bootpart=0:2\0" \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"usbtty=cdc_acm\0" \
	"vram=16M\0" \
	"mmcdev=0\0" \
	"mmcroot=/dev/mmcblk0p2 rw\0" \
	"mmcrootfstype=ext3 rootwait\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"vram=${vram} " \
		"root=${mmcroot} " \
		"rootfstype=${mmcrootfstype}\0" \
	"loadbootscript=fatload mmc ${mmcdev} ${loadaddr} boot.scr\0" \
	"bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
		"source ${loadaddr}\0" \
	"loadbootenv=fatload mmc ${mmcdev} ${loadaddr} uEnv.txt\0" \
	"importbootenv=echo Importing environment from mmc${mmcdev} ...; " \
		"env import -t ${loadaddr} ${filesize}\0" \
	"loadimage=load mmc ${bootpart} ${loadaddr} ${bootdir}/${bootfile}\0" \
	"mmcboot=echo Booting from mmc${mmcdev} ...; " \
		"run mmcargs; " \
		"bootz ${loadaddr} - ${fdtaddr}\0" \
	"findfdt="\
		"if test $board_name = sdp4430; then " \
			"setenv fdtfile omap4-sdp.dtb; fi; " \
		"if test $board_name = panda; then " \
			"setenv fdtfile omap4-panda.dtb; fi;" \
		"if test $board_name = panda-a4; then " \
			"setenv fdtfile omap4-panda-a4.dtb; fi;" \
		"if test $board_name = panda-es; then " \
			"setenv fdtfile omap4-panda-es.dtb; fi;" \
		"if test $fdtfile = undefined; then " \
			"echo WARNING: Could not determine device tree to use; fi; \0" \
	"loadfdt=load mmc ${bootpart} ${fdtaddr} ${bootdir}/${fdtfile}\0" \

#define CONFIG_BOOTCOMMAND \
	"run findfdt; " \
	"mmc dev ${mmcdev}; if mmc rescan; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"else " \
			"if run loadbootenv; then " \
				"run importbootenv; " \
			"fi;" \
			"if test -n ${uenvcmd}; then " \
				"echo Running uenvcmd ...;" \
				"run uenvcmd;" \
			"fi;" \
		"fi;" \
		"if run loadimage; then " \
			"run loadfdt;" \
			"run mmcboot; " \
		"fi; " \
	"fi"

/*
 * Defines for SPL
 * It is known that this will break HS devices. Since the current size of
 * SPL is overlapped with public stack and breaking non HS devices to boot.
 * So moving TEXT_BASE down to non-HS limit.
 */
#define CONFIG_SPL_TEXT_BASE		0x40300000
#define CONFIG_SPL_MAX_SIZE		(0x4030C000 - CONFIG_SPL_TEXT_BASE)
#define CONFIG_SPL_DISPLAY_PRINT
#define CONFIG_SPL_LDSCRIPT "$(CPUDIR)/omap-common/u-boot-spl.lds"

#ifdef CONFIG_NAND
#define CONFIG_SPL_NAND_AM33XX_BCH	/* ELM support */
#endif

#endif /* __CONFIG_TI_OMAP4_COMMON_H */
