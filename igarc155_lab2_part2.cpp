#include <avr/io.h>
#include <util/delay.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

enum states {INIT, WAIT, INC, DEC, HOLD} state;

void Tick() {
  static unsigned char val = 0;
  unsigned char shifted;

  // State Transitions
  switch(state) {
    case INIT:
      state = WAIT;
      break;

    case WAIT:
      if (GetBit(PIND, 7)) {
        state = INC;
      } else if (GetBit(PIND, 6)) {
        state = DEC;
      } else {
        state = WAIT;
      }
      break;

    case INC:
      state = HOLD;
      break;

    case DEC:
      state = HOLD;
      break;

    case HOLD:
      if (!GetBit(PIND, 6) && !GetBit(PIND, 7)) {
        state = WAIT;
      }
      break;

    default:
      state = INIT;
      break;
  }

  // State Actions
  switch(state) {
    case INIT:
      break;

    case WAIT:
      break;

    case INC:
      val++;
      if (val > 15) {
        val = 0;
      }
      break;

    case DEC:
      if (val == 0) {
        val = 15;
      } else {
        val--;
      }
      break;

    case HOLD:
      shifted = (val << 2) & 0x3C;
      PORTB = (PORTB & ~0x3C) | shifted;
      _delay_ms(500);
      break;
  }
}

int main(void)
{
  // PB2–PB5 as output (LEDs)
  DDRB = 0x3C;
  PORTB = 0x00;

  // PD6 and PD7 as input (buttons)
  DDRD = DDRD & ~(1 << 6) & ~(1 << 7);
  PORTD = PORTD | (1 << 6) | (1 << 7); // Enable pull-ups

  state = INIT;

  while (1) {
    Tick();
  }
}
