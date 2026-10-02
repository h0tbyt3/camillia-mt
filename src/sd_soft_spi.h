#pragma once
// Bit-banged SPI-mode SD card, mounted through FatFs and the ESP-IDF VFS so it
// presents as an ordinary fs::FS.
//
// For boards whose card slot sits on pins neither hardware SPI host can serve.
// The CrowPanel Advance 3.5 is the case: its display holds SPI3, the LoRa radio
// holds SPI2 (Arduino's global SPI), and the S3 has no third general-purpose
// host. Meshtastic drives the same slot the same way (SDCARD_USE_SOFT_SPI).
//
// Pins come from the board header: SD_SOFT_SCK, SD_SOFT_MISO, SD_SOFT_MOSI and
// SD_CS. All must be below GPIO32 -- the driver writes the low GPIO register
// directly.
#include <Arduino.h>
#include <FS.h>

// Probes the card and mounts it at /sd. False when no card answers or it has
// no readable FAT filesystem -- a card is never formatted from here.
bool sdSoftBegin();

// Unmounts and releases the drive. Safe when nothing is mounted.
void sdSoftEnd();

bool sdSoftMounted();

// The mounted card. Operations fail cleanly while it is unmounted.
fs::FS &sdSoftFs();

// Card capacity in bytes from its CSD; 0 when unmounted.
uint64_t sdSoftCardSize();

// "SDHC", "SDSC" or "MMC"; empty when unmounted.
const char *sdSoftCardTypeName();
