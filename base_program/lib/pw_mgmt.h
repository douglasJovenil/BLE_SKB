#ifndef __PW__MGMT__H__
#define __PW__MGMT__H__

#ifdef __cplusplus
extern "C" {
#endif

/** Biblioteca do ADC */
#include "adc.h"
/** Biblioteca do BLE */
#include "ble_d.h"

/**@brief Funcao que acorda o micro
 */
void timeout_handler();

/**@brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
void sleep_mode_enter(void);

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module. This creates and starts application timers.
 */
void timers_init(void);

/**@brief Function for initializing power management.
 */
void power_management_init(void);

/**@brief Function for starting timers.
 */
void application_timers_start(void);

#ifdef __cplusplus
}
#endif

#endif