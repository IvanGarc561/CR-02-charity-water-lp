#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
              //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

// TODO: complete nums
// the index is also the digit it represents
// eg: nums[0]="0", nums[9]="9", nums[15]="f"
// bits layout:   gfedcba   (REVERSE ORDER!)
int nums[16] = {0b0111111, // 0
                0b0000110, // 1
                0b1011011, // 2
                0b1001111, // 3 
                0b1100110, // 4
                , // 5
                , // 6
                , // 7
                , // 8
                , // 9
                , // a
                , // b
                , // c 
                , // d
                , // e
                  // f 
                }; 

//TODO: complete outNum()
void outNum(int num){
	PORTB = ; // depends on your wiring. Assign bits (e-a), which are bits (4-0) from nums[] to register PORTB
  PORTD = ; // Assign bits (g & f) which are bits 6 & 5 of nums[] to register PORTD
}

enum states {} state; //TODO: finish the enum for the SM


void Tick() {
  // Declare any static variables here

  // State Transistions
  //TODO: complete transitions 
  switch(state) {

  }

  // State Actions
  //TODO: complete transitions
  switch(state) {

  }

}



int main(void)
{
  //TODO: initialize all outputs and inputs
  DDRB     = ;
  PORTB    = ;
  
  DDRC    = ;
  PORTC   = ;

  DDRD   = ;
  PORTD  = ;

  //TODO: initialize your state
  state = ;
  
  while (1) {
    Tick();
  }
}