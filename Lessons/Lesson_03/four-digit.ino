// the start of the pins used for A-G - must be sequential
int segmentStart = 2;

// the start of the common pins - must be sequential
int digitStart = 10;

// this code can use either polarity of display.
// true if common is high when ON, otherwise false.
boolean commonAnode = false;

// the number of digits your display has.
int numDigits = 4;

void setup() {
  // Enable all A-G and DP and outputs, 
  // set them to OFF 
  for(int i=0;i<8;++i) {
    pinMode(segmentStart + i, OUTPUT);
    digitalWrite(segmentStart + i, commonAnode?1:0);
  }
  
  // Setup all the common pins, initially OFF.
  for(int i=0;i<numDigits;++i) {
    pinMode(digitStart + i, OUTPUT);
    digitalWrite(digitStart + i, commonAnode?0:1);
  }
}

void loop() {
  // display a number on the 4-digit display.
  int amount = 1234;
  
  for(int i=(numDigits-1);i>=0;--i) {
    // find the current digit, which is in the low 4 bits
    int digit = amount % 10;
    
    writeDigitToDisplay(digit);
    
    // enable the right digit for display
    digitalWrite(digitStart + i, commonAnode?1:0);
    
    // short delay between changes.
    delay(1);
    // Turn of the digit
    digitalWrite(digitStart + i, commonAnode?0:1);
    
    // get the next digit.
    amount = amount / 10;
    
    //rinse, and repeat
  }
}

// Now we define the bits that are on and off
// for each segment, These are used in the
// function below to turn the correct segments on.
int dig[16] = {
// bits     6543210
// digits   abcdefg
          0b1111110,//0
          0b0110000,//1
          0b1101101,//2
          0b1111001,//3
          0b0110011,//4
          0b1011011,//5
          0b1011111,//6
          0b1110000,//7
          0b1111111,//8
          0b1111011,//9
          0b1110111,//a
          0b0011111,//b
          0b1001110,//c
          0b0111101,//d
          0b1001111,//e
          0b1000111 //f
};

void writeDigitToDisplay(int digit) {
  digit = (digit & 0x0f);
  // iterate through each bit
  for(int i=0;i<7;++i) {
    // isolate the current bit in the loop.
    int currentBit = (1<<(6-i));

    // check if the bit is on, and invert for
    // commonhigh if needed.
    int bitOn = (currentBit&dig[digit])!=0;
    if(commonAnode) {
      bitOn = !bitOn;
    }
    
    // and lastly set the bit
    digitalWrite(segmentStart+i, bitOn);
  }
}