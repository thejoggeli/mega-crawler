#include "Servo.h"


Servo::Servo(Stream& stream, uint8_t id) : servo(stream, id) {

}

void Servo::SetAngle(float angle, float seconds){

    uint8_t time = (uint8_t)(seconds * 100.0f);
    uint16_t position = (uint16_t)(angle/PI*512.0f+511.0f);
    position = max(0, min(1023, position));
    servo.setPosition(position, time);

}