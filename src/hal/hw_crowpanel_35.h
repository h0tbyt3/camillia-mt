#pragma once
// ════════════════════════════════════════════════════════════════════════════
// hal/hw_crowpanel_35.h — Elecrow CrowPanel Advance 3.5" HMI (ESP32-S3)
//
// The Meshtastic bundle (sold by Muzi Works / Elecrow): ESP32-S3-WROOM-1-N16R8
// (16 MB flash, 8 MB OPI PSRAM) with:
//   • 3.5" ILI9488 IPS TFT, 320×480 native portrait, run here as 480×320
//   • GT911 capacitive touch on I2C (SDA 15 / SCL 16)
//   • SX1262 LoRa module in the J8/J9 expansion slot
//   • No keyboard, trackball or free user button (GPIO0 is LoRa NSS)
//
// Pins follow Meshtastic's support and Elecrow's V1.0 schematic:
//   meshtastic/firmware variants/esp32s3/elecrow_panel/variant.h (CROW_SELECT 1)
//   meshtastic/firmware variants/esp32s3/elecrow_panel/platformio.ini
//     [env:elecrow-adv-35-tft]  (LGFX_* display and touch flags)
//   meshtastic/firmware boards/crowpanel.json
//   Elecrow-RD/CrowPanel-Advance-HMI-ESP32-AI-Display
//     3.5/schematic/ESP32 Display 3.5 inch V1.0.sch
//
// Expansion slot, viewed from above (2.4/2.8/3.5"):
//   DIO1/IO1 o   o IO2/NRESET
//   SCK/IO10 o   o IO16/NC
//   MISO/IO9 o   o IO15/NC
//   MOSI/IO3 o   o NC/DIO2
//        3V3 o   o IO46/BUSY
//        GND o   o IO0/NSS
//      5V/NC o   o NC/DIO3
//           J9   J8
// ════════════════════════════════════════════════════════════════════════════

// ── Power & board peripherals ────────────────────────────────────────────────
#define BOARD_POWERON             -1
// GPIO8 drives the I2S amp's MCLK; Meshtastic abuses it as a PWM buzzer. Left
// off until someone confirms on hardware that it is wanted.
#define BOARD_BUZZER              -1
#define BOARD_VEXT_ENABLE         -1
#define BOARD_VEXT_ON_LEVEL     HIGH

// ── TFT display — ILI9488 320×480 ───────────────────────────────────────────
// SPI3_HOST, not the SPI2_HOST Meshtastic uses: here the LoRa radio is driven
// through Arduino's global SPI, which is SPI2 (FSPI) on the S3. Meshtastic puts
// its radio on SPI1/HSPI instead, so it never had the clash.
#define TFT_SPI_HOST          SPI3_HOST
#define TFT_SPI_SCK               42
#define TFT_SPI_MISO              -1   // Write-only
#define TFT_SPI_MOSI              39
#define TFT_SPI_3WIRE          false
#define TFT_SPI_WRITE_HZ    40000000   // Meshtastic runs 60 MHz; start conservative
#define TFT_SPI_READ_HZ     16000000
#define TFT_CS                    40
#define TFT_DC                    41
#define TFT_RST                   -1
#define TFT_BL                    38
#define TFT_BL_INVERT          false
#define TFT_BL_FREQ            44000
#define TFT_BL_PWM_CH              7
#define TFT_BRIGHTNESS_DEFAULT   160
#define TFT_PANEL_WIDTH          320
#define TFT_PANEL_HEIGHT         480
#define TFT_INVERT              true
#define TFT_RGB_ORDER          false

// ── LoRa — SX1262 in the expansion slot ─────────────────────────────────────
#define LORA_SPI_SCK              10
#define LORA_SPI_MISO              9
#define LORA_SPI_MOSI              3
#define LORA_CS                    0
#define LORA_DIO1                  1
#define LORA_RST                   2
#define LORA_BUSY                 46
#define LORA_FEM_POWER_PIN        -1
#define LORA_FEM_ENABLE_PIN       -1
#define LORA_FEM_TX_MODE_PIN      -1
// IO45 selects the expansion slot: LOW routes it to LoRa, HIGH to the
// microphone. Meshtastic: SENSOR_POWER_CTRL_PIN 45 / SENSOR_POWER_ON LOW.
#define LORA_POWER_ENABLE_PIN     45
#define LORA_POWER_ENABLE_LEVEL  LOW

// ── Storage — microSD over software SPI, internal LittleFS as fallback ───────
// Elecrow's V1.0 schematic connects J5 to GPIO5 (SCLK), GPIO4 (DO),
// GPIO6 (DI), and GPIO7 (CS). These match Meshtastic's software-SPI flags.
//
// Bit-banged because both general SPI hosts are taken: the display has SPI3
// and the radio has SPI2. storageBegin() mounts the card when one answers and
// otherwise falls back to the littlefs partition in partitions_16mb_fs.csv.
// The choice is made at mount time; a card inserted later is picked up on the
// next boot.
#define SD_CS                      7
#define HAS_SD_CARD                1
#define HAS_SD_SOFT_SPI            1
#define SD_SOFT_SCK                5
#define SD_SOFT_MISO               4
#define SD_SOFT_MOSI               6
#define HAS_INTERNAL_FS            1
#define INTERNAL_FS_PARTITION  "littlefs"

// ── No keyboard ──────────────────────────────────────────────────────────────
#define HAS_KEYBOARD               0
#define KB_SDA                    -1
#define KB_SCL                    -1
#define KB_ADDR                 0x00
#define KB_INT                    -1

// ── Capacitive touch — GT911 ─────────────────────────────────────────────────
#define HAS_TOUCH                  1
#define TOUCH_SDA                 15
#define TOUCH_SCL                 16
#define TOUCH_ADDR              0x5D
#define TOUCH_INT                 47
#define TOUCH_RST                 48
#define TOUCH_I2C_PORT             0
#ifndef TOUCH_POLL_ENABLED
#define TOUCH_POLL_ENABLED         1
#endif

// ── No trackball ─────────────────────────────────────────────────────────────
#define HAS_TRACKBALL              0
#define TBALL_UP                  -1
#define TBALL_DOWN                -1
#define TBALL_LEFT                -1
#define TBALL_RIGHT               -1
#define TBALL_CLICK               -1

// ── No free user button: BOOT (GPIO0) doubles as LoRa NSS ───────────────────
#define USER_BUTTON_PIN           -1
#define USER_BUTTON_ACTIVE_LEVEL LOW

// ── GPS — optional module on the UART1 connector ────────────────────────────
// Nothing ships attached. GPS_RX is the pin this board receives on.
#define HAS_GPS                    1
#define GPS_RX                    18
#define GPS_TX                    17
#define GPS_BAUD                9600

// ── No battery sense ─────────────────────────────────────────────────────────
// Meshtastic's variant declares no battery ADC for this board.
#define BATT_ADC_PIN              -1
#define BATT_DIV                1.0f
#define BATT_SENSE_ENABLE_PIN     -1
#define BATT_SENSE_ENABLE_LEVEL  LOW

// ── Radio TCXO voltage ───────────────────────────────────────────────────────
// Meshtastic: SX126X_DIO3_TCXO_VOLTAGE 3.3, DIO2 as RF switch.
#define MESH_TCXO_V             3.3f

// ── Memory / display geometry ────────────────────────────────────────────────
#define HAS_PSRAM                  1
#define DEVICE_LCD_PORTRAIT_W    320
#define DEVICE_LCD_PORTRAIT_H    480
#define DEVICE_LCD_LANDSCAPE_W   480
#define DEVICE_LCD_LANDSCAPE_H   320
