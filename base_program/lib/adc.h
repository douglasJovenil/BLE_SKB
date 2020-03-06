#ifndef __ADC__H__
#define __ADC__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_log.h"

/**
 * As bibliotecas nrf_drv_saadc.h, nrf_drv_timer.h e nrf_drv_ppi.h sao necessarias
 * para a utilizacao do adc. Para compilar elas deve ser adicionas no Makefile
 * dentro da variavel SRC_FILE, portanto adicione as seguintes linhas:
 * 
 * $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_saadc.c 
 * $(SDK_ROOT)/integration/nrfx/legacy/nrf_drv_ppi.c 
 * $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_ppi.c 
 * $(SDK_ROOT)/modules/nrfx/drivers/src/nrfx_timer.c 
 * 
 * Alem disso, devemos habilitar esses perifericos dentro 
 * do arquivo ../pca10056/config/sdk_config.h, verifique se 
 * o sdk_config possui as seguintes linhas:
 * 
 * #define PPI_ENABLED 1
 * #define TIMER_ENABLED 1
 * #define SAADC_ENABLED 1
 * #define SAADC_CONFIG_LP_MODE 1
 * #define TIMER3_ENABLED 1
*/

#include "nrf_drv_saadc.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_ppi.h"

void timer_handler(nrf_timer_event_t event_type, void * p_context);
void saadc_sampling_event_init(void);
void saadc_sampling_event_enable(void);
void saadc_callback(nrf_drv_saadc_evt_t const * p_event);
void saadc_init(void);
void enable_adc(void);
void disable_adc(void);

#ifdef __cplusplus
}
#endif

#endif