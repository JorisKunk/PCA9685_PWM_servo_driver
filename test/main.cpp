#include "hwlib.hpp"
#include "PCA9685.hpp"

// this is a test to see of the PCA9685 class works properly
int main() {
    // scl pin
    auto scl = hwlib::target::pin_oc{hwlib::target::pins::scl};
    // sda pin
    auto sda = hwlib::target::pin_oc{hwlib::target::pins::sda};
    // i2c_bus with scl and sda
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{scl, sda};

    // Make PCA9685 object with i2c_bus and the address of the chip (0x40)
    PCA9685 pwm(i2c_bus, 0x40);
    // Reset the chip
    pwm.reset();
    // Set PWM frequentie for the chip
    pwm.set_servo_freq();

    uint8_t servo_num = 0;

    // turn servo 0
    pwm.set_servo(servo_num, 0, 400);
    hwlib::wait_ms(500);
    pwm.set_servo(servo_num, 0, 500);
}