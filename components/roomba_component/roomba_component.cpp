#include "esphome/core/log.h"
#include "roomba_component.h"

namespace esphome {
namespace roomba_component {

static const char *TAG = "roomba_component.sensor";

void RoombaComponent::setup() {

}

void RoombaComponent::update() {

}

void RoombaComponent::loop() {

}

void RoombaComponent::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty UART sensor");
}

}  // namespace roomba_component
}  // namespace esphome