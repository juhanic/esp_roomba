#include "esphome/core/log.h"
#include "roomba_component.h"

namespace esphome {
namespace roomba_component {

static const char *TAG = "roomba_component.sensor";

void RoombaComponent::setup() {

}

void RoombaComponent::update() {
    uint16_t batteryCharge;
    uint16_t batteryCapacity;

    flush();

    uint8_t sensors[] = {
        SensorBatteryCharge,
        SensorBatteryCapacity,
    };
    uint8_t values[] = { 0, 0, 0, 0 };
    bool success = getSensorsList(sensors, sizeof(sensors), values, sizeof(values));
    if (!success) {
        ESP_LOGE(TAG, "Failed to get battery sensors");
        return;
    }
    batteryCharge = values[0] * 256 + values[1];
    batteryCapacity = values[2] * 256 + values[3];
    ESP_LOGD(TAG, "Battery charge: %d", batteryCharge);
    ESP_LOGD(TAG, "Battery capacity: %d", batteryCapacity);
    
    float batteryLevel = 100.0 * ((1.0*batteryCharge) / (1.0*batteryCapacity));
    ESP_LOGD(TAG, "Battery level: %f", batteryLevel);
    if (this->battery_sensor != nullptr) {
        this->battery_sensor->publish_state((float)batteryCharge / (float)batteryCapacity * 100.0);
    }
}

void RoombaComponent::loop() {

}

void RoombaComponent::dump_config(){
    ESP_LOGCONFIG(TAG, "roomba component");
}

}  // namespace roomba_component
}  // namespace esphome