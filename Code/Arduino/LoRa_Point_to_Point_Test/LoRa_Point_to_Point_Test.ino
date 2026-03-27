/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  AQIL - ESP32-C6 SX1262 LoRa Air Quality Monitor IoT Weather Station

  Example Code, to demonstrate and test the AQIL - LoRa Comms TX/RX Test

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
#include <Adafruit_NeoPixel.h>
#include "WiFi.h"  // Used only to get the unique number

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** INPUTS ****************
#define User_Button 9  // GPIO 9

// **************** OUTPUTS ****************
#define LED_Red 22    // Red LED
#define LED_Green 21  // Gren LED
#define LED_Blue 23   // Blue LED

// Pin definitions
#define SPI_MOSI 18
#define SPI_MISO 20
#define SPI_SCK 19
#define SPI_CS 14

// AQIL
#define E22_IRQ 4
#define E22_NRST 8
#define E22_BUSY 5

SX1262 radio = new Module(SPI_CS, E22_IRQ, E22_NRST, E22_BUSY);

//Example Values.  Leave 00 between P2P testing.  Just compile as is, to all devices under test.
// uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// uint8_t devEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// uint8_t appKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint32_t counter = 0;
uint8_t payload[64];  // buffer for receive

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

  // Configure GPIO Inputs
  pinMode(User_Button, INPUT_PULLUP);

  // Used only to get the unique number
  WiFi.mode(WIFI_MODE_STA);

  // initialize SPI
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);

  // initialize SX1262 FSK modem with default settings
  Serial.print(F("\n[SX1262] Initializing ... "));

  digitalWrite(LED_Green, HIGH);

  radio.XTAL = true;

  int state = radio.begin(868.0,  // frequency (MHz)
                          125.0,  // bandwidth (kHz)
                          9,      // spreading factor
                          5,      // coding rate
                          RADIOLIB_SX126X_SYNC_WORD_PRIVATE,
                          20,    // TX power (dBm)
                          8,     // preamble length
                          0.0);  // TCXO voltage (use 0.0 if no TCXO)

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

  Serial.println(F("Ready!\n"));

  Serial.print("AQIL MAC Address:\t");
  Serial.println(WiFi.macAddress());

  Serial.println("\nAQIL - LoRa Air Quality Monitor IoT Weather Station");
  Serial.println("AQIL - LoRa Point-to-Point Messaging");
  Serial.println("Press USER Button to send Message\n");
}

// **************** LOOP ****************
void loop() {

  // LEDs Default Off State
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);

  // Check for Button Press
  if (digitalRead(User_Button) == LOW) {

    Serial.print("Button Pressed\t");
    sendPacket();
  }

  // Receive Packet if Payload Available
  receivePacket();

  // Heartbeat
  digitalWrite(LED_Red, HIGH);
  delay(50);
  digitalWrite(LED_Red, LOW);
}

// ====================== RECEIVE PACKET ======================
void receivePacket() {

  // Try to receive a packet
  int state = radio.receive(payload, sizeof(payload) - 1);  // leave 1 byte for null terminator

  if (state == RADIOLIB_ERR_NONE) {

    digitalWrite(LED_Green, HIGH);

    // Packet received successfully
    payload[sizeof(payload) - 1] = '\0';  // ensure null termination

    Serial.print(F("Received: "));
    Serial.print(F(" RSSI: "));
    Serial.print(radio.getRSSI());
    Serial.print(F(" dBm   SNR: "));
    Serial.print(radio.getSNR());
    Serial.print(F(" dB\tRX: "));
    Serial.println((char*)payload);
    delay(500);
  }
}

// ====================== SEND PACKET ======================
void sendPacket() {

  // Build a simple text message
  snprintf((char*)payload, sizeof(payload), "Hello from AQIL %08X  #%lu", WiFi.macAddress(), counter);

  Serial.print(F("Sending: \t\t\tTX: "));
  Serial.println((char*)payload);

  int state = radio.transmit(payload, strlen((char*)payload));

  if (state == RADIOLIB_ERR_NONE) {
    digitalWrite(LED_Blue, HIGH);
  } else {
    digitalWrite(LED_Red, HIGH);
    Serial.print(F("Sending Failed. Code "));
    Serial.println(state);
    while (true) {
      delay(10);
    }
  }

  counter++;
  delay(500);
}