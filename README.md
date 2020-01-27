# BLE_SKB
<p align="center"><img src="https://images-na.ssl-images-amazon.com/images/I/81Mx3JxGdfL._SX466_.jpg"></p>

### Comunicando com o nRF

```bash
$ git clone https://github.com/blacksphere/blackmagic.git
$ cd ./blackmagic
$ git submodule init
$ git submodule update

$ sudo make
$ cd ./src

$ sudo make clean && sudo make PROBE_HOST=stlink                -> ira gerar os arquivos blackmagic.bin e blackmagic_dfu.bin
```
* Para gravar os binarios gerados, utilizando o gravador ST-LINK e o software do ST-LINK no OS Windows, ter certeza de que **BOOT0** e **BOOT1** do **STM32F103C8T6** estão em nível lógico **zero**.
* Gravar o blackmagic_dfu.bin no endreço 0x8000000.
* Gravar o blackmagic.bin no endereço 0x8002000.

Conectar o SKB501 com o Blue Pill como segue:

* VCC - VCC
* GND - GND
* A5 - SWDIO
* B14 - SWCLK

```bash
$ arm-none-eabi-gdb
$ target extended-remote /dev/tty_PORTA_COM_GDB_SERVER
$ att num_nrf52                                             -> Se tudo estiver funcionando, o gdb irá se conectar no nRF52840
```

### Programando
```bash
$ pio device list                           -> Identificar a porta do Black Magic GDB Server
$ arm-none-eabi-gdb                         -> Abrir o software para comunicar com o nRF52840
$ target extended-remote <PORT_GDB_SERVER>  -> Abre a porta do Black Magic Probe
$ mon swdp_scan                             -> Procura por dispositivos plugados no computador que utilizam o protocolo SWD
$ att <NUM_NRF52840>                        -> Conecta no nRF52840
$ mon mass_erase                            -> Apaga a flash
$ pio init -b nrf52_dk                      -> Cria o projeto no platformio
```

* Para gravar no nRF52840 deve ser colocado na flash o firmware da MBR, por padrão o platformio instala o MBR.
* Dentro do projeto gravador criar um arquivo **main.cpp** com as funções **void loop()** e **void setup()**.
* Abrir o arquivo **platformio.ini** e colocar as seguintes configurações:
```
[env:nrf52_dk]
platform = nordicnrf52
board = nrf52_dk
framework = arduino
upload_protocol = blackmagic
```
* As configurações podem variar de acordo com a placa, porém o **upload_protocol** será **blackmagic**,
```
$ pio run -t upload -> Grava o programa main junto com o MBR
```

* O Bluetooth necessita de um firmware separado para funcionar, chamado de **softdevice**.
* Para instalar o softdevice, baixar o plugin para arduino em <a href="https://github.com/sandeepmistry/arduino-nRF5/releases/download/tools/nRF5FlashSoftDevice.jar" target='_blank'>nRF5FlashSoftDevice</a>.
* Criar uma pasta em ***<PATH_SKETCHBOOK_ARDUINO>/tools/nRF5FlashSoftDevice/tool/*** e colocar o arquivo baixado dentro dela.
* Abrir o **arduino**, ir em **File** -> **Preferences** no campo **Additional Boards Manager URLs** adicionar a seguinte URL:
```html
https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json
```
* Ir em **Tools** -> **Boards** -> **Boards Manager** e procurar por **nRF52**, instalar o pacote do **sandeepmistry**.
* Em **Tools** selecionar as seguintes opções (podem variar de acordo com a placa):
```
Board: Generic nRF52
Softdevice: S132
Programmer: Black Magic Probe(GDB)
```
* Clicar na aba **nRF5 Flash SoftDevice** para colocar o firmware do bluetooth no nRF52840
    * *Talvez seja necessário modificar o arquivo **softdevices.txt**, caso o link de download esteja desatualizado, procurar pelo novo link em <a href="https://www.nordicsemi.com/Software-and-Tools/Software/S132/Download#infotabs" target="_blank">S132</a>*
    * *Ir na pasta **<sandeepmitry>/hardware/nRF5/0.6.0** e abrir o arquivo **softdevices.txt** e atualizar o mesmo.*
* Com o MBR e SoftDevice o nRF52840 estará pronto para programação.

* Abrir o platformio.ini e adicionar modificar para:
```
[common]
lib_deps = BLEPeripheral
build_flags = -DNRF52_S132

[env:nrf52_dk]
platform = nordicnrf52
board = nrf52_dk
framework = arduino
upload_protocol = blackmagic
build_flags = ${common.build_flags}
lib_deps = ${common.lib_deps}
```

* Abrir o **main.cpp** e utilizar o seguinte o <a href="https://github.com/douglasJovenil/BLE_SKB/blob/master/exemplo/src/main.cpp" target="_blank">código</a>.

```bash
$ pio run -t upload
```

<!-- 
################### END Programando ###################

## JLINK

Baixar o Jlink Commander em: https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb -->