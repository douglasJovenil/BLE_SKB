# BLE_SKB
<p align="center"><img src="https://images-na.ssl-images-amazon.com/images/I/81Mx3JxGdfL._SX466_.jpg"></p>

### JLINK

Realizar a montagem do hardware como segue 

<p align="center"><img src="https://i.imgur.com/YesQOCq.png"></p>

Baixar o Jlink Commander <a href="https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb" target="_blank">aqui</a> e instalar o pacote com o seguinte:
```bash
$ sudo dpkg -i nome_pacote_jlink.deb
```

Baixar o SDK da Nordic <a href="https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK" target="_blank">aqui</a>, após o download extraia o arquivo em seu local de preferência, a partir de agora iremos referenciar esse local como **PATH_NRF5_SDK**.

Instalar o seguinte
```bash
$ sudo apt-get install gcc-arm-none-eabi libnewlib-arm-none-eabi -y
```

Abra o arquivo que se encontra em **PATH_NRF5_SDK/components/toolchain/gcc/Makefile.posix**

Edite para parecer como mostra abaixo

```bash
GNU_INSTALL_ROOT ?= /usr/bin/
GNU_VERSION ?= 7.3.1
GNU_PREFIX ?= arm-none-eabi
```

onde:
* **GNU_INSTALL_ROOT**: é o **local de instação** do arm-none-eabi-gcc, pode ser verificado com o comando
    ```bash
    $ which arm-none-eabi-gcc
    ```
* **GNU_VERSION**: é a versão do arm-none-eabi-gcc, pode ser verificada com
    ```bash
    $ arm-none-eabi-gcc --version
    ```
* **GNU_PREFIX**: é o prefixo das aplicações arm-none-eabi, será o mesmo do exemplo acima.

**Verifique as informações citadas e atualize o arquivo Makefile.posix de acordo com o que está no seu computador**

Como utilizaremos um exemplo com bluetooth, navegue até **PATH_NRF5_SDK/examples/ble_peripheral** copie o projeto **ble_app_template** e cole EM **PATH_NRF5_SDK/examples/ble_peripheral**, troque o nome da pasta para um de sua preferência, a partir de agora iremos chamar esse nome escolhido como **PATH_PROJETO**

Abra o **PATH_PROJETO** e edite o arquivo **main.c** de acordo com suas necessidades.

Para compilar devemos utilizar o código compatível com o do **SKB501** que utiliza o micro **nRF52840**, que no caso é a placa **pca10056**, portanto dentro de **PATH_PROJETO** navegue utilizando o terminal até **PATH_PROJETO/pca10056/s140/armgcc/** e execute 
```bash
$ make
```
Se tudo ocorrer bem, irá aparecer uma pasta chamada **_build** e dentro dela um arquivo chamado **nrf52840_xxaa.hex**.

Como para utilizar o BLE é necessário um firmware chamado **softdevice** devemos instalar este, para fazer isso esse o modo mais fácil é fazendo upload de um exemplo do nRF5 SDK, que irá armazenar o softdevice em uma região de memória do micro e o programa em outro, sendo assim, depois da primeira gravação podemos trabalhar apenas no programa que estamos desenvolvendo. Navegue até **PATH_PROJETO/hex** e copie o arquivo referente a placa que estamos programando no caso **ble_app_template_pca10056_s140.hex** e cole na pasta **_build**, com isso entre na pasta pelo terminal **_build** e execute

```bash
$ JLinkExe
$ device NRF52840_XXAA
$ si SWD
$ speed 4000
$ connect
$ erase
$ loadfile ble_app_template_pca10056_s140.hex
$ r
$ loadfile nrf52840_xxaa.hex
$ r
$ g
$ q
```

Abaixo segue alguns comandos úteis durante a utilização do JLink Commander

#### JTAG 

| Command   | Syntax                                                    | Description                                       |
|-----------|-----------------------------------------------------------|---------------------------------------------------|
| JTAGConf  | Config `<IRpre>`, `<DRpre>`                               | Set number of IR/DR bits before ARM device.       |
| speed     | speed `<freq>`|auto|adaptive, e.g. speed 2000, speed a    | Set target interface speed.                       |
| i         |                                                           | Read JTAG Id (Host CPU)                           |
| wjc       | wjc `<Data>`(hex)                                         | Write JTAG command (IR).                          |    
| wjd       | wjd `<Data64>`(hex), `<NumBits>`(dec)                     | Write JTAG data (DR).                             |
| RTAP      |                                                           | Reset TAP Controller using state machine (111110) |
| wjraw     | wjraw <NumBits(dec)>, `<tms>`, `<tdi>`                    | Write Raw JTAG data.                              |
| rt        |                                                           | Reset TAP Controller (nTRST)                      |

#### Configuração

| Command       | Syntax                                                                                                        | Description                                                           |
|---------------|---------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------|
| si            | si `<Interface>`, where `<Interface>` can be any supported target interface (e.g SWD, JTAG, ICSP, FINE, ...   | Select target interface.                                              |
| power         | power `<State>` [perm], where State is either On or Off. Example: power on perm                               | Switch power supply for target.                                       |
| wconf         | wconf `<offset>`, `<data>`                                                                                    | Write configuration byte.                                             |
| rconf         | rconf                                                                                                         | Read configuration bytes.                                             |
| license       |                                                                                                               | Shows a list of all available license commands                        |
| ipaddr        |                                                                                                               | Show/Assign IP address and subnetmask of/to the connected J-Link.     |
| gwaddr        |                                                                                                               | Show/Assign network gateway address of/to the connected J-Link.       |
| dnsaddr       |                                                                                                               | Show/Assign network DNS server address of/to the connected J-Link.    |
| conf          |                                                                                                               | Show configuration of the connected J-Link.                           |
| calibrate     |                                                                                                               | Calibrate the target current measurement.                             |
| selemu        | selemu [`<Interface0>` `<Interface1>` ...]                                                                    | Select a emulator to communicate with, from a list of all emulators                                                                                                                                               which are connected to the host The interfaces to search on,                                                                                                                                                      can be specified                                                      |
| ShowEmuList   | ShowEmuList [`<Interface0>` `<Interface1>` ...]                                                               | Shows a list of all emulators which are connected to the host.                                                                                                                                                    The interface to search on, can be specified.                         |
| VTREF         | VTREF `<ValuemV>`                                                                                             | Sets a fixed value for VTref on J-Link.                               |

#### Comandos Gerais

| Command     | Syntax                                                                                                                                    | Description                                     |
|-------------|-------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------|
| hwinfo      |                                                                                                                                           | Show hardware info                              | 
| st          |                                                                                                                                           | Show hardware status                            | 
| erase       | Erase                                                                                                                                     | Erase internal flash of selected device.        |
| loadfile    | loadfile `<filename>`, [`<addr>`] Supported extensions: *.bin, *.mot, *.hex, *.srec `<addr>` is needed for bin files only.                | Load data file into target memory.              |
| loadbin     | loadbin `<filename>`, `<addr>`                                                                                                            | Load *.bin file into target memory.             |
| g           |                                                                                                                                           | go                                              |
| savebin     | savebin `<filename>`, `<addr>`, `<NumBytes>`                                                                                              | Saves target memory into binary file.           |
| q           |                                                                                                                                           | Quit                                            |
| qc          |                                                                                                                                           | Close JLink connection and quit                 |

#### SWO 

| Command   | Description               |
|-----------|---------------------------|
| SWOSpeed  | Show supported speeds     |
| SWOStart  | Start                     |
| SWOStop   | Stop                      |
| SWOStat   | Display SWO status        |
| SWORead   | Read and display SWO data |
| SWOShow   | Read and analyze SWO data |
| SWOFlush  | Flush data                |
| SWOView   | View terminal data        |

### Black Magic Probe

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
$ target extended-remote `<PORT_GDB_SERVER>`  -> Abre a porta do Black Magic Probe
$ mon swdp_scan                             -> Procura por dispositivos plugados no computador que utilizam o protocolo SWD
$ att `<NUM_NRF52840>`                        -> Conecta no nRF52840
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
* Criar uma pasta em ***`<PATH_SKETCHBOOK_ARDUINO>`/tools/nRF5FlashSoftDevice/tool/*** e colocar o arquivo baixado dentro dela.
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
    * *Ir na pasta **`<sandeepmitry>`/hardware/nRF5/0.6.0** e abrir o arquivo **softdevices.txt** e atualizar o mesmo.*
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