/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_test

#include <zephyr/device.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <drivers/behavior.h>
#include <zmk/behavior.h>
#include "pmw3610.h"

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)

static const struct behavior_parameter_value_metadata no_arg_values[] = {
    {
        .display_name = "CPI_I200",
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
        .value = CPI_I200,
    },
    {
        .display_name = "CPI_D200",
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
        .value = CPI_D200,
    },
};

static const struct behavior_parameter_metadata_set no_args_set = {
    .param1_values = no_arg_values,
    .param1_values_len = ARRAY_SIZE(no_arg_values),
};

static const struct behavior_parameter_metadata_set profile_index_metadata_set = {
    .param1_values = prof_index_param1_values,
    .param1_values_len = ARRAY_SIZE(prof_index_param1_values),
};

static const struct behavior_parameter_metadata_set metadata_sets[] = {no_args_set,
                                                                       profile_index_metadata_set};

static const struct behavior_parameter_metadata metadata = {
    .sets_len = ARRAY_SIZE(metadata_sets),
    .sets = metadata_sets,
};

#endif // IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    switch (binding->param1) {
    case CPI_I200:
        return set_cpi_if_needed(data->curr_cpi+200);
    case CPI_D200:
        return set_cpi_if_needed(data->curr_cpi-200);
    default:
        LOG_ERR("Unknown BT command: %d", binding->param1);
    }

    return -ENOTSUP;
}

static int behavior_test_init(const struct device *dev) { return 0; };

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_test_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .parameter_metadata = &metadata,
#endif // IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
};

BEHAVIOR_DT_INST_DEFINE(0, behavior_test_init, NULL, NULL, NULL, POST_KERNEL,
                        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_test_driver_api);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
