#include <avr/io.h>
#include <util/delay.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

// Segment display not used for LED shift, so nums[] is skipped here
// You can add it if you plan to display numbers

enum states {INIT, WAIT, INCREMENT, DECREMENT, HOLD} state;

void Tick() {
  static signed char ledStep = 0;

  switch(state) {
    case INIT:
      ledStep = 0;
      state = WAIT;
      break;

    case WAIT:
      if (GetBit(PIND, 7)) {
        state = INCREMENT;
      } else if (GetBit(PIND, 6)) {
        state = DECREMENT;
      } else {
        state = WAIT;
      }
      break;

    case INCREMENT:
      state = HOLD;
      break;

    case DECREMENT:
      state = HOLD;
      break;

    case HOLD:
      if (!GetBit(PIND, 7) && !GetBit(PIND, 6)) {
        state = WAIT;
      }
      break;

    default:
      state = INIT;
      break;
  }

  switch(state) {
    case INIT:
      break;

    case WAIT:
      break;

    case INCREMENT:
      ledStep++;
      if (ledStep > 3) ledStep = 3;
      break;

    case DECREMENT:
      ledStep--;
      if (ledStep < 0) ledStep = 0;
      break;

    case HOLD:
      PORTB = PORTB & ~0x3C; // Clear PB2–PB5
      PORTB = PORTB | (1 << (ledStep + 2));
      _delay_ms(500);
      break;
  }
}

int main(void)
{
  // PB2–PB5 outputs
  DDRB = 0x3C;
  PORTB = 0x00;

  // PD6, PD7 inputs
  DDRD = DDRD & ~(1 << 6) & ~(1 << 7);
  PORTD = PORTD | (1 << 6) | (1 << 7); // Enable pull-up resistors

  state = INIT;

  while (1) {
    Tick();
  }
}
