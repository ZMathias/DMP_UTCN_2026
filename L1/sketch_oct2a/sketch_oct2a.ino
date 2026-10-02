#define BTN_PIN1 4

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN1, INPUT_PULLUP);
  DDRA = 0b11111111;
}

char stat = 1;

void loop() {
  int dir = digitalRead(BTN_PIN1);

  if (dir) {
    stat = stat << 1;
    if (stat > (1 << 2)) stat = 1;
  }
   else {
    stat = stat >> 1;
    if (stat == 0) stat = (1 << 2);
  }
  
  if (stat == (1 << 3)) {
    stat = 0;
  }

  PORTA = stat;

  delay(200);
}
