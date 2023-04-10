/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2023, The Linux Foundation. All rights reserved.
 */

#ifndef _DP_SWITCH_H_
#define _DP_SWITCH_H_

int dp_usb_switch_init_gpio(struct device *dev);
int dp_usb_switch_event(int event);

#endif /*_DP_SWITCH_H_*/
