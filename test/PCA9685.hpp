/// @mainpage
/// Made by Joris Kunkeler \n \n
/// This library can be used to communicate with the PCA9685 chip over i2c.
/// The PCA9685 chip has 16 PWM channels wich can be used to drive servo's.
/// To use one or multiple servo's you can make a PCA9685 object.
/// Then to make the chip ready for use, you have to use the PCA9685::reset() and PCA9685::set_servo_freq() functions.
/// This library uses hwlib for arduino i2c interaction and arduino pins.
/// For more information take a look at hwlib here: https://github.com/wovo/hwlib \n \n
/// If you want to look at an example on how to use the PCA9685 class you should take a look at the main file in my Github repository:
/// https://github.com/JorisKunk/PCA9685_PWM_servo_driver/blob/master/main.cpp.
/// I made my own DIY 7 segment mechanical display wich I use as a scoreboard.
/// To make the scoreboard I used a PCA9685 chip, 7 micro servo's, and a breadboard with a button on it.
/// To make you're score go up by one just press the button once.


#ifndef PCA9685_HPP
#define PCA9685_HPP

#include "hwlib.hpp"

/// @brief  Class with members and functions for interacting with PCA9685 PWM chip
class PCA9685 {
private:
    const hwlib::i2c_bus& i2c_bus;
    /// PCA9685 chip address
    const uint_fast8_t PCA9685_addr;
    /// MODE1 register address
    const uint8_t MODE1_addr = 0x00;
    /// MODE1 restart bit
    const uint8_t MODE1_restart = 0x80;
    /// MODE1 sleep bit
    const uint8_t MODE1_sleep = 0x10;
    /// MODE1 auto increment bit
    const uint8_t MODE1_ai = 0x20;
    /// SERVO_ON_L register address
    const uint8_t SERVO_ON_L = 0x06;
    /// Prescale byte calculated with 50 Hz servo updates and 25 MHz clock: (25000000 / (50 * 4096)) - 1 = 121 = 0111 1001 = 0x79
    const uint8_t prescale = 0x79;
    /// Prescale register address
    const uint8_t prescale_adr = 0xFE;

    /// @brief  Reads data in MODE1 register
    ///
    /// @details
    /// First a write transaction with the adress of the MODE1 register, then a read transaction to read the data
    uint8_t read_MODE1(){
        // Read MODE1 register
        {
            hwlib::i2c_write_transaction writetrans = ((hwlib::i2c_bus * )(&i2c_bus))->write(PCA9685_addr);
            writetrans.write(MODE1_addr);
        }
        uint8_t MODE1_data;
        {
            hwlib::i2c_read_transaction readtrans = ((hwlib::i2c_bus * )(&i2c_bus))->read(PCA9685_addr);
            readtrans.read(MODE1_data);
        }
        return MODE1_data;
    }

public:
    /// @brief
    /// PCA9685 constructor
    /// @details
    /// This constructor initializes the i2c_bus and the address of the PCA9685 chip
    PCA9685(const hwlib::i2c_bus& i2c_bus,const uint_fast8_t& PCA9685_addr);

    /// @brief
    /// Sends a reset command to the PCA9685 chip over i2c
    /// @details
    /// Sleep bit is set to 0 in MODE1 register of the PCA9685 chip
    void reset();

    /// @brief
    /// Enables restart for the PCA9685 chip
    /// @details
    /// The restartbit in the MODE1 register will be set to 0 by writing a 1
    void set_restart_bit();

    /// @brief
    /// Puts the PCA9685 chip in sleepmode
    /// @details
    /// The sleepbit in the MODE1 register will be set to 1 so that the PCA9685 chip will be set to sleepmode
    void set_sleep_bit();

    /// @brief Gets the PCA9685 chip out of sleepmode
    ///
    /// @details
    /// The sleepbit in the MODE1 register will be cleared so that the PCA9685 chip will get out of sleepmode
    void clear_sleep_bit();

    /// @brief
    /// Enables Auto-Increment
    /// @details
    /// The AI bit in the MODE1 register will be set to 1 so that Auto-Increment is enabled
    void set_ai_bit();

    /// @brief
    /// Writes the prescale byte to the PRE_SCALE register
    /// @details
    /// The prescale byte wil be written to the PRE_SCALE register
    void set_prescale_byte();

    /// @brief
    /// Sets the PWM freqency for the entire chip
    /// @details
    /// The PCA9685 chip will be set to sleepmode so that the prescale byte can be set in the PRE_SCALE register, then awakes the chip when it's done
    void set_servo_freq();

    /// @brief  Sets the PWM output of one of the PCA9685 pins
    ///@param num One of the PWM output pins, from 0 to 15
    ///@param on At what point in the 4096-part cycle to turn the PWM output ON
    ///@param off At what point in the 4096-part cycle to turn the PWM output OFF
    void set_servo(const uint8_t& num, const uint16_t& on, const uint16_t& off);
};

#endif //PCA9685_HPP