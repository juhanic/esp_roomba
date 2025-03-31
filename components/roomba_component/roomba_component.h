#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace roomba_component {

class RoombaComponent : public sensor::Sensor, public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
  void set_battery_sensor(sensor::Sensor *sensor) {
    battery_sensor = sensor;
  }
protected:
  sensor::Sensor *battery_sensor;
};

}  // namespace roomba_component
}  // namespace esphome