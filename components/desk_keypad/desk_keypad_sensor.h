#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include <bitset>

namespace esphome {
namespace desk_keypad {

class DeskKeypadSensor : public sensor::Sensor, public Component, public uart::UARTDevice {
 public:
  enum Command {
    Up = 1,
    Down = 2,
    Preset1 = 3,
    Preset2 = 4,
    Preset3 = 5,
    M = 6,
    Alarm = 7,
    Empty = 8
  };
  
  Command mReturnCommand = Command::Empty;
  Command lastPublished = Command::Empty;
  uint8_t history[3] = {0, 0, 0};

  int msg_len = 0;
  uint8_t msg_type = 0;
  bool valid = false;

  float get_setup_priority() const override { return setup_priority::DATA; }

  void setup() override;
  void loop() override;
};

}  // namespace desk_keypad
}  // namespace esphome 