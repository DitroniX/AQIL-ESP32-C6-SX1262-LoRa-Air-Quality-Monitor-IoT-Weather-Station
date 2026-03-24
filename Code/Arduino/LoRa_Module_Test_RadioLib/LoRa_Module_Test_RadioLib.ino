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

// save transmission states between loops
int transmissionState = RADIOLIB_ERR_NONE;

// flag to indicate transmission or reception state
bool transmitFlag = false;

// flag to indicate that a packet was sent or received
volatile bool operationDone = false;

ICACHE_RAM_ATTR

void setFlag(void) {
  // we sent or received a packet, set the flag
  operationDone = true;
}

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

  // Initialise SPI
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

  // Initialise RED LED on GP22
  pinMode(LED_Red, OUTPUT);

  // initialize SX1262 with default settings
  Serial.print(F("[SX1262] Initializing ... "));
  digitalWrite(LED_Green, HIGH);

  // int state = radio.begin();
  // int state = radio.begin(868.0);
  int state = radio.begin(868.0, 125.0, 9, 7, RADIOLIB_SX126X_SYNC_WORD_PRIVATE, 10, 8, 1.6, false);

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

  // set the function that will be called when new packet is received
  radio.setDio1Action(setFlag);

  Serial.println("\nAQIL - LoRa Air Quality Monitor IoT Weather Station");
}

// **************** LOOP ****************
void loop() {

  // Heartbeat RED LED
  digitalWrite(LED_Red, HIGH);
  delay(50);
  digitalWrite(LED_Red, LOW);
  delay(1000);
}
