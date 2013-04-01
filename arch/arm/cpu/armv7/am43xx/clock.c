/*
 * clock.c
 *
 * clocks for AM43XX based boards (copied from AM33XX)
 *
 * Copyright (C) 2013, Texas Instruments, Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR /PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clock.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>

#define PRCM_MOD_EN		0x2

const struct cm_per *cmper = (struct cm_per *)CM_PER;
const struct cm_wkup *cmwkup = (struct cm_wkup *)CM_WKUP;

/* Enable the clock for required peripherals */
static void enable_per_clocks(void)
{
	/* TIMER2 */
	writel(PRCM_MOD_EN, &cmper->timer2clkctrl);
	while (readl(&cmper->timer2clkctrl) != PRCM_MOD_EN)
		;

	/* UART0 */
	writel(PRCM_MOD_EN, &cmwkup->wkup_uart0ctrl);
	while (readl(&cmwkup->wkup_uart0ctrl) != PRCM_MOD_EN)
		;

	/* EMIF */
	writel(PRCM_MOD_EN, &cmper->emifclkctrl);
	while (readl(&cmper->emifclkctrl) != PRCM_MOD_EN)
		;

	/* EMIF FW */
	writel(PRCM_MOD_EN, &cmper->emiffwclkctrl);
	while (readl(&cmper->emiffwclkctrl) != PRCM_MOD_EN)
		;

	/* OTFA EMIF */
	writel(PRCM_MOD_EN, &cmper->otfaemifclkctrl);
	while (readl(&cmper->otfaemifclkctrl) != PRCM_MOD_EN)
		;
}

void clk_init(void)
{
	enable_per_clocks();
}
