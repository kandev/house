#define _ABOUT "Todor Kandev, https://kandev.com"
#define _VERSION "2019.01.09"
#define led_speed 5    //onboard led fade in-out speed
#define led_blink_speed 1000
#define debounce_limit 100
#define _METER1 2
#define _METER2 3
#define _METER3 18
#define _METER4 19
#define _METER5 20
#define _METER6 21
#define _BLUE_LED 51
#define _RED_LED 52
#define _GREEN_LED 53
#define _LED 13         //heartbeat led pin (onboard is 13)

int led_br = 1;                             //initial led brightness
short led_steps = 10;                        //led brightness change steps
unsigned long led_millis = 0;                        //stores the moment of last led change
unsigned long blink_moment = led_blink_speed;                         //at which time was the last led blink
unsigned long red_moment = 0;
unsigned long consumption[7] = {0, 0, 0, 0, 0, 0, 0};   //average consumption for the last 5 minutes
volatile unsigned long m[7] = {0, 0, 0, 0, 0, 0, 0};    //store the moment of each interrupt in millis
volatile unsigned long v[7] = {0, 0, 0, 0, 0, 0, 0};    //store interrupt calls, each meter tick
long unsigned uptime = 0;
char c;

void inc_1() {
  if (millis() - m[1] > debounce_limit) {
    v[1]++;
    m[1] = millis();
  }
}
void inc_2() {
  if (millis() - m[2] > debounce_limit) {
    v[2]++;
    m[2] = millis();
  }
}
void inc_3() {
  if (millis() - m[3] > debounce_limit) {
    v[3]++;
    m[3] = millis();
  }
}
void inc_4() {
  if (millis() - m[4] > debounce_limit) {
    v[4]++;
    m[4] = millis();
  }
}
void inc_5() {
  if (millis() - m[5] > debounce_limit) {
    v[5]++;
    m[5] = millis();
  }
}
void inc_6() {
  if (millis() - m[6] > debounce_limit) {
    v[6]++;
    m[6] = millis();
  }
}

void setup() {
  pinMode(_METER1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_METER1), inc_1, FALLING);
  pinMode(_METER2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_METER2), inc_2, FALLING);
  pinMode(_METER3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_METER3), inc_3, FALLING);
  pinMode(_METER4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_METER4), inc_4, FALLING);
  pinMode(_METER5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_METER5), inc_5, FALLING);
  pinMode(_METER6, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_METER6), inc_6, FALLING);
  pinMode(_LED, OUTPUT);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(_RED_LED, OUTPUT);

  Serial.begin(9600);
  delay(100);
  Serial.print("{\"about\":\"");
  Serial.print(_ABOUT);
  Serial.print("\",\"version\":\"");
  Serial.print(_VERSION);
  Serial.println("\"}");
}

void loop() {
  short q,p;

  p=1;
  while (p<=6) {
    consumption[p] = v[p] * 12;
    p++;
  }
  if (millis() - uptime >= 300000) {
    q=1;
    while (q<=6) {
      v[q] = 0;
      q++;
    }
    uptime = millis();
  }
  if (Serial.available()) {
    c = Serial.read();
    if (c == '\n') {
      Serial.println("{");
      Serial.println("\"info\":\"Displays uptime in milliseconds and 5min average power load for each input pin in watts.\",");

      Serial.print("\"uptime-ms\":\"");
      Serial.print(millis());
      Serial.println("\",");
      q=1;
      while (q<=6) {
        Serial.print("\"PWR");
        Serial.print(q);
        Serial.print("\":\"");
        Serial.print(consumption[q]);
        Serial.println("\",");
        q++;
      }

      Serial.print("\"In1\":\"");
      Serial.print(digitalRead(22));
      Serial.println("\",");

      Serial.print("\"In2\":\"");
      Serial.print(digitalRead(23));
      Serial.println("\"");

      Serial.println("}");
      Serial.println(led_millis);
      Serial.println(blink_moment);
      Serial.println(led_br);
    }
  }
  if (millis() - led_millis > led_speed) {
    analogWrite(_LED, led_br);
    if (millis()-blink_moment>led_blink_speed) {
      led_br = led_br + led_steps;
    }
    if (led_br <= 0 || led_br >= 255) {
      led_steps = -led_steps;
    }
    if (led_br <= 0 ) {
      blink_moment=millis();
      led_br = led_br + led_steps;
    }
    led_millis = millis();
  }
  for (q=1;q<=6;q++) {
    if (millis()-m[q]<10) {
      digitalWrite(_RED_LED,1);
      red_moment=millis();
    }
  }
  if (millis()-red_moment>10) {
    digitalWrite(_RED_LED,0);
  }
  delay(1);
}
