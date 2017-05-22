/* @file motor.cpp
*
* This file contains the driver for the BTN7960B motor driver that actuates the
* linear actuator driven brake.
*
*/
//------------------------------------------------------------------------------

#include "brake.h"

//------------------------------------------------------------------------------

BRAKE::BRAKE(PinName extend, PinName retract, PinName enable, PinName position):
             _extend(extend), _retract(retract), _enable(enable, 0), _position(position)
{

    _extend.period_us(50);
    _extend.pulsewidth_us(0);
    _retract.period_us(50);
    _retract.pulsewidth_us(0);
    _enable = 1;

}

//------------------------------------------------------------------------------

void BRAKE::setPosition(float percent)
{

    if(percent > 0.75){
        percent = 0.75;
    }

    if(percent < 0.03){
        percent = 0.03;
    }

    if(_position.read() < percent - 0.01){
        while(_position.read() < percent){
            _retract.pulsewidth_us(0);
            _extend.pulsewidth_us(50);
        }
        _extend.pulsewidth_us(0);
    }
    else {
        while(_position.read() > percent + 0.01){
            _retract.pulsewidth_us(50);
            _extend.pulsewidth_us(0);
        }
        _retract.pulsewidth_us(0);
    }

}

float BRAKE::getPosition()
{
    return _position.read();
}

//------------------------------------------------------------------------------

void BRAKE::stop()
{
    _enable = 0;
    _extend.pulsewidth_us(0);
    _retract.pulsewidth_us(0);

}