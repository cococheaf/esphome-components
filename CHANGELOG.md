# Changelog

## v5-esp8266.3

- Limit supported microcontroller families to ESP32 and ESP8266.
- Remove the copied ESP32 core override and product-specific example files.
- Provide neutral ESP32/ESP8266 examples, setup guides, and source notices.
- Update component maintainer metadata and repository documentation.

## v5-esp8266.2

- Keep the ESP8266 CC1101 receive loop at high frequency and drain FIFO data
  promptly, reducing missed frames while ESPHome handles other work.
- Use the CC1101 sync-word interrupt on GDO2 in the ESP8266 example.
- Verify compilation with ESPHome 2026.11.0 and live Diehl IZAR reception on a
  Wemos D1 Mini. Occasional FIFO overflows remain possible under load.

## v5-esp8266.1

- Change the ESP8266 example to use an early CC1101 GDO2 interrupt.

## Initial ESP8266 support

- Add an ESP8266/Arduino CC1101 receive path alongside the upstream
  ESP32/ESP-IDF implementation.
- Expose CC1101 RSSI and LQI as meter sensor fields.
- Reduce ESP8266 RAM usage by omitting expanded manufacturer names.

Earlier version 5 history is retained in the Git commit history.
