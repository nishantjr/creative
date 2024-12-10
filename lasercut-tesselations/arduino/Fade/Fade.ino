
const int pin_num[3] = {9, 10, 11};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(pin_num[i], OUTPUT);
  }
}

void setLEDs(int stage){
  for (int i = 0; i < 3; i++) {
    int value = (stage + i*(256/3)) % 256;
    analogWrite(pin_num[i], value);
  }
}

int n = 0;
void loop() {
    n = (n+1) % 512;
    if (n < 256) {
        setLEDs(n);
    }
    else {
        setLEDs(265 - (n - 256));
    }
    delay(100);
}
