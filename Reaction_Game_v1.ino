
int lpoint2 = 2;
int left_b = 3;
int greenLED = 4;
int whiteleft = 5;
int whiteright = 11;
int yellowLED = 7;
int redLED = 8;
int lpoint1 = 9;
int rpoint2 = 6;
int rpoint1 = 10;
int Buzzer = 12;
int right_b = 13;
int preemptiveClickLeft;
int preemptiveClickRight;

void blink_LED(int a, int t) {
  digitalWrite(a, HIGH);
  delay(t);
  digitalWrite(a, LOW);
  delay(t);
}
void blink_2LEDS(int a, int b, int t) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  delay(t);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  delay(t);
}
void blink_3LEDS(int a, int b, int c, int t) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  delay(t);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  delay(t);
}
void preemptiveCheck() {
  if (!digitalRead(left_b)) {
    preemptiveClickLeft = 1;
  }
  if (!digitalRead(right_b)) {
    preemptiveClickRight = 1;
  }
}
void setup() {

  pinMode(lpoint1, OUTPUT);
  pinMode(lpoint2, OUTPUT);
  pinMode(left_b, INPUT_PULLUP);
  pinMode(greenLED, OUTPUT);
  pinMode(whiteleft, OUTPUT);
  pinMode(whiteright, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(rpoint1, OUTPUT);
  pinMode(rpoint2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(right_b, INPUT_PULLUP);
}
void loop() {
  int leftwin = 0;
  int rightwin = 0;
  while (leftwin < 3 && rightwin < 3) {
    while (1) {  //WAITING FOR PLAYERS TO READY UP
      if (!digitalRead(left_b) && !digitalRead(right_b))
        break;
      blink_3LEDS(greenLED, yellowLED, redLED, 200);
    }
    preemptiveClickLeft = 0;
    preemptiveClickRight = 0;
    digitalWrite(greenLED, HIGH);  //COUNT DOWN
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    delay(800);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    delay(800);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    delay(800);
    digitalWrite(redLED, LOW);
    unsigned long int randomDelay = random(1200, 4000);
    unsigned long int delaystart = millis();
    while (millis() - delaystart < randomDelay) {
      preemptiveCheck();
      if (preemptiveClickLeft == 1 || preemptiveClickRight == 1) {
        break;
      }
    }
    if (preemptiveClickLeft == 0 && preemptiveClickRight == 0) {
      digitalWrite(Buzzer, HIGH);
      digitalWrite(whiteleft, HIGH);
      digitalWrite(whiteright, HIGH);
      unsigned long int startTime = millis();  //REACTION TIME
      while (millis() - startTime < 3000) {
        if (!digitalRead(right_b) && !digitalRead(left_b)) {
          digitalWrite(Buzzer, LOW);
          for (int i = 0; i < 5; i++) {
            digitalWrite(Buzzer, LOW);
            blink_2LEDS(whiteleft, whiteright, 300);
          }
          break;
        }
        if (!digitalRead(right_b) && digitalRead(left_b)) {  //RIGHT PLAYER POINT INCREASE
          digitalWrite(Buzzer, LOW);
          rightwin += 1;
          if (rightwin == 1) {
            digitalWrite(rpoint1, HIGH);
          }
          if (rightwin == 2) {
            digitalWrite(rpoint2, HIGH);
          }
          digitalWrite(whiteleft, LOW);
          blink_LED(whiteright, 1500);
          break;
        }
        if (!digitalRead(left_b) && digitalRead(right_b)) {  //LEFT PLAYER POINT INCREASE
          digitalWrite(Buzzer, LOW);
          leftwin += 1;
          if (leftwin == 1) {
            digitalWrite(lpoint1, HIGH);
          }
          if (leftwin == 2) {
            digitalWrite(lpoint2, HIGH);
          }
          digitalWrite(whiteright, LOW);
          blink_LED(whiteleft, 1500);
          break;
        }
      }
      digitalWrite(Buzzer, LOW);
      digitalWrite(whiteleft, LOW);
      digitalWrite(whiteright, LOW);
    }
    if (preemptiveClickLeft == 1) {
      for (int i = 0; i < 5; i++) {
        blink_LED(whiteleft, 200);
      }
    }
    if (preemptiveClickRight == 1) {
      for (int i = 0; i < 5; i++) {
        blink_LED(whiteright, 200);
      }
    }
  }
  if (leftwin == 3) {  //LEFT PLAYER WON
    digitalWrite(rpoint1, LOW);
    digitalWrite(rpoint2, LOW);
    for (int i = 0; i < 5; i++) {
      blink_3LEDS(lpoint1, lpoint2, whiteleft, 500);
    }
  }
  if (rightwin == 3) {  //RIGHT PLAYER WON
    digitalWrite(lpoint1, LOW);
    digitalWrite(lpoint2, LOW);
    for (int i = 0; i < 5; i++) {
      blink_3LEDS(rpoint1, rpoint2, whiteright, 500);
    }
  }
}