#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

#define ROOMBA_READ_TIMEOUT 200

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
  void flush() {
    while(available()) {
      read();
    }
  }
private:
typedef enum {
  Sensors7to26					= 0,  //00
  Sensors7to16					= 1,  //01
  Sensors17to20					= 2,  //02
  Sensors21to26					= 3,  //03
  Sensors27to34					= 4,  //04
  Sensors35to42					= 5,  //05
  Sensors7to42					= 6,  //06
  SensorBumpsAndWheelDrops		= 7,  //07
  SensorWall						= 8,  //08
  SensorCliffLeft					= 9,  //09
  SensorCliffFrontLeft			= 10, //0A
  SensorCliffFrontRight			= 11, //0B
  SensorCliffRight				= 12, //0C
  SensorVirtualWall				= 13, //0D
  SensorOvercurrents				= 14, //0E
  //SensorUnused1					= 15, //0F
  //SensorUnused2					= 16, //10
  SensorIRByte					= 17, //11
  SensorButtons					= 18, //12
  SensorDistance					= 19, //13
  SensorAngle						= 20, //14
  SensorChargingState				= 21, //15
  SensorVoltage					= 22, //16
  SensorCurrent					= 23, //17
  SensorBatteryTemperature		= 24, //18
  SensorBatteryCharge				= 25, //19
  SensorBatteryCapacity			= 26, //1A
  SensorWallSignal				= 27, //1B
  SensoCliffLeftSignal			= 28, //1C
  SensoCliffFrontLeftSignal		= 29, //1D
  SensoCliffFrontRightSignal		= 30, //1E
  SensoCliffRightSignal			= 31, //1F
  SensorUserDigitalInputs			= 32, //20
  SensorUserAnalogInput			= 33, //21
  SensorChargingSourcesAvailable	= 34, //22
  SensorOIMode					= 35, //23
  SensorSongNumber				= 36, //24
  SensorSongPlaying				= 37, //25
  SensorNumberOfStreamPackets		= 38, //26
  SensorVelocity					= 39, //27
  SensorRadius					= 40, //28
  SensorRightVelocity				= 41, //29
  SensorLeftVelocity				= 42, //2A
} SensorCode;

typedef enum {
  ChargeStateNotCharging				= 0,
  ChargeStateReconditioningCharging	= 1,
  ChargeStateFullCharging				= 2,
  ChargeStateTrickleCharging			= 3,
  ChargeStateWaiting					= 4,
  ChargeStateFault					= 5,
} ChargeState;

typedef enum {
  ResetCmd        = 7,   //07
  StartCmd        = 128, //80
  StopCmd         = 173, //AD
  SafeCmd         = 131, //83
  FullCmd         = 132, //84
  CleanCmd        = 135, //87
  SpotCmd         = 134, //86
  DockCmd         = 143, //8F
  PowerCmd        = 133, //85
  DriveCmd        = 137, //89
  MotorsCmd       = 138, //8A
  LEDAsciiCMD     = 164, //A4
  SongCmd         = 140, //8C
  PlayCmd         = 141, //8D
  SensorsListCmd  = 149, //95
} Commands;      
          
bool getSensorsList(uint8_t* packetIDs, uint8_t numPacketIDs, uint8_t* dest, uint8_t len){
  write(149);
  write(numPacketIDs);
  write_array(packetIDs, numPacketIDs);
  return getData(dest, len);
}

bool getData(uint8_t* dest, uint8_t len) {
  while (len-- > 0) {
    unsigned long startTime = millis();
    while (!available()) {
      yield();
      // Look for a timeout
      if (millis() > startTime + ROOMBA_READ_TIMEOUT) 
        return false;
    }
    *dest++ = read();
  }
  return true;
}

};

}  // namespace roomba_component
}  // namespace esphome