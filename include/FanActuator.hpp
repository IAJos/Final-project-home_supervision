#ifndef FANACTUATOR_H
#define FANACTUATOR_H

#include <Arduino.h>

/// @brief This class is used to activate or deactivate a fan.
class FanActuator
{
    private:
        /// @brief This property represents the pin to which 
        ///        our fan will be connected.
        uint8_t p_fanActuator;

    public:
        /// @brief FanActuator class constructor
        /// @param fanActuator Represents the pin to which 
        ///                    our fan will be connected.
        FanActuator(uint8_t fanActuator);

        /// @brief FanActuator class destructor
        ~FanActuator();

        /// @brief This method activates the fan
        void enableFan();

        /// @brief This method stops the fan
        void desableFan();
};

#endif // FANACTUATOR_H