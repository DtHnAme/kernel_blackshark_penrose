// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023, The Linux Foundation. All rights reserved.
 */

#include <linux/soc/qcom/fsa4480-i2c.h>
#include <linux/of_gpio.h>

#include "dp_switch.h"
#include "dp_debug.h"

static int aux_cc_gpio;
static int uart_en_gpio;

int dp_usb_switch_init_gpio(struct device *dev) {
	int rc;

	aux_cc_gpio = of_get_named_gpio(dev->of_node, "qcom,aux-cc-gpio", 0);
	rc = devm_gpio_request(dev, aux_cc_gpio, "aux_cc_gpio");
	if (rc) {
		DP_ERR("request aux-cc-gpio failed\n");
	}

	uart_en_gpio = of_get_named_gpio(dev->of_node, "qcom,uart-en-gpio", 0);
	rc = devm_gpio_request(dev, uart_en_gpio, "uart_en_gpio");
	if (rc) {
		DP_ERR("request uart-en-gpio failed\n");
	}

	DP_DEBUG("aux_cc_gpio: %d uart-en-gpio: %d\n", aux_cc_gpio, uart_en_gpio);

	return rc;
}

int dp_usb_switch_event(int event) {
    switch (event) {
        case FSA_USBC_ORIENTATION_CC1:
            gpio_direction_output(uart_en_gpio, 1);
            msleep(10);
            gpio_direction_output(aux_cc_gpio, 0);
            break;
        case FSA_USBC_ORIENTATION_CC2:
            gpio_direction_output(uart_en_gpio, 1);
            msleep(10);
            gpio_direction_output(aux_cc_gpio, 1);
            break;
        case FSA_USBC_DISPLAYPORT_DISCONNECTED:
            gpio_direction_output(uart_en_gpio, 0);
            break;
        default:
            break;
    }

    DP_DEBUG("dp_usb_switch_event: %d aux-cc-gpio: %d uart-en-gpio: %d\n", event, aux_cc_gpio, uart_en_gpio);

    return 0;
};
