/*
 * Copyright (C) 2010 MediaTek, Inc.
 *
 * Author: Terry Chang <terry.chang@mediatek.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _MTK_KPD_H_
#define _MTK_KPD_H_

#include <linux/kernel.h>
#if defined(CONFIG_MTK_LEGACY)
#include <cust_kpd.h>
#endif
#include <mach/mt_pm_ldo.h>
#include <linux/delay.h>
/* include PMIC header file */
#include <mach/mt_typedefs.h>
#include <mach/upmu_common_sw.h>
#include <mach/upmu_hw.h>
#define KPD_PWRKEY_USE_EINT 0
#define KPD_PWRKEY_USE_PMIC 1
#define KPD_DRV_CTRL_BACKLIGHT	0	/* retired, move to Lights framework */
#define KPD_BACKLIGHT_TIME	8	/* sec */
/* the keys can wake up the system and we should enable backlight */
#define KPD_BACKLIGHT_WAKE_KEY	\
{				\
	KEY_ENDCALL, KEY_POWER,	\
}

#define KPD_HAS_SLIDE_QWERTY	1	//0
#if KPD_HAS_SLIDE_QWERTY
static inline bool powerOn_slidePin_interface() {
	return 1;	//hwPowerOn(MT65XX_POWER_LDO_VCAM_IO, VOL_2800, "Qwerty slide");
}
static inline bool powerOff_slidePin_interface(){
	return 1;	//hwPowerDown(MT65XX_POWER_LDO_VCAM_IO, "Qwerty slide");
}
#endif
#define KPD_SLIDE_EINT		CUST_EINT_KPD_SLIDE_NUM
#define KPD_SLIDE_DEBOUNCE	CUST_EINT_KPD_SLIDE_DEBOUNCE_CN		/* ms */
#define KPD_SLIDE_POLARITY	0	//CUST_EINT_KPD_SLIDE_POLARITY
//#define KPD_SLIDE_SENSITIVE	CUST_EINT_KPD_SLIDE_SENSITIVE

#if KPD_DRV_CTRL_BACKLIGHT
extern void kpd_enable_backlight(void);
extern void kpd_disable_backlight(void);
extern void kpd_backlight_handler(bool pressed, u16 linux_keycode);
#else
#define kpd_enable_backlight()		do {} while (0)
#define kpd_disable_backlight()		do {} while (0)
#define kpd_backlight_handler(pressed, linux_keycode)	do {} while (0)
#endif

/* for META tool */
extern void kpd_set_backlight(bool onoff, void *val1, void *val2);

#if KPD_PWRKEY_USE_PMIC
void kpd_pwrkey_pmic_handler(unsigned long pressed);
#else
static inline void kpd_pwrkey_pmic_handler(unsigned long data){}
#endif

void kpd_pmic_rstkey_handler(unsigned long pressed);

/* KPD_PMIC_RSTKEY_MAP is defined in cust_kpd.h */
/* Long press settings are moved to Kconfig */

#endif
