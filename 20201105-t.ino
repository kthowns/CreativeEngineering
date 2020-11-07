#include <SoftwareSerial.h>
SoftwareSerial Bt(10, 11);
void setup() {
  // put your setup code here, to run once:
  Bt.begin(9600);
  Serial.begin(9600);
}
int flag = 0;
int i = 0;
int inten;
void loop() {
  // put your main code here, to run repeatedly:
  char ch;
  inten = analogRead(A0);
  Serial.println(inten);
  //  char cch = Serial.read(); //testing in serial
  //  Serial.println(cch);
  if (inten < 350) i = 524;
  if (Bt.available()) flag = 1;
  if (flag == 1) {
    ch = Bt.read();
    switch (ch) {
      case '1':
        tone(4, 523 + i, 200); //c
        Bt.write(523 + i);
        break;
      case '2':
        if (i > 0) i += 64;
        tone(4, 587 + i, 200); //d
        Bt.write(587 + i);
        break;
      case '3':
        if (i > 0) i += 136;
        tone(4, 659 + i, 200); //e
        Bt.write(659 + i);
        break;
      case '4':
        if (i > 0) i += 175;
        tone(4, 698 + i, 200); //f
        Bt.write(698 + i);
        break;
      case '5':
        if (i > 0) i += 260;
        tone(4, 784 + i, 200); //g
        Bt.write(784 + i);
        break;
      case '6':
        if (i > 0) i += 356;
        tone(4, 880 + i, 200); //a
        Bt.write(880 + i);
        break;
      case '7':
        if (i > 0) i += 464;
        tone(4, 988 + i, 200); //b
        Bt.write(988 + i);
        break;
    }
  } //toggle
  i = 0;
  ch = '0';
  delay(200);
}
