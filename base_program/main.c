/**
 * Essa biblioteca NAO esta sendo usada aqui, mas as modificacoes
 * aqui descritas sao importantes
 * 
 * Para funcionar os GPIO's usando a biblioteca BSP (Board Support Package)
 * eh necessario configurar os pinos de acordo com o SKB501, pois
 * esse template utiliza como base a placa pca10056.
 * Portanto, deve-se modificar o arquivo ~/nRF5_SDK/components/boards/custom_board.h
 * de acordo com o microcontrolador em questao.
 * OBS: O arquivo custom_board.h foi criado a partir do exemplo de pca10056.h
 * 
 * Apos modificar os pinos dentro de custom_board.h deve se passar a flag BOARD_CUSTOM
 * para o compilador, podemos fazer isso dentro do Makefile, que se encontra em
 * ./pca10056/s140/armgcc/Makefile
 * 
 * Dentro desse arquivo modificar a linha:
 * CFLAGS += -DBOARD_PCA10056
 * para:
 * CFLAGS += -DBOARD_CUSTOM
 * 
 * E tambem modificar
 * ASMFLAGS += -DBOARD_PCA10056
 * para:
 * ASMFLAGS += -DBOARD_CUSTOM
*/
#include "boards.h"

/**
 * Biblioteca implementada para o funcionamento do BLE.
 * 
 * Devido ao alto acoplamento entre as funcoes do BSP 
 * elas foram implementadas dentro de ble_d.
 * 
 * Funcoes utilizadas:
 *  - buttons_leds_init()
 *  - ble_stack_init()
 *  - gap_params_init()
 *  - gatt_init()
 *  - advertising_init()
 *  - services_init()
 *  - conn_params_init()
 *  - peer_manager_init()
 *  - advertising_start()
 *  - idle_state_handle()
*/
#include "ble_d.h"

/**
 * Biblioteca implementada para o funcionamento do ADC.
 * 
 * Ela NAO esta sendo usada aqui, porem eh utilizada dentro de pw_mgmt.h
 * Esta sendo citada pois modificacoes podem ser necessarias.
 * 
 * Funcoes utilizadas:
 *  - saadc_sampling_event_init()
 *  - saadc_sampling_event_enable()
 *  - saadc_init()
*/
#include "adc.h"

/**
 * Biblioteca implementada para as funcoes Low Power.
 * 
 * Funcoes:
 *  - timers_init()              -> Inicializa o timer que vai ficar acordando o micro
 *  - power_management_init()    -> Inicializa o gerenciamento de potencia
 *  - application_timers_start() -> Starta os timers   
*/
#include "pw_mgmt.h"

/**
 * Biblioteca implementada para as funcoes gerais.
 * 
 * Funcoes utilizadas: log_init()
*/
#include "common.h"

/**
 * Alguns links importantes:
 * 
 * How to minimize current consumption for BLE application on nRF51822
 * https://devzone.nordicsemi.com/f/nordic-q-a/1657/how-to-minimize-current-consumption-for-ble-application-on-nrf51822/7351#7351
 * 
 * System ON Sleep mode
 * https://devzone.nordicsemi.com/f/nordic-q-a/38832/system-on-sleep-mode/156595#156595
 * 
 * nRF52840 Datasheet
 * https://infocenter.nordicsemi.com/pdf/nRF52840_PS_v1.0.pdf
*/

int main(void) {
    bool erase_bonds = false;

    // Initialize.

    // COMENTAR ESSA BIBLIOTECA AO UTILIZAR EM PRODUCAO
    // utilize apenas para debug
    // log_init(); 
    timers_init(); 
    // Modificada para ligar apenas os botoes de interrupcao
    buttons_leds_init(&erase_bonds);
    power_management_init();
    ble_stack_init();
    gap_params_init();
    gatt_init();
    advertising_init();
    services_init();
    conn_params_init();
    peer_manager_init();
    
    saadc_init();
    saadc_sampling_event_init();
    saadc_sampling_event_enable();

    application_timers_start();

    // Start execution.
    NRF_LOG_INFO("Template example started.");

    advertising_start(erase_bonds);

    // Enter main loop.
    while (true) {
        idle_state_handle();
    }
}
