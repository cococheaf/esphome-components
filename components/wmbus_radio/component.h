#pragma once

#include <functional>

#ifdef USE_ESP32
#include "freertos/FreeRTOS.h"
#endif

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"

#include "esphome/components/spi/spi.h"
#include "esphome/components/wmbus_common/wmbus.h"

#include "packet.h"
#include "transceiver.h"

namespace esphome {
namespace wmbus_radio {

class Radio : public Component {
public:
  void set_radio(RadioTransceiver *radio) { this->radio = radio; };

  void setup() override;
  void loop() override;
  void receive_frame();
  void handle_packet(Packet *packet);

  void add_frame_handler(std::function<void(Frame *)> &&callback);

protected:
#ifdef USE_ESP32
  static void wakeup_receiver_task_from_isr(TaskHandle_t *arg);
  static void receiver_task(Radio *arg);
  TaskHandle_t receiver_task_handle_{nullptr};
  QueueHandle_t packet_queue_{nullptr};
#else
  static void wakeup_receiver_from_isr(Radio *arg);
  volatile bool frame_ready_{false};
  uint32_t last_refresh_ms_{0};
#endif

  RadioTransceiver *radio{nullptr};

  std::vector<std::function<void(Frame *)>> handlers_;
};
} // namespace wmbus_radio
} // namespace esphome
