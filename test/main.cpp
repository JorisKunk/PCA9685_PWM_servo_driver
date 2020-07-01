#include "hwlib.hpp"
#include "PCA9685.hpp"

void button_count(PCA9685& pwm, const int& num){
    // Array with number of servo's that need to turn to clear the scoreboard
    std::array<int,7> clear = {0,1,2,3,4,5,6};
    // Array with number of servo's that need to turn to make number 0 on the scoreboard
    std::array<int,6> zero = {0,1,2,3,4,6};
    // Array with number of servo's that need to turn to make number 1 on the scoreboard
    std::array<int,2> one = {0,1};
    // Array with number of servo's that need to turn to make number 2 on the scoreboard
    std::array<int,5> two = {0,2,4,5,6};
    // Array with number of servo's that need to turn to make number 3 on the scoreboard
    std::array<int,5> three = {0,1,2,5,6};
    // Array with number of servo's that need to turn to make number 4 on the scoreboard
    std::array<int,4> four = {0,1,3,5};
    // Array with number of servo's that need to turn to make number 5 on the scoreboard
    std::array<int,5> five = {1,2,3,5,6};
    // Array with number of servo's that need to turn to make number 6 on the scoreboard
    std::array<int,6> six = {1,2,3,4,5,6};
    // Array with number of servo's that need to turn to make number 7 on the scoreboard
    std::array<int,4> seven = {0,1,2,3};
    // Array with number of servo's that need to turn to make number 8 on the scoreboard
    std::array<int,7> eight = {0,1,2,3,4,5,6};
    // Array with number of servo's that need to turn to make number 9 on the scoreboard
    std::array<int,6> nine = {0,1,2,3,5,6};

    // The 'halfway' pulse length count (out of 4096)
    uint16_t servo_half = 400;
    // The 'maximum' pulse length count (out of 4096)
    uint16_t servo_max = 535;

    if(num < 0 || num >10){
        for (unsigned int i = 0; i < clear.size(); i++) {
            pwm.set_servo(clear[i], 0, servo_max);
        }
    }

    for (unsigned int i = 0; i < clear.size(); i++) {
        pwm.set_servo(clear[i], 0, servo_max);
    }

    hwlib::wait_ms(400);

    switch (num) {

        case 0:
            for (unsigned int i = 0; i < zero.size(); i++) {
                pwm.set_servo(zero[i], 0, servo_half);
            }
            break;
        case 1:
            for (unsigned int i = 0; i < one.size(); i++) {
                pwm.set_servo(one[i], 0, servo_half);
            }
            break;
        case 2:
            for (unsigned int i = 0; i < two.size(); i++) {
                pwm.set_servo(two[i], 0, servo_half);
            }
            break;
        case 3:
            for (unsigned int i = 0; i < three.size(); i++) {
                pwm.set_servo(three[i], 0, servo_half);
            }
            break;
        case 4:
            for ( unsigned int i = 0; i < four.size(); i++) {
                pwm.set_servo(four[i], 0, servo_half);
            }
            break;
        case 5:
            for ( unsigned int i = 0; i < five.size(); i++) {
                pwm.set_servo(five[i], 0, servo_half);
            }
            break;
        case 6:
            for ( unsigned int i = 0; i < six.size(); i++) {
                pwm.set_servo(six[i], 0, servo_half);
            }
            break;
        case 7:
            for ( unsigned int i = 0; i < seven.size(); i++) {
                pwm.set_servo(seven[i], 0, servo_half);
            }
            break;
        case 8:
            for ( unsigned int i = 0; i < eight.size(); i++) {
                pwm.set_servo(eight[i], 0, servo_half);
            }
            break;
        case 9:
            for ( unsigned int i = 0; i < nine.size(); i++) {
                pwm.set_servo(nine[i], 0, servo_half);
            }
            break;
    }
    hwlib::wait_ms(400);
}

int main() {
    // scl pin
    auto scl = hwlib::target::pin_oc{hwlib::target::pins::scl};
    // sda pin
    auto sda = hwlib::target::pin_oc{hwlib::target::pins::sda};
    // i2c_bus with scl and sda
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{scl, sda};
    // Button pin
    auto button = hwlib::target::pin_in( hwlib::target::pins::d22);

    // Make PCA9685 object with i2c_bus and the address of the chip (0x40)
    PCA9685 pwm(i2c_bus, 0x40);
    // Reset the chip
    pwm.reset();
    // Set PWM frequentie for the chip
    pwm.set_servo_freq();

    bool button_check = false;
    int number = 0;

    while(true){
        if(number>9){
            number = 0;
        }
        if(button.read() && !button_check){
            button_count(pwm, number);
            button_check = true;
            number++;
        }
        else if(!button.read() && button_check){
            button_check = false;
        }
    }
}