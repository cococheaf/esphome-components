# Wireless M-Bus components for ESPHome

ESPHome external components for receiving Wireless M-Bus telegrams with a
CC1101, SX1276, or SX1262 radio and decoding supported meters. The supported
microcontroller families are **ESP32 and ESP8266**.

## Compatibility

| Platform | Radio | Status |
| --- | --- | --- |
| ESP8266 / Arduino | CC1101 | Built and tested with a Wemos D1 Mini, Diehl IZAR, and ESPHome 2026.11.0 |
| ESP8266 / Arduino | SX1276, SX1262 | Not supported |
| ESP32 / ESP-IDF | CC1101, SX1276, SX1262 | Retained from upstream; not retested for this fork |

Use a fixed tag in production:

```yaml
external_components:
  - source: github://cococheaf/esphome-components@v5-esp8266.3
    components: [wmbus_common, wmbus_radio, wmbus_meter]
```

Start with an example without personal network details:

- [ESP8266 / D1 Mini / CC1101 / IZAR](examples/esp8266-cc1101-izar.yaml)
- [ESP32 / CC1101 / IZAR](examples/esp32-cc1101-izar.yaml)

Read the [ESP8266 setup and migration guide](docs/esp8266-cc1101.md) before
replacing a working version 3 installation. For ESP32 radio wiring and
supported variants, see [ESP32 setup](docs/esp32.md).

## Configuration model

Version 5 uses `spi:`, `wmbus_radio:`, `wmbus_meter:`, and
`platform: wmbus_meter`. It is **not** a drop-in replacement for version 3's
`wmbus:` and `platform: wmbus` YAML. Match `meter_id` to the address
reported by the version 5 log, not automatically to the hexadecimal value in
the old configuration. For the IZAR tested here, the version 3 ID
`0x71840778` corresponds to version 5 ID `0x23537184`.

On ESP8266, CC1101 GDO2 is used for the sync-word interrupt. On ESP32, the
CC1101 example uses GDO0 for the FIFO-threshold interrupt. The ESP8266 receiver
drains the radio FIFO in ESPHome's high-frequency main loop; it does not use
the ESP32 FreeRTOS receive task. The large manufacturer-name table is omitted
on ESP8266 to conserve RAM; manufacturer codes are still available. Telegram
RSSI and LQI can be exposed as diagnostic sensors.

## Troubleshooting

- `Telegram not handled by any handler`: the radio received a frame, but no
  configured meter matched it. Check the address printed in the log, meter
  type, and (for encrypted meters) the key.
- `RX FIFO overflow`: the receiver did not drain the CC1101 quickly enough
  for that frame. Check GDO2 wiring, signal quality, and whether Wi-Fi or
  logging is consuming CPU time. An occasional warning does not prove that
  all readings are lost; verify that the total and RSSI continue updating.
- `Disconnected from API` during OTA: the device restarts while flashing.
  Confirm that it reconnects with the new ESPHome build before troubleshooting
  the radio.

For changes and known limitations, see [CHANGELOG.md](CHANGELOG.md).

Source acknowledgements and licensing notes are in [NOTICE.md](NOTICE.md).
