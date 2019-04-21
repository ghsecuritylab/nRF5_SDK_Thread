/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**@cond To Make Doxygen skip documentation generation for this file.
 * @{
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "bsp.h"

#include "sdk_config.h"
#include "nrf.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_power.h"
#include "nordic_common.h"
#include "nrf_gpio.h"

#include "app_scheduler.h"
#include "app_timer.h"
#include "app_error.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "benchmark_api.h"
#include "protocol_api.h"
#include "ble_advertiser.h"
#include "ble_central.h"
#include "ble_ping.h"
#include "cpu_utilization.h"

#include "nrf_sdh_ble.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh.h"
#include "nrf_soc.h"

#include "cli_api.h"

#include "cli_suppress.h"

#define APP_BLE_OBSERVER_PRIO       1                               /**< Application's BLE observer priority. You shouldn't need to modify this value. */
#define APP_BLE_CONN_CFG_TAG        1                               /**< A tag identifying the SoftDevice BLE configuration. */

/**@brief Scheduler configuration. */
#define SCHED_MAX_EVENT_DATA_SIZE   BENCHMARK_SCHED_MAX_EVENT_DATA_SIZE
#define SCHED_QUEUE_SIZE            32

/***************************************************************************************************
 * @section Callbacks
 **************************************************************************************************/

/**@brief Function for handling events from the BSP module.
 *
 * @param[in]   event   Event generated by button press.
 */
static void bsp_event_handler(bsp_event_t event)
{
    uint32_t err;
    uint32_t cpu_util;

    switch (event)
    {
        case BSP_EVENT_KEY_0:
            NRF_LOG_INFO("CPU Utilization measurement started.");
            err = cpu_utilization_start();
            APP_ERROR_CHECK(err);
            break;

        case BSP_EVENT_KEY_1:
            NRF_LOG_INFO("CPU Utilization measurement stopped.");
            err = cpu_utilization_stop();
            APP_ERROR_CHECK(err);
            break;

        case BSP_EVENT_KEY_2:
            cpu_util = cpu_utilization_get();
            NRF_LOG_INFO("CPU Utilization: %d.%02d%%.", (cpu_util / 100), (cpu_util % 100));
            break;

        case BSP_EVENT_KEY_3:
            NRF_LOG_INFO("CPU Utilization measurement cleared.");
            cpu_utilization_clear();
            break;

          default:
            break;
    }
}

/**@brief Function for handling BLE events.
 *
 * @param[inout]   p_ble_evt   Bluetooth stack event.
 * @param[in]      p_context   Unused.
 */
static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
    ret_code_t err_code;

    UNUSED_VARIABLE(p_context);

    ble_advertiser_evt_handle(p_ble_evt);
    ble_connection_evt_handle(p_ble_evt);
    ble_ping_evt_handle(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            NRF_LOG_INFO("Connected over Bluetooth.");
            err_code = bsp_indication_set(BSP_INDICATE_CONNECTED);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            NRF_LOG_INFO("Bluetooth connection lost.");
            err_code = bsp_indication_set(BSP_INDICATE_CONNECTED);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
            NRF_LOG_INFO("Connection parameters updated.");
            break;

        default:
            break;
    }
}

/**@brief Function for handling SOC events.
 *
 * @param[in]   sys_evt     SoC stack event.
 * @param[in]   p_context   Unused.
 */
static void soc_evt_handler(uint32_t sys_evt, void * p_context)
{
    UNUSED_PARAMETER(p_context);

    protocol_soc_evt_handler(sys_evt);
}

/***************************************************************************************************
 * @section Init
 **************************************************************************************************/

/**@brief Function for initializing the logging module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(app_timer_cnt_get);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Function for initializing the Board Support Package.
 */
static void app_bsp_init(void)
{
    uint32_t err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, bsp_event_handler);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module. This creates and starts application timers.
 */
static void timer_init(void)
{
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing the Power Driver.
 */
static void power_driver_init(void)
{
    ret_code_t ret = nrf_drv_power_init(NULL);
    APP_ERROR_CHECK(ret);
}

/**@brief Function for initializing the Clock Driver.
 */
static void clock_driver_init(void)
{
    ret_code_t ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);
}

/**@brief Function for initializing the BLE stack.
 */
static void ble_stack_init(void)
{
    ret_code_t err_code;

    err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    // Configure the BLE stack using the default settings.
    // Fetch the start address of the application RAM.
    uint32_t ram_start = 0;
    err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    APP_ERROR_CHECK(err_code);

    // Enable BLE stack.
    err_code = nrf_sdh_ble_enable(&ram_start);
    APP_ERROR_CHECK(err_code);

    // Register a handler for BLE events.
    NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);

    // Register a handler for SOC events.
    NRF_SDH_SOC_OBSERVER(m_soc_observer, NRF_SDH_SOC_STACK_OBSERVER_PRIO, soc_evt_handler, NULL);
}

/**@brief Function for initializing the scheduler module.
 */
static void scheduler_init(void)
{
    APP_SCHED_INIT(SCHED_MAX_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
}

int main(void)
{
    uint32_t err_code;

    log_init();
    clock_driver_init();
    scheduler_init();
    power_driver_init();
    timer_init();
    app_bsp_init();

    err_code = cpu_utilization_init();
    APP_ERROR_CHECK(err_code);

    ble_stack_init();
    ble_ping_init();

    // Initialize the protocol stack.
    protocol_init();
    benchmark_init();

    cli_init();
    cli_remote_init();

    // Start interpreting CLI commands.
    cli_start();
    cli_remote_start();

    for (;;)
    {
        protocol_process();
        benchmark_process();
        app_sched_execute();

        if (!cli_suppress_is_enabled())
        {
            cli_process();

            if (NRF_LOG_PROCESS() == false)
            {
                protocol_sleep();
            }
        }
        else
        {
            protocol_sleep();
        }
    }
}


/**
 * @}
 */
