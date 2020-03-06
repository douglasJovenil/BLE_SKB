#include "pw_mgmt.h"

APP_TIMER_DEF(timer_id);   /**< Instancia do modulo timer que acorda o micro */

void timeout_handler() {
    NRF_LOG_INFO("ACORDEI");

    enable_adc();
    advertising_start(false);
}

void sleep_mode_enter(void) {
    ret_code_t err_code;

    err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    APP_ERROR_CHECK(err_code);

    // Prepare wakeup buttons.
    err_code = bsp_btn_ble_sleep_mode_prepare();
    APP_ERROR_CHECK(err_code);

    NRF_LOG_INFO("Deep Sleep");

    disable_adc();
    err_code = sd_app_evt_wait();
    // err_code = sd_power_system_off();

    APP_ERROR_CHECK(err_code);
}

void timers_init(void) {
    // Initialize timer module.
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    // Create timers.

    /* YOUR_JOB: Create any timers to be used by the application.
                 Below is an example of how to create a timer.
                 For every new timer needed, increase the value of the macro APP_TIMER_MAX_TIMERS by
                 one.
       ret_code_t err_code;
       err_code = app_timer_create(&m_app_timer_id, APP_TIMER_MODE_REPEATED, timer_timeout_handler);
       APP_ERROR_CHECK(err_code); */

    app_timer_create(&timer_id, APP_TIMER_MODE_REPEATED, timeout_handler);
}

void power_management_init(void) {
    ret_code_t err_code;
    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);
}

void application_timers_start(void) {
/* YOUR_JOB: Start your timers. below is an example of how to start a timer.
    ret_code_t err_code;
    err_code = app_timer_start(m_app_timer_id, TIMER_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code); */

    ret_code_t err_code;
    err_code = app_timer_start(timer_id, 1000000, NULL);
    APP_ERROR_CHECK(err_code);
}