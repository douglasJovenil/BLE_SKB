#ifndef __COMMON__H__
#define __COMMON__H__

#ifdef __cplusplus
#endif

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

/**@brief Function for initializing the nrf log module.
 */
void log_init(void);

#ifdef __cplusplus
#endif

#endif
