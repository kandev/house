#define _ABOUT "https://github.com/kandev/house"
#define _VERSION "2019.05.22"
#define led_speed 5                                     //onboard led fade in-out speed
#define led_blink_speed 2000                            //delay between blinks
#define debounce_limit 200                              //minimum delay between interrupts
#define _BLUE_LED 51
#define _RED_LED 52
#define _GREEN_LED 53
#define _LED 13                                         //heartbeat led pin (onboard is 13)
const short irq_pins[] = {2, 3, 18, 19, 20, 21};
const short digital_in[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
const short digital_out[] = {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

int led_br = 1;                                         //initial status led brightness
short led_steps = 10;                                   //status led brightness change steps
unsigned long led_millis = 0;                           //stores the moment of last status led change
unsigned long blink_moment = led_blink_speed;           //at which time was the last status led blink
unsigned long red_moment = 0;
long unsigned uptime = 0;                               //stores the moment of the last 5 minutes period
String cmd;                                             //used for serial console input
String cmd_status;                                      //serial console output some status after command execution
volatile unsigned long counters[] = {0, 0, 0, 0, 0, 0};        //store counters of each irq
volatile unsigned long counters_temp[] = {0, 0, 0, 0, 0, 0};        //store counters of each irq for comparison and led blinking
volatile unsigned long m[] = {0, 0, 0, 0, 0, 0};        //store the moment of each interrupt in millis

void inc_0() {
  if (millis() - m[0] > debounce_limit) {
    counters[0]++;
    m[0] = millis();
  }
}
void inc_1() {
  if (millis() - m[1] > debounce_limit) {
    counters[1]++;
    m[1] = millis();
  }
}
void inc_2() {
  if (millis() - m[2] > debounce_limit) {
    counters[2]++;
    m[2] = millis();
  }
}
void inc_3() {
  if (millis() - m[3] > debounce_limit) {
    counters[3]++;
    m[3] = millis();
  }
}
void inc_4() {
  if (millis() - m[4] > debounce_limit) {
    counters[4]++;
    m[4] = millis();
  }
}
void inc_5() {
  if (millis() - m[5] > debounce_limit) {
    counters[5]++;
    m[5] = millis();
  }
}

void setup() {
  pinMode(irq_pins[0], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irq_pins[0]), inc_0, FALLING);
  pinMode(irq_pins[1], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irq_pins[1]), inc_1, FALLING);
  pinMode(irq_pins[2], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irq_pins[2]), inc_2, FALLING);
  pinMode(irq_pins[3], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irq_pins[3]), inc_3, FALLING);
  pinMode(irq_pins[4], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irq_pins[4]), inc_4, FALLING);
  pinMode(irq_pins[5], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irq_pins[5]), inc_5, FALLING);
  pinMode(_LED, OUTPUT);
  pinMode(_RED_LED, OUTPUT);
  pinMode(_GREEN_LED, OUTPUT);
  pinMode(_BLUE_LED, OUTPUT);
  for (int q = 0; q < (sizeof(digital_in) / sizeof(digital_in[0])); q++) {
    pinMode(digital_in[q], INPUT_PULLUP);
  }
  for (int q = 0; q < (sizeof(digital_out) / sizeof(digital_out[0])); q++) {
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
  uptime = millis();
  if (Serial.available()) {
    cmd = Serial.readStringUntil('\n');
    if (cmd == "0=1") {
      digitalWrite(digital_out[0], HIGH);
    } else if (cmd == "0=0") {
      digitalWrite(digital_out[0], LOW);
    } else if (cmd == "1=1") {
      digitalWrite(digital_out[1], HIGH);
    } else if (cmd == "1=0") {
      digitalWrite(digital_out[1], LOW);
    } else if (cmd == "2=1") {
      digitalWrite(digital_out[2], HIGH);
    } else if (cmd == "2=0") {
      digitalWrite(digital_out[2], LOW);
    } else if (cmd == "3=1") {
      digitalWrite(digital_out[3], HIGH);
    } else if (cmd == "3=0") {
      digitalWrite(digital_out[3], LOW);
    } else if (cmd == "4=1") {
      digitalWrite(digital_out[4], HIGH);
    } else if (cmd == "4=0") {
      digitalWrite(digital_out[4], LOW);
    } else if (cmd == "5=1") {
      digitalWrite(digital_out[5], HIGH);
    } else if (cmd == "5=0") {
      digitalWrite(digital_out[5], LOW);
    } else if (cmd == "6=1") {
      digitalWrite(digital_out[6], HIGH);
    } else if (cmd == "6=0") {
      digitalWrite(digital_out[6], LOW);
    } else if (cmd == "7=1") {
      digitalWrite(digital_out[7], HIGH);
    } else if (cmd == "7=0") {
      digitalWrite(digital_out[7], LOW);
    } else if (cmd == "8=1") {
      digitalWrite(digital_out[8], HIGH);
    } else if (cmd == "8=0") {
      digitalWrite(digital_out[8], LOW);
    } else if (cmd == "9=1") {
      digitalWrite(digital_out[9], HIGH);
    } else if (cmd == "9=0") {
      digitalWrite(digital_out[9], LOW);
    } else if (cmd == "10=1") {
      digitalWrite(digital_out[10], HIGH);
    } else if (cmd == "10=0") {
      digitalWrite(digital_out[10], LOW);
    } else if (cmd == "11=1") {
      digitalWrite(digital_out[11], HIGH);
    } else if (cmd == "11=0") {
      digitalWrite(digital_out[11], LOW);
    } else if (cmd == "12=1") {
      digitalWrite(digital_out[12], HIGH);
    } else if (cmd == "12=0") {
      digitalWrite(digital_out[12], LOW);
    } else if (cmd == "13=1") {
      digitalWrite(digital_out[13], HIGH);
    } else if (cmd == "13=0") {
      digitalWrite(digital_out[13], LOW);
    } else if (cmd == "14=1") {
      digitalWrite(digital_out[14], HIGH);
    } else if (cmd == "14=0") {
      digitalWrite(digital_out[14], LOW);
    }
    //    if (cmd == "") {
    Serial.print("{");

    Serial.print("\"cmd\":\"");
    Serial.print(cmd_status);
    Serial.println("\",");

    Serial.print("\"inputs\":\"");
    Serial.print(sizeof(digital_in) / sizeof(digital_in[0]));
    Serial.println("\",");

    Serial.print("\"outputs\":\"");
    Serial.print(sizeof(digital_out) / sizeof(digital_out[0]));
    Serial.println("\",");

    Serial.print("\"counters\":\"");
    Serial.print(sizeof(irq_pins) / sizeof(irq_pins[0]));
    Serial.println("\",");

    for (short q = 0; q < (sizeof(counters) / sizeof(counters[0])); q++) {
      Serial.print("\"Pulses");
      Serial.print(q);
      Serial.print("\":\"");
      Serial.print(counters[q]);
      Serial.println("\",");
    }

    for (short q = 0; q < (sizeof(digital_in) / sizeof(digital_in[0])); q++) {
      Serial.print("\"In");
      Serial.print(q);
      Serial.print("\":\"");
      Serial.print(digitalRead(digital_in[q]));
      Serial.println("\",");
    }
    for (short q = 0; q < (sizeof(digital_out) / sizeof(digital_out[0])); q++) {
      Serial.print("\"Out");
      Serial.print(q);
      Serial.print("\":\"");
      Serial.print(digitalRead(digital_out[q]));
      Serial.println("\",");
    }
    Serial.print("\"uptime-ms\":\"");
    Serial.print(millis());
    Serial.println("\"}");
  }
  //  }

  //Pulse blinking, visible sign of life :)
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

  //check if we had an interrupt and blink the led
  for (short q = 0; q < (sizeof(counters) / sizeof(counters[0])); q++) {
    if (counters[q] != counters_temp[q]) {
      digitalWrite(_RED_LED, 1);
      red_moment = millis();
      counters_temp[q] = counters[q];
    }
  }
  if (millis() - red_moment > 10) {
    digitalWrite(_RED_LED, 0);
  }
}
