#include <math.h>
#define LED_TOP 7
#define LED_RIGHT 8
#define LED_BOTTOM 9
#define LED_LEFT 10
#define LED_AUX 11
#define BTN_TOP 3
#define BTN_RIGHT 4
#define BTN_BOTTOM 6
#define BTN_LEFT 5
#define JOY_BTN 2
#define JOY_VERT A0
#define JOY_HORZ A1

int joy_vert_val_raw = 0;
float joy_vert_val = 0;
const int JOY_VERT_OFFSET = 519;
int joy_horz_val_raw = 0;
float joy_horz_val = 0;
const int JOY_HORZ_OFFSET = 528;

float joy_angle = 0;
float joy_mag = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_TOP, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_BOTTOM, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_AUX, OUTPUT);
  pinMode(JOY_BTN, INPUT);
  pinMode(BTN_TOP, INPUT);
  pinMode(BTN_RIGHT, INPUT);
  pinMode(BTN_BOTTOM, INPUT);
  pinMode(BTN_LEFT, INPUT);

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  joy_vert_val_raw = analogRead(JOY_VERT);
  joy_horz_val_raw = analogRead(JOY_HORZ);
  joy_vert_val = normalizeRange(joy_vert_val_raw, JOY_VERT_OFFSET, 1023);
  joy_horz_val = -1 * normalizeRange(joy_horz_val_raw, JOY_HORZ_OFFSET, 1023);

  joy_angle = atan2(joy_vert_val, joy_horz_val) * (180.0 / M_PI);
  joy_mag = sqrt(pow(joy_vert_val,2) + pow(joy_horz_val,2));
  Serial.print("Vertical: "); Serial.print(joy_vert_val);
  Serial.print(" Horizontal: "); Serial.println(joy_horz_val);

  //joystick points up
  if((joy_angle > -45) && (joy_angle <= 45) && (joy_mag > 0.10))
    digitalWrite(LED_RIGHT, HIGH);
  else
    digitalWrite(LED_RIGHT, LOW);

  //joystick points right
  if((joy_angle > 45) && (joy_angle <= 135) && (joy_mag > 0.10))
    digitalWrite(LED_TOP, HIGH);
  else
    digitalWrite(LED_TOP, LOW);

  //joystick points left
  if((joy_angle > 135) && (joy_angle <= 180) && (joy_mag > 0.10))
    digitalWrite(LED_LEFT, HIGH);
  else if((joy_angle >= -180) && (joy_angle <= -135) && (joy_mag > 0.10))
    digitalWrite(LED_LEFT, HIGH);
  else
    digitalWrite(LED_LEFT, LOW);

  //joystick points down
  if((joy_angle > -135) && (joy_angle <= -45) && (joy_mag > 0.10))
    digitalWrite(LED_BOTTOM, HIGH);
  else
    digitalWrite(LED_BOTTOM, LOW);

  //Turn on auxilary led when the joystick btn is pressed
  if(digitalRead(JOY_BTN) == LOW)
    digitalWrite(LED_AUX, HIGH);
  else
    digitalWrite(LED_AUX, LOW);
  
  delay(100);
}

float normalizeRange(int x, int mid_offset, int max){

  if(x >= mid_offset)
    return(((float)(x - mid_offset)) / (max - mid_offset));
  else
    return(((float)(x - mid_offset)) / (mid_offset));
}
