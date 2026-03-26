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
  RadioLib SX126x Spectrum Scan Example

  This example shows how to perform a spectrum power scan using SX126x.

  The output is in the form of scan lines, each line has 33 power bins.

  First power bin corresponds to -11 dBm, the second to -15 dBm and so on.

  Higher number of samples in a bin corresponds to more power received at that level.

  To show the results in a plot, run the Python script
  RadioLib/extras/SX126x_Spectrum_Scan/SpectrumScan.py

  WARNING: This functionality is experimental and requires a binary patch to be uploaded to the SX126x device. There may be some undocumented side effects!

  For default module settings, see the wiki page
  https://github.com/jgromes/RadioLib/wiki/Default-configuration#sx126x---lora-modem

  For full API reference, see the GitHub Pages
  https://jgromes.github.io/RadioLib/
*/

// this file contains binary patch for the SX1262
#include <modules/SX126x/patches/SX126x_patch_scan.h>

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

  int state = radio.beginFSK();

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

  // Upload a patch to the SX1262 to enable spectral scan
  
  // NOTE: this patch is uploaded into volatile memory, and must be re-uploaded on every power up

  Serial.print(F("[SX1262] Uploading patch ... "));
  digitalWrite(LED_Green, HIGH);

  state = radio.uploadPatch(sx126x_patch_scan, sizeof(sx126x_patch_scan));

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

  // Configure scan bandwidth to 234.4 kHz and disable the data shaping
  Serial.print(F("[SX1262] Setting scan parameters ... "));
  digitalWrite(LED_Green, HIGH);

  state = radio.setRxBandwidth(234.3);

  state |= radio.setDataShaping(RADIOLIB_SHAPING_NONE);

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
  Serial.print(F("[SX1262] Starting Spectral Scan ... "));
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Red, HIGH);

  // start spectral scan
  // number of scans in each line is 2048
  // number of samples: 2048 (fewer samples = better temporal resolution)
  int state = radio.spectralScanStart(2048);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

  // wait for spectral scan to finish
  while (radio.spectralScanGetStatus() != RADIOLIB_ERR_NONE) {
    delay(10);
  }

  // read the results
  uint16_t results[RADIOLIB_SX126X_SPECTRAL_SCAN_RES_SIZE];
  state = radio.spectralScanGetResult(results);
  if (state == RADIOLIB_ERR_NONE) {
    // we have some results, print it
    Serial.print("SCAN ");
    for (uint8_t i = 0; i < RADIOLIB_SX126X_SPECTRAL_SCAN_RES_SIZE; i++) {
      Serial.print(results[i]);
      Serial.print(',');
    }
    Serial.println(" END");
  }

  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Red, LOW);

  // Blue
  digitalWrite(LED_Blue, HIGH);
  delay(500);
  digitalWrite(LED_Blue, LOW);

  delay(2000);
}