import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    UNIT_EMPTY,
    ICON_COUNTER,
)

DEPENDENCIES = ["uart"]

desk_keypad_ns = cg.esphome_ns.namespace("desk_keypad")
DeskKeypadSensor = desk_keypad_ns.class_(
    "DeskKeypadSensor", sensor.Sensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        DeskKeypadSensor,
        unit_of_measurement=UNIT_EMPTY,
        icon=ICON_COUNTER,
        accuracy_decimals=0,
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(DeskKeypadSensor),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
