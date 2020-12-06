#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial bt(12, 13);

Servo left;
Servo right;

void setup()                                 // Built-in initialization block
{
  pinMode(10, INPUT);  pinMode(9, OUTPUT);   // Left IR LED & Receiver
  pinMode(3, INPUT);  pinMode(2, OUTPUT);   // Right IR LED & Receiver
  Serial.begin(9600);                        // Set data rate to 9600 bps
  bt.begin(9600);

  left.attach(13);
  right.attach(12);
}

byte isFire = 0; // false
double th; // 온도

void loop()                                  // Main loop auto-repeats
{
  th = Thermister(analogRead(A0));
  Serial.println("TH");
  Serial.println(th);
  if (th >= 35 && !isFire) { //if isFire : false
    backward(800);
    isFire = 1;
    pause(0);
  }
  if (isFire) {
    fireAlarm();
  }
  else {
    int irLeft = irDetect(9, 10, 38000);       // Check for object
    int irRight = irDetect(2, 3, 38000);       // Check for object
    delay(100);

    if (irLeft == 0 && irRight == 1) {
      backward(300); RotateRight(300);
    }
    else if (irRight == 0 && irLeft == 1) {
      backward(300); RotateLeft(300);
    }
    else forward(100);
  }
  if (Serial.read() == '1') isFire = 0;
  if (bt.available() != 0) {
    if (bt.read() == '1') isFire = 0; //Button clicked
  }
  delay(100);                                // 0.1 second delay
}

// IR Object Detection Function
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}

void fireAlarm() {
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);  // Delay to finish tone
  bt.write('1'); //Alert via bluetooth
}

double Thermister(int RawADC) {
  double t;
  t = log(((10240000 / RawADC) - 10000));
  t = 1 / (0.001129148 + (0.000234125 * t) + (0.0000000876741 * t * t * t));
  t = t - 273.15;
  return t;
}

void forward(int mtime) { //delay 넣는 곳
  right.write(1300);
  left.write(1700);
  delay(mtime);
}
void backward(int mtime) {
  left.write(1300);
  right.write(1700);
  delay(mtime);
}
void pause(int mtime) {
  left.write(1500);
  right.write(1500);
  delay(mtime);
}
void RotateRight(int mtime) {
  left.write(1700);
  right.write(1700);
  delay(mtime);
}
void RotateLeft(int mtime) {
  left.write(1300);
  right.write(1300);
  delay(mtime);
}
