#include "esphome/core/log.h"
#include "roomba_component.h"

namespace esphome {
namespace roomba_component {

static const char *TAG = "roomba_component.sensor";

void RoombaComponent::setup() {

}

void RoombaComponent::update() {
    if (this->battery_sensor != nullptr) {
        this->battery_sensor->publish_state(100.0);
    }
}

void RoombaComponent::loop() {

}

void RoombaComponent::dump_config(){
    ESP_LOGCONFIG(TAG, "roomba component");
}

}  // namespace roomba_component
}  // namespace esphome