#define _ABOUT "Todor Kandev, https://kandev.com, https://github.com/kandev/house"
#define _VERSION "2019.01.09"
#define led_speed 5                                     //onboard led fade in-out speed
#define led_blink_speed 1000                            //delay between blinks
#define debounce_limit 100                              //minimum delay between interrupts
#define _BLUE_LED 51
#define _RED_LED 52
#define _GREEN_LED 53
#define _LED 13                                         //heartbeat led pin (onboard is 13)
const short meters[] = {2, 3, 18, 19, 20, 21};
const short digital_in[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
const short digital_out[] = {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

int led_br = 1;                                         //initial status led brightness
short led_steps = 10;                                   //status led brightness change steps
unsigned long led_millis = 0;                           //stores the moment of last status led change
unsigned long blink_moment = led_blink_speed;           //at which time was the last status led blink
unsigned long red_moment = 0;
unsigned long consumption[] = {0, 0, 0, 0, 0, 0};       //average consumption for the last 5 minutes
volatile unsigned long m[] = {0, 0, 0, 0, 0, 0};        //store the moment of each interrupt in millis
volatile unsigned long v[] = {0, 0, 0, 0, 0, 0};        //store interrupt calls, each meter tick
long unsigned uptime = 0;                               //stores the moment of the last 5 minutes period
char c;                                                 //used for serial console input

void inc_0() {
  if (millis() - m[0] > debounce_limit) {
    v[0]++;
    m[0] = millis();
  }
}
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

void setup() {
  pinMode(meters[0], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(meters[0]), inc_0, FALLING);
  pinMode(meters[1], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(meters[1]), inc_1, FALLING);
  pinMode(meters[2], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(meters[2]), inc_2, FALLING);
  pinMode(meters[3], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(meters[3]), inc_3, FALLING);
  pinMode(meters[4], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(meters[4]), inc_4, FALLING);
  pinMode(meters[5], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(meters[5]), inc_5, FALLING);
  pinMode(_LED, OUTPUT);
  pinMode(_RED_LED, OUTPUT);
  pinMode(_GREEN_LED, OUTPUT);
  pinMode(_BLUE_LED, OUTPUT);
  for (int q = 0; q < (sizeof(digital_in)/sizeof(digital_in[0])); q++) {
    pinMode(digital_in[q], INPUT_PULLUP);
  }
  for (int q = 0; q < (sizeof(digital_out)/sizeof(digital_out[0])); q++) {
    pinMode(digital_out[q], OUTPUT);
  }
  Serial.begin(9600);
  delay(100);
  Serial.print("{\"about\":\"");
  Serial.print(_ABOUT);
  Serial.print("\",\"version\":\"");
  Serial.print(_VERSION);
  Serial.println("\"}");
}

void loop() {
  for (short q = 0; q <= 5; q++) {
    consumption[q] = v[q] * 12;
  }
  if (millis() - uptime >= 300000) {
    for (short q = 0; q <= 5; q++) {
      v[q] = 0;
    }
    uptime = millis();
  }
  if (Serial.available()) {
    c = Serial.read();
    if (c == '\n') {
      Serial.println("{");
      Serial.println("\"info\":\"Displays uptime in milliseconds and 5min average power load for each input pin in watts.\",");

      Serial.print("\"inputs\":\"");
      Serial.print(sizeof(digital_in)/sizeof(digital_in[0]));
      Serial.println("\",");

      Serial.print("\"outputs\":\"");
      Serial.print(sizeof(digital_out)/sizeof(digital_out[0]));
      Serial.println("\",");

      Serial.print("\"meters\":\"");
      Serial.print(sizeof(meters)/sizeof(meters[0]));
      Serial.println("\",");

      Serial.print("\"uptime-ms\":\"");
      Serial.print(millis());
      Serial.println("\",");

      for (short q = 0; q < (sizeof(consumption)/sizeof(consumption[0])); q++) {
        Serial.print("\"PWR");
        Serial.print(q);
        Serial.print("\":\"");
        Serial.print(consumption[q]);
        Serial.println("\",");
      }

      for (short q = 0; q < (sizeof(digital_in)/sizeof(digital_in[0])); q++) {
        Serial.print("\"In");
        Serial.print(q);
        Serial.print("\":\"");
        Serial.print(digitalRead(digital_in[q]));
        Serial.println("\",");
      }

      Serial.println("}");
    }
  }
  if (millis() - led_millis > led_speed) {
    analogWrite(_LED, led_br);
    if (millis() - blink_moment > led_blink_speed) {
      led_br = led_br + led_steps;
    }
    if (led_br <= 0 || led_br >= 255) {
      led_steps = -led_steps;
    }
    if (led_br <= 0 ) {
      blink_moment = millis();
      led_br = led_br + led_steps;
    }
    led_millis = millis();
  }

  //check if we had and interrupt in the past 10ms and blinks the irq led
  for (short q = 0; q <= 5; q++) {
    if (millis() - m[q] < 10) {
      digitalWrite(_RED_LED, 1);
      red_moment = millis();
    }
  }
  if (millis() - red_moment > 10) {
    digitalWrite(_RED_LED, 0);
  }
  delay(1);
}
