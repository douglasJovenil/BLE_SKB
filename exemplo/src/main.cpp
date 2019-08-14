#include <BLEPeripheral.h>
#include <Arduino.h>
#include "pinout.h"
#include <SPI.h>

#include "nrf.h"

BLEPeripheral blePeripheral = BLEPeripheral();
BLEService ledService = BLEService("19b10000e8f2537e4f6cd104768a1214");
BLECharCharacteristic switchCharacteristic = BLECharCharacteristic("19b10001e8f2537e4f6cd104768a1214", BLERead | BLEWrite);

uint8_t PINS[] = { PIN_3, PIN_4, PIN_5, PIN_7, PIN_8, 
               PIN_9,  PIN_11, PIN_12, PIN_13, PIN_15, 
               PIN_17, PIN_18, PIN_19, PIN_23, PIN_24 };

int const MAX_PIN = (sizeof(PINS) / sizeof(PINS[0]));
int const const_delay = 500;

void setup() {
  // set advertised local name and service UUID
  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);

  // begin initialization
  blePeripheral.begin();

  // Inicializa os pinos
  for (int i = 0; i < MAX_PIN; i++) pinMode(PINS[i], OUTPUT);
}

void loop() {
  BLECentral central = blePeripheral.central();
  bool state = false;

  if (central) {
    while (central.connected()) {
      // central still connected to peripheral
      if (switchCharacteristic.written()) {
        // central wrote new value to characteristic, update LED
        if (switchCharacteristic.value() == '1') {
          state = true;
        } else {
          state = false;
        }
      }
      for (int i = 0; i < MAX_PIN; i++) digitalWrite(PINS[i], state);
    }
  }
}