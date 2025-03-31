import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import ICON_EMPTY, UNIT_PERCENT, CONF_ID

CONF_BATTERY_SENSOR = "battery_percentage_sensor"

DEPENDENCIES = ["uart"]

roomba_component_ns = cg.esphome_ns.namespace("roomba_component")
RoombaComponent = roomba_component_ns.class_(
    "RoombaComponent", cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RoombaComponent),
    cv.Optional(CONF_BATTERY_SENSOR): sensor.sensor_schema(
        unit_of_measurement=UNIT_PERCENT,
        accuracy_decimals=0,
        icon=ICON_EMPTY,
    )
}).extend(cv.polling_component_schema("60s")).extend(uart.UART_DEVICE_SCHEMA)



async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if bat_config := config.get(CONF_BATTERY_SENSOR):
        battery_sensor = await sensor.new_sensor(bat_config)
        cg.add(var.set_battery_sensor(battery_sensor))
