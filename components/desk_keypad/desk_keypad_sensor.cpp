#include "desk_keypad_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace desk_keypad {

static const char *const TAG = "desk_keypad";

void DeskKeypadSensor::setup() {
  // Nothing to do here
}

void DeskKeypadSensor::loop() {
  while (available() > 0) {
    uint8_t incomingByte = read();
    // ESP_LOGD(TAG, "Incoming byte is: %02x", incomingByte);
    
    // First byte, start of a packet
    if (incomingByte == 0x9b) {
      // Reset message length
      msg_len = 0;
      valid = false;
    }

    // Second byte defines the message length
    if (history[0] == 0x9b) {
      msg_len = (int)incomingByte;
    }

    // Third byte is message type
    if (history[1] == 0x9b) {
      msg_type = incomingByte;
    }

    // Fourth byte contains the command
    if (history[2] == 0x9b) {
      switch (incomingByte) {
        case 0x00: mReturnCommand = Command::Empty; break;
        case 0x01: mReturnCommand = Command::Up; break;
        case 0x02: mReturnCommand = Command::Down; break;
        case 0x04: mReturnCommand = Command::Preset1; break;
        case 0x08: mReturnCommand = Command::Preset2; break;
        case 0x10: mReturnCommand = Command::Preset3; break;
        case 0x20: mReturnCommand = Command::M; break;
        case 0x40: mReturnCommand = Command::Alarm; break;
      }
    }

    if (incomingByte == 0x9d && msg_type == 0x02 && msg_len == 6 && 
        mReturnCommand && mReturnCommand != lastPublished) {
      publish_state(mReturnCommand);
      ESP_LOGI(TAG, "Keypad command: %d", mReturnCommand);
      lastPublished = mReturnCommand;
    }

    // Save byte buffer to history array
    history[2] = history[1];
    history[1] = history[0];
    history[0] = incomingByte;
  }
}

}  // namespace desk_keypad
}  // namespace esphome 