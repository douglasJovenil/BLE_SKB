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

################### END Programando ###################

### JLINK

Baixar o Jlink Commander <a href="https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb" target="_blank">aqui</a>.

Após finalizar o download, instalar o pacote com o seguinte:
```bash
$ sudo dpkg -i nome_pacote_jlink.deb
```
Caso esteja instalado com sucesso, pluge o JLink conectado com o SKB501 no computador e execute o seguinte

```bash
$ JLinkExe

```


## Comandos Gerais

| Command         | Syntax                                                                                                                                    | Description                                     |
|-----------------|-------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------|
| f               |                                                                                                                                           | Firmware info                                   |
| h               |                                                                                                                                           | halt                                            |
| IsHalted        |                                                                                                                                           | Returns the current CPU state (halted / running)|
| WaitHalt        |  WaitHalt `<TimeoutMs>`                                                                                                                   | Waits until the CPU is halted or the given.                                                                                                                                                                       timeout is exceeded. Default timeout is 1000 ms |
| g               |                                                                                                                                           | go                                              |
| Sleep           | Sleep `<delay>`                                                                                                                           | Waits the given time (in milliseconds).         |
| s               | s [<NumSteps (dec)>]                                                                                                                      | Single step the target chip.                    |
| st              |                                                                                                                                           | Show hardware status                            | 
| hwinfo          |                                                                                                                                           | Show hardware info                              | 
| mem             | mem  [`<Zone>`:]`<Addr>`, `<NumBytes>` (hex)                                                                                              | Read memory.                                    |
| mem8            | mem8  [`<Zone>`:]`<Addr>`, `<NumBytes>` (hex)                                                                                             | Read  8-bit items.                              |
| mem16           | mem16 [`<Zone>`:]`<Addr>`, `<NumItems>` (hex)                                                                                             | Read 16-bit items.                              |
| mem32           | mem32 [`<Zone>`:]`<Addr>`, `<NumItems>` (hex)                                                                                             | Read 32-bit items.                              |
| w1              | w1 [`<Zone>`:]`<Addr>`, `<Data>` (hex)                                                                                                    | Write  8-bit items.                             |
| w2              | w2 [`<Zone>`:]`<Addr>`, `<Data>` (hex)                                                                                                    | Write 16-bit items.                             |
| w4              | w4 [`<Zone>`:]`<Addr>`, `<Data>` (hex)                                                                                                    | Write 32-bit items.                             |
| erase           | Erase                                                                                                                                     | Erase internal flash of selected device.        |
| wm              | wm `<NumWords>`                                                                                                                           | Write test words.                               |
| is              |                                                                                                                                           | Identify length of scan chain select register   |
| ms              | ms <Scan chain>                                                                                                                           | Measure length of scan chain.                   |
| mr              | mr                                                                                                                                        | Measure RTCK react time.                        |
| q               |                                                                                                                                           | Quit                                            |
| qc              |                                                                                                                                           | Close JLink connection and quit                 |
| r               |                                                                                                                                           | Reset target         (RESET)                    |
| rx              | rx `<DelayAfterReset>`                                                                                                                    | Reset target         (RESET).                   |
| RSetType        | RSetType `<type>`                                                                                                                         | Set the current reset type.                     |
| Regs            |                                                                                                                                           | Display contents of registers                   |
| wreg            | wreg `<RegName>`, `<Value>`                                                                                                               | Write register.                                 |
| moe             |                                                                                                                                           | Shows why CPU is halted                         |
| SetBP           |  SetBP `<addr>` [A/T] [S/H]                                                                                                               | Set breakpoint.                                 |
| SetWP           | `<Addr>` [R/W] [`<Data>` [<D-Mask>] [A-Mask]]                                                                                             | Set Watchpoint.                                 |
| ClrBP           |  ClrBP  `<BP_Handle>`                                                                                                                     | Clear breakpoint.                               |
| ClrWP           |  ClrWP  `<WP_Handle>`                                                                                                                     | Clear watchpoint.                               |
| VCatch          | VCatch `<Value>`                                                                                                                          | Write vector catch.                             |
| **loadfile**    | loadfile `<filename>`, [`<addr>`] Supported extensions: *.bin, *.mot, *.hex, *.srec `<addr>` is needed for bin files only.                | Load data file into target memory.              |
| **loadbin**     | loadbin `<filename>`, `<addr>`                                                                                                            | Load *.bin file into target memory.             |
| savebin         | savebin `<filename>`, `<addr>`, `<NumBytes>`                                                                                              | Saves target memory into binary file.           |
| verifybin       | verifybin `<filename>`, `<addr>`                                                                                                          | Verfies if the specified binary is already in the                                                                                                                                                                 target memory at the specified address.         |
| SetPC           | SetPC `<Addr>`                                                                                                                            | Set the PC to specified value.                  |
| le              |                                                                                                                                           | Change to little endian mode                    |
| be              |                                                                                                                                           | Change to big endian mode                       |
| log             | log `<filename>`                                                                                                                          | Enables log to file.                            |
| unlock          | unlock `<DeviceName>` Type unlock without `<DeviceName>` to get a list of supported device names. nRESET has to be connected              | Unlocks a device.                               |
| term            |                                                                                                                                           | Test command to visualize printf output from the                                                                                                                                                                  target device, using DCC (SEGGER DCC handler                                                                                                                                                                      running on target)                              |
| ReadAP          |                                                                                                                                           | Reads a CoreSight AP register. Note: First read                                                                                                                                                                   returns the data of the previous read. An                                                                                                                                                                         additional read of DP reg 3 is necessary to get                                                                                                                                                                   the data.                                       |
| ReadDP          |                                                                                                                                           | Reads a CoreSight DP register. Note: For SWD data                                                                                                                                                                 is returned immediately. For JTAG the data of the                                                                                                                                                                 previous read is returned. An additional read of                                                                                                                                                                  DP reg 3 is necessary to get the data.          |
| WriteAP         |                                                                                                                                           | Writes a CoreSight AP register.                 |
| WriteDP         |                                                                                                                                           | Writes a CoreSight DP register.                 |
| SWDSelect       |                                                                                                                                           | Selects SWD as interface and outputs the JTAG ->                                                                                                                                                                  SWD switching sequence.                         |
| SWDReadAP       |                                                                                                                                           | Reads a CoreSight AP register via SWD. Note:                                                                                                                                                                      First read returns the data of the previous read.                                                                                                                                                                 An additional read of DP reg 3 is necessary to                                                                                                                                                                    get the data.                                   |
| SWDReadDP       |                                                                                                                                           | Reads a CoreSight DP register via SWD. Note:                                                                                                                                                                      Correct data is returned immediately.           |
| SWDWriteAP      |                                                                                                                                           | Writes a CoreSight AP register via SWD.         |
| SWDWriteDP      |                                                                                                                                           | Writes a CoreSight DP register via SWD.         |
| Device          |                                                                                                                                           | Selects a specific device J-Link shall connect to                                                                                                                                                                 and performs a reconnect. In most cases explicit                                                                                                                                                                  selection of the device is not necessary.                                                                                                                                                                         Selecting a device enables the user to make use                                                                                                                                                                   of the J-Link flash programming functionality as                                                                                                                                                                  well as using unlimited breakpoints in flash                                                                                                                                                                      memory. For some devices explicit device                                                                                                                                                                          selection is mandatory in order to allow the DLL                                                                                                                                                                  to perform special handling needed by the device|
|   ExpDevList      | ExpDevList `<filename>`                                                                                                                 | Exports the device names from the DLL internal                                                                                                                                                                    device list to a text file.                     |
|   ExpDevListXML   | ExpDevListXML `<Filename>`                                                                                                              | Exports the device names from the DLL internal                                                                                                                                                                    device list to a text file in XML format.       |
|   PowerTrace      | PowerTrace `<LogFile>` [`<ChannelMask>` `<RefCountSel>`] `<LogFile>`: File to store power trace data to `<ChannelMask>`: 32-bit mask to specify what channels shall be enabled `<SampleFreq>`: Sampling frequency  Hz (0 == max) `<RefCountSel>`:       0: No reference count 1: Number of bytes transmitted on SWO                          | Perform power trace (not supported by all models|

## CP15

| Command 
rce        Read CP15.  Syntax: rce `<Op1>`, `<CRn>`, `<CRm>`, `<Op2>`
wce        Write CP15. Syntax: wce `<Op1>`, `<CRn>`, `<CRm>`, `<Op2>`, `<Data>`
---- ICE -------------
Ice        Show state of the embedded ice macrocell (ICE breaker)
ri         Read Ice reg.  Syntax: ri `<RegIndex>`(hex)
wi         Write Ice reg. Syntax: wi `<RegIndex>`, `<Data>`(hex)
---- TRACE -----------
TClear     TRACE - Clear buffer
TSetSize   TRACE - Set Size of trace buffer
TSetFormat TRACE - SetFormat
TSR        TRACE - Show Regions (and analyze trace buffer)
TStart     TRACE - Start
TStop      TRACE - Stop
---- SWO -------------
SWOSpeed   SWO - Show supported speeds
SWOStart   SWO - Start
SWOStop    SWO - Stop
SWOStat    SWO - Display SWO status
SWORead    SWO - Read and display SWO data
SWOShow    SWO - Read and analyze SWO data
SWOFlush   SWO - Flush data
SWOView    SWO - View terminal data
---- PERIODIC --------
PERConf    PERIODIC - Configure
PERStart   PERIODIC - Start
PERStop    PERIODIC - Stop
PERStat    PERIODIC - Display status
PERRead    PERIODIC - Read and display data
PERShow    PERIODIC - Read and analyze data
---- File I/O --------
fwrite     Write file to emulator
fread      Read file from emulator
fshow      Read and display file from emulator
fdelete    Delete file on emulator
fsize      Display size of file on emulator
flist      List directory on emulator
SecureArea Creates/Removes secure area on probe
---- Test ------------
TestHaltGo   Run go/halt 1000 times
TestStep     Run step 1000 times
TestCSpeed   Measure CPU speed.
             Parameters: [`<RAMAddr>`]
TestWSpeed   Measure download speed into target memory.
             Parameters:  [`<Addr>` [`<Size>`]]
TestRSpeed   Measure upload speed from target memory.
             Parameters: [`<Addr>` [`<Size>`] [`<NumBlocks>`]]
TestNWSpeed  Measure network download speed.
             Parameters: [`<NumBytes>` [`<NumReps>`]]
TestNRSpeed  Measure network upload speed.
             Parameters: [`<NumBytes>` [`<NumReps>`]]
---- JTAG ------------
JTAGConf   Set number of IR/DR bits before ARM device.
             Syntax: Config `<IRpre>`, `<DRpre>`
speed      Set target interface speed. Syntax: speed `<freq>`|auto|adaptive, e.g. speed 2000, speed a
i          Read JTAG Id (Host CPU)
wjc        Write JTAG command (IR). Syntax: wjc `<Data>`(hex)
wjd        Write JTAG data (DR). Syntax: wjd `<Data64>`(hex), `<NumBits>`(dec)
RTAP       Reset TAP Controller using state machine (111110)
wjraw      Write Raw JTAG data. Syntax: wjraw <NumBits(dec)>, `<tms>`, `<tdi>`
rt         Reset TAP Controller (nTRST)
---- JTAG-Hardware ---
c00        Create clock with TDI = TMS = 0
c          Clock
tck0       Clear TCK
tck1       Set   TCK
0          Clear TDI
1          Set   TDI
t0         Clear TMS
t1         Set   TMS
trst0      Clear TRST
trst1      Set   TRST
r0         Clear RESET
r1         Set   RESET
---- Connection ------
usb        Connect to J-Link via USB.  Syntax: usb `<port>`, where port is 0..3
ip         Connect to J-Link ARM Pro or J-Link TCP/IP Server via TCP/IP.
           Syntax: ip `<ip_addr>`
---- Configuration ---
si         Select target interface. Syntax: si `<Interface>`,
           where `<Interface>` can be any supported target interface (e.g SWD, JTAG, ICSP, FINE, ...
power      Switch power supply for target. Syntax: power `<State>` [perm],
           where State is either On or Off. Example: power on perm
wconf      Write configuration byte. Syntax: wconf `<offset>`, `<data>`
rconf      Read configuration bytes. Syntax: rconf
license    Shows a list of all available license commands
ipaddr     Show/Assign IP address and subnetmask of/to the connected J-Link.
gwaddr     Show/Assign network gateway address of/to the connected J-Link.
dnsaddr    Show/Assign network DNS server address of/to the connected J-Link.
conf       Show configuration of the connected J-Link.
calibrate  Calibrate the target current measurement.
selemu     Select a emulator to communicate with,
           from a list of all emulators which are connected to the host
           The interfaces to search on, can be specified
             Syntax: selemu [`<Interface0>` `<Interface1>` ...]
ShowEmuList Shows a list of all emulators which are connected to the host.
            The interfaces to search on, can be specified.
             Syntax: ShowEmuList [`<Interface0>` `<Interface1>` ...]
VTREF       Sets a fixed value for VTref on J-Link.
              Syntax: VTREF `<ValuemV>`


| Nome      | Idade | 
|-----------|-------|
| Douglas   | 10    |