int latchPin = 4;
int clockPin = 7;
int dataPin = 8;  // SSD pins

const unsigned char ssdlut[] = {0b00111111, 0b00000110,
0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101,
0b00000111, 0b01111111, 0b01101111};

const unsigned char anodelut[] = { 0b00000001, 0b00000010, 0b00000100, 0b00001000 };

long nr = 0;
long ts = 0;
long start = 0;

#define BTN1 A1
#define BTN2 A2
#define BTN3 A3

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  // The three pins connected to
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  // the shift register must be output pins
}

bool run = false;

void loop() {
  if (!digitalRead(BTN1)) {
    start = millis();
    run = true;
    while (!digitalRead(BTN1)) {}
  } else if (!digitalRead(BTN2)) {
    run = false;
    while (!digitalRead(BTN2)) {}
  } else if (!digitalRead(BTN3)) {
    run = false;
    nr = 0;
    while (!digitalRead(BTN3)) {}
  }

  if (run)
    nr = millis() - start;

  unsigned char digits[4];
  digits[3] = nr / 10 % 10;
  digits[2] = nr / 100 % 10;
  digits[1] = nr / 1000 % 10;
  digits[0] = nr / 10000 % 10;

  for (char i = 0; i <= 3; i++) {
    unsigned char digit = digits[i];          // the current digit
    unsigned char cathodes = ~ssdlut[digit];  // The
    //cathodes of the current digit, we’ll
    //negate the value from the original LUT
    digitalWrite(latchPin, LOW);  // Activate the latch to
    //allow writing
    shiftOut(dataPin, clockPin, MSBFIRST, cathodes);  //
    //shift out the cathode byte
    shiftOut(dataPin, clockPin, MSBFIRST, anodelut[i]);
    // shift out the anode byte
    digitalWrite(latchPin, HIGH);  // De-activate the latch
    //signal
    delay(2);
    // Short wait
  }
}