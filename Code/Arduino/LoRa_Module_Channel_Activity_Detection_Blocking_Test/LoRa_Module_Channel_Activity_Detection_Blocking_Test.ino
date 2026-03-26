/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  AQIL - ESP32-C6 SX1262 LoRa Air Quality Monitor IoT Weather Station

  Example Code, to demonstrate and test the AQIL - LoRa Comms TX Test

  Further information, details and examples can be found on our website and also GitHub wiki pages:
  * ditronix.net
  * github.com/DitroniX
  * github.com/DitroniX/AQIL-ESP32-C6-SX1262-LoRa-Air-Quality-Monitor-IoT-Weather-Station
  * github.com/DitroniX/AQIL-ESP32-C6-SX1262-LoRa-Air-Quality-Monitor-IoT-Weather-Station/wiki
  * hackster.io/DitroniX/aqil-esp32-c6-sx1262-scd41-lora-air-quality-monitor-iot-wx-d7a332

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  For board configuration, see https://github.com/DitroniX/AQIL-ESP32-C6-SX1262-LoRa-Air-Quality-Monitor-IoT-Weather-Station/wiki/Arduino-IDE

  Further information, details and examples maybe found on github.com/DitroniX

  Further information and documentation on the excellent RadioLib from Jan Gromeš, maybe found https://github.com/jgromes/RadioLib
  Many thanks to Jan for his support on this Radio library.
*/

// REMEMBER TO PUT THE LORA ENABLE JUMPER ON - OR THIS CODE WILL NOT WORK.

// IMPORTANT: ENSURE AN ANTENNA, OR RF LOAD, IS CONNECTED TO THE LORA MODULE - BEFORE TX.  OTHERWISE DAMAGE TO THE LORA MODULE COULD RESULT.

// Libraries
#include <RadioLib.h>
#include <SPI.h>

/*
  RadioLib SX126x Blocking Channel Activity Detection Example

  This example uses SX1262 to scan the current LoRa channel and detect ongoing LoRa transmissions.

  Unlike SX127x CAD, SX126x can detect any part of LoRa transmission, not just the preamble.

  Other modules from SX126x family can also be used.

  Using blocking CAD is not recommended, as it will lead to significant amount of timeouts, inefficient use of processor time and can some miss packets!
  Instead, interrupt CAD is recommended.

  For default module settings, see the wiki page
  https://github.com/jgromes/RadioLib/wiki/Default-configuration#sx126x---lora-modem

  For full API reference, see the GitHub Pages
  https://jgromes.github.io/RadioLib/
*/

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** OUTPUTS ****************
#define LED_Red 22    // Red LED
#define LED_Green 21  // Gren LED
#define LED_Blue 23   // Blue LED

// Pin definitions
#define SPI_MOSI 18
#define SPI_MISO 20
#define SPI_SCK 19
#define SPI_CS 14

#define E22_IRQ 4
#define E22_NRST 8
#define E22_BUSY 5

SX1262 radio = new Module(SPI_CS, E22_IRQ, E22_NRST, E22_BUSY);

// **************** SETUP ****************
void setup() {
  Serial.begin(115200);

  // Configures the specified LED GPIO as outputs
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Blue, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);

  // initialize SX1262 FSK modem with default settings
  Serial.print(F("\n[SX1262] Initializing ... "));
  digitalWrite(LED_Green, HIGH);

  int state = radio.begin();

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
    digitalWrite(LED_Green, LOW);
  } else {
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Red, HIGH);
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) {
      delay(10);
    }
  }

  Serial.println("\nAQIL - LoRa Air Quality Monitor IoT Weather Station");
}

// **************** LOOP ****************
void loop() {
  Serial.print(F("[SX1262] Scanning channel for LoRa transmission ... Channel Activity Detection (CAD)"));
  digitalWrite(LED_Green, HIGH);

  // start scanning current channel
  int state = radio.scanChannel();

  if (state == RADIOLIB_LORA_DETECTED) {
    // LoRa preamble was detected
    Serial.println(F("detected!"));

  } else if (state == RADIOLIB_CHANNEL_FREE) {
    // no preamble was detected, channel is free
    Serial.println(F("channel is free!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
  
  digitalWrite(LED_Green, LOW);

  // Blue
  digitalWrite(LED_Blue, HIGH);
  delay(500);
  digitalWrite(LED_Blue, LOW);

  delay(2000);
}