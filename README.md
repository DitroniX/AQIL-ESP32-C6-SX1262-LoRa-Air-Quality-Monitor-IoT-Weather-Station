# AQIL - ESP32-C6 SX1262 LoRa Air Quality Monitor IoT Weather Station
**Supporting STEM Electronic Internet of Things & Home Automation Technology for Smart Energy Monitoring**

[![DitroniX WiKi Pages](https://github.com/DitroniX/AQIL-ESP32-C6-SX1262-LoRa-Air-Quality-Monitor-IoT-Weather-Station/blob/main/Datasheets%20and%20Information/GitHub%20WiKi.png?raw=true)](https://github.com/DitroniX/AQIL-ESP32-C6-SX1262-LoRa-Air-Quality-Monitor-IoT-Weather-Station/wiki)

[**For Latest Project Updates - Click Here**](https://github.com/DitroniX/AQIL-ESP32-C6-SX1262-LoRa-Air-Quality-Monitor-IoT-Weather-Station?tab=readme-ov-file#updates)

**AQIL** is an ESP32-C6 (2.4GHz), based SX1262 LoRa Air Quality Monitor IoT Weather Station

![AQIL Features Preview](https://github.com/DitroniX/AQIL-ESP32-C6-SX1262-LoRa-Air-Quality-Monitor-IoT-Weather-Station/blob/main/Datasheets%20and%20Information/AQIL%20-%20Features.png)


**NEW SDK BOARD** - Availability planned for March 2026.

## History

The Compact Weather IoT Monitor boards such as the [CWX](https://github.com/DitroniX/CWX-Compact-Weather-Station) series, and [AQIX](https://github.com/DitroniX/AQIX-Air-Quality-Monitor-IoT-Weather-Station), have been popular, especially for education purposes  and home use.

Taking the CWX and AQIX concept, a new LoRa enabled version has been designed.  This is called AQIL.

## Features

High Precision Digital Environmental Monitor Sensors.

The **AQIL** board offers the following main features:

-   **Espressif ESP32-C6**
    -   WiFi, Bluetooth, Zigbee and Thread
-   **EByte E22-900MM22S**
    -   LoRa (LoRaWAN), SX1262 module for 850 MHz through to 930 MHz
-   **Sensirion SCD40 or SCD41**
    -   High Accuracy CO2 Sensor
    -   [SCD40](https://sensirion.com/products/catalog/SCD40)  – 400 to 2000 ppm, Accuracy ±50.0 ppm ±5.0 %m.v (Home)
    -   [SCD41](https://sensirion.com/products/catalog/SCD41)  – 400 to 5000 ppm, Accuracy ±50.0 ppm ±2.5 %m.v (Home, Office, Industry)
-   **Bosch BME280**
    -   High Precision Barometric Pressure, Relative Humidity and Temperature
    -   **Barometric Pressure** 300…1100 hPa (millibar)
        – Accuracy ±0.25%
        – which is equivalent to 1m at 400m height change
        – RMS Noise 0.2 Pa
        – which is equivalent to 1.7 cm
        – **Temperature** -40 to 85°C
        – Temperature coefficient offset ±1.5Pa/K.
        – which is equivalent to ±12.6cm at 1 °C temperature change
        – **Humidity**
        – 0 to 100 %
        – Accuracy tolerance ±3% relative humidity
        – Hysteresis ≤2% relative humidity
-   **Ambient Light Sensor**
    -   SFH2440, providing spectral sensitivity adapted to human eye sensitivity
    -   Std. Light A; T = 2856 K Minimum 7 nA/lx
    -   Spectral range of sensitivity λ10% typically 400 to 690 nm
    -   Wavelength of max sensitivity λS max typically 620 nm
    -   ESP32-C6 ADC provides light voltage reading
-   **EEPROM P24C64C**
    -   64Kbit storage
    -   AT24C64 64Kbit
    -   On-board Data Logging
    -   On-board Parameters
    -   Firmware setup user parameters and configuration
-   **USB C**
    -   With UART for easy programming and development
    -   Board powering during development or use.
    -   Type C USB Connector
    -   CH340K USB UART 2Mbps Transceiver
    -   Easy programming. Select ‘ESP32C3 Dev Module’
    -   BAUD rate up to 921600 to speed up Flashing
    -   Serial Monitoring Debug and Remote Logging
    -   Power Can Be Taken from USB 5V (when Flashing).
-   **FET Output**
    -   External Relay or Sounder.
    -   GPIO or PWM
-   **OneWire (Dallas) Interface**
    -   External Sensors such as Soil Temperature Probe (DS18S20)
    -   Dallas OneWire Interface for External Temperatures
-   **I2C Interface Display**
    -   OLED Display
    -   PCB 4 Pin Header Connector
-   **I2C Interface Sensors**
    -   External Sensors such as Soil Monitoring
    -   PCB 4 Pin Header Connector
-   **Buttons**
    -   Reset
    -   User (Program or GP9 Detect)
-   **Battery Voltage Monitor**
    -   ESP32-C6 ADC provides battery voltage reading
-   **3V3 LDO**
    -   AMS1117 LDO allowing use of external DC input 4.5V to 15V
-   **LED**
    -   RGB, Ext DC LED
-   **Compact Design and Easy to Use**
    -   Board Size63 x 51mm
    -   4 x M3 mounting holes
    -   Operating Ambient Temperature -10 to +60 °
    -   Optional Conformal Coating – on request.
    -   Designed to fit into a Waterproof Clear Cover Enclosure

Power can be via external 5 to 15V DC, or using a CR123A 3V Lithium battery. CR123A Battery is not a rechargeable.

This board could also be powered from a Solar Panel.

## Updates

-   26-02-20 - In Beta Development 
-   26-02-01 - Project Launched


## **Purchase**

Via our DitroniX.net [Shop](https://ditronix.net/shop/) 

or this board will be added to eBay once in stock.

[![Display-Type-B](https://raw.githubusercontent.com/DitroniX/DitroniX/main/Files/DitroniX.net%20STEM%20IoT%20eBay.jpg?raw=true)](https://www.ebay.co.uk/usr/ditronixuk)

Our STEM SDK boards and accessories are available from our online shops on [eBay](https://www.ebay.co.uk/usr/ditronixuk) 

## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE and PlatformIO)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Maidstone, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

Life is one long exciting learning curve, help others by setting the seed to knowledge.

![DitroniX Supporting STEM](https://hackster.imgix.net/uploads/attachments/1606838/stem_ambassador_-_100_volunteer_badge_edxfxlrfbc1_bjdqharfoe1_xbqi2KUcri.png?auto=compress%2Cformat&w=540&fit=max)
