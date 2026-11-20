# ESP32 setup

ESP32 with ESP-IDF supports the CC1101, SX1276, and SX1262 radio backends.
The [CC1101 / IZAR example](../examples/esp32-cc1101-izar.yaml) uses a generic
ESP32 DevKit pinout. Adapt pins for your board and radio module.

For CC1101 on ESP32, connect the configured `irq_pin` to **GDO0** (FIFO
threshold), unlike the ESP8266 example, which uses GDO2. Configure SPI,
`wmbus_radio:`, and at least one `wmbus_meter:`. Use only the components
required by your YAML in `external_components:`.

For SX1276, use its DIO1 as `irq_pin` and configure `reset_pin`. For SX1262,
configure `reset_pin`, `irq_pin`, and optionally `busy_pin`, `rx_gain`,
`rf_switch`, and `has_tcxo` according to the module. These radio backends
were retained from the version 5 codebase but were not hardware-retested as
part of the ESP8266 work.
