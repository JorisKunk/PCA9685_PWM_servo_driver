#include "PCA9685.hpp"
#include <array>

PCA9685::PCA9685(const hwlib::i2c_bus& i2c_bus,const uint_fast8_t& PCA9685_addr):
        i2c_bus(i2c_bus),
        PCA9685_addr(PCA9685_addr)
{}

void PCA9685::reset() {
    clear_sleep_bit();
    set_restart_bit();
}

void PCA9685::set_restart_bit(){
    uint8_t restart = read_MODE1() & (MODE1_restart);
    uint8_t restartwrite[2] = {MODE1_addr, restart};

    // Set restart bit to 0 by writing 1 in MODE1 register
    {
        hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus * )(&i2c_bus))->write(PCA9685_addr);
        writetrans.write(restartwrite, 2);
    }
}

void PCA9685::set_sleep_bit(){
    uint8_t sleep =  read_MODE1() | MODE1_sleep; //Set sleep bit 1
    uint8_t sleepwrite[2] = {MODE1_addr, sleep};

    // Set sleep bit to 1 in MODE1 register
    {
        hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus * )(&i2c_bus))->write(PCA9685_addr);
        writetrans.write(sleepwrite,2);
    }
}

void PCA9685::clear_sleep_bit(){
    uint8_t wakeup = read_MODE1() & ~(MODE1_sleep);
    uint8_t wakeupwrite[2] = {MODE1_addr, wakeup};

    // Clear sleep bit in MODE1 register
    {
        hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus * )(&i2c_bus))->write(PCA9685_addr);
        writetrans.write(wakeupwrite,2);
    }
    hwlib::wait_ms(5);
}

void PCA9685::set_ai_bit(){
    hwlib::wait_ms(5);
    uint8_t ai = read_MODE1() | MODE1_ai;
    uint8_t aiwrite[2] = {MODE1_addr, ai};

    // Set auto increment bit in MODE1 register.
    {
        hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus * )(&i2c_bus))->write(PCA9685_addr);
        writetrans.write(aiwrite,2);
    }
}

void PCA9685::set_prescale_byte(){
    uint8_t prescalewrite[2] = {prescale_adr, prescale};

    // Set the prescale byte in the prescale register
    {
        hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus * )(&i2c_bus))->write(PCA9685_addr);
        writetrans.write(prescalewrite,2);
    }
}

void PCA9685::set_servo_freq() {
    set_sleep_bit();

    set_prescale_byte();

    clear_sleep_bit();

    set_ai_bit();

}

void PCA9685::set_servo(const uint8_t& num, const uint16_t& on, const uint16_t& off) {
    {
        hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus * )(&i2c_bus))->write(PCA9685_addr);
        writetrans.write(SERVO_ON_L + 4 * num);
        writetrans.write(on);
        writetrans.write(on >> 8);
        writetrans.write(off);
        writetrans.write(off >> 8);
    }
}
