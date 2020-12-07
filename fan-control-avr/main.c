#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Pin Connections
// PB0 - OC0A - Fan
#define FANPIN PB0
// PB1 - INT0 - Clock input
#define CLOCKPIN PB1
// PB2 - GPIO - Data Input
#define DATAPIN PB2
// PB3 - PCINT- Latch
#define LATCHPIN PB3

volatile uint8_t pwm_value = 0;

// Clock Pin
ISR(INT0_vect) {
  // shift bits one to the left
  pwm_value = pwm_value << 1;

  // set bit 0 to value of pin 2
  if (PINB & (1 << DATAPIN)) {
    pwm_value |= 1;
  }
}

// Latch Pin
ISR(PCINT0_vect) {
  if (PINB & (1 << LATCHPIN)) {
      OCR0A = pwm_value;
  }
}

static inline void initTimers(void) {
  // TCCR0A: Fast PWM mode, PWM output on OCR2A
  // on: 7-COM0A1, 1-WGM01, 0-WGM00
  //          76543210
  TCCR0A |= 0b10000011;

  // TCCR0B: PWM Freq = F_CPU/8/256
  // on: 1-CS01
  //          76543210
  TCCR0B |= 0b00000100;

}

static inline void initInterupts(void) {
  // GIMSK: Enable INT0, Enable PCINT
  // on: 6-INT0, 5-PCIE
  //         76543210
  GIMSK |= 0b01100000;

  // MCUCR: Interupt on rising edge of clock
  // on: 1-ISC01, 0-ISC00
  //         76543210
  MCUCR |= 0b00000011;

  // PCMSK: Enable PCINT on pin 3
  // on: 3-PCINT3
  //         76543210
  PCMSK |= 0b00001000;

}

int main(void) {

  // -------- Inits --------- //
  initTimers();
  initInterupts();

  DDRB  = 0b00000001; // Set all pins to input except pin 0
  PORTB = 0b00001110; // Enable pullups on pin 1, 2, and 3

  // ------ Event loop ------ //
  while (1) {
    cli();
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
  }

  return 0;
}
