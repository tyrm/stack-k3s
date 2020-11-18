#include <avr/io.h>
#include <util/delay.h>

#define DELAYTIME 1000 // milliseconds

// Basically Linear Ramp Speed
#define FANSPEED0 255
#define FANSPEED1 225
#define FANSPEED2 196
#define FANSPEED3 167
#define FANSPEED4 138
#define FANSPEED5 109
#define FANSPEED6 80
#define FANSPEED7 51

static inline void initTimers(void) {
  // TCCR0A: Fast PWM mode, PWM output on OCR2A
  // on: 7-COM0A1, 1-WGM01, 0-WGM00
  //         76543210
  TCCR0A = 0b10000011;

  // TCCR0B: PWM Freq = F_CPU/8/256
  // on: 1-CS01
  //         76543210
  TCCR0B = 0b00000010;

}

int main(void) {
  uint8_t last_reading=0;
  uint8_t this_reading=0;

  // -------- Inits --------- //
  initTimers();

  DDRB  = 0b00000001; // Set all pins to input except pin 0
  PORTB = 0b00001110; // Enable pullups on pin 1, 2, and 3

  // ------ Event loop ------ //
  while (1) {
    // Read three bits from input pins
    this_reading = (PINB & 0b00001110) >> 1;

    if (last_reading != this_reading) {
      switch (this_reading) {
        case 0:
          OCR0A = FANSPEED0;
          break;
        case 1:
          OCR0A = FANSPEED1;
          break;
        case 2:
          OCR0A = FANSPEED2;
          break;
        case 3:
          OCR0A = FANSPEED3;
          break;
        case 4:
          OCR0A = FANSPEED4;
          break;
        case 5:
          OCR0A = FANSPEED5;
          break;
        case 6:
          OCR0A = FANSPEED6;
          break;
        case 7:
          OCR0A = FANSPEED7;
          break;
      }

      last_reading = this_reading;
    }

    _delay_ms(DELAYTIME);
  }

  return 0;
}
