#include <Adafruit_CircuitPlayground.h>


int target_led = 2;
int current_led = 0;
int level = 1;
int delay_time = 100;
int button_debounce = 50;
int score = 0;


void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
}


void loop() {
  int num_leds = CircuitPlayground.strip.numPixels();
  CircuitPlayground.strip.clear();


  if (score < 3) {
    CircuitPlayground.strip.setPixelColor(target_led, 0, 0, 255); // Keep target LED always blue


    if (current_led != target_led) {
      CircuitPlayground.strip.setPixelColor(current_led, CircuitPlayground.colorWheel(255));
    }
    CircuitPlayground.strip.show();
    delay(delay_time);


    if (CircuitPlayground.leftButton()) {
      if (current_led == target_led) {
        CircuitPlayground.playTone(1000, 100);
        level++;
        score++;
        delay_time = 100 / level;
      } else {
        CircuitPlayground.playTone(300, 100);
        level = 1;
        delay_time = 100;
        score = 0;
      }
      Serial.print("Score: ");
      Serial.println(score);
      delay(button_debounce);
    }


    if (CircuitPlayground.rightButton()) {
      target_led = random(num_leds);
      delay(button_debounce);
    }


    current_led++;
    if (current_led >= num_leds) {
      current_led = 0;
    }
  } else {
    CircuitPlayground.playTone(2000, 100);
    Serial.println("You win!");
    delay(3000);
    score = 0;
    level = 1;
    delay_time = 100;
  }
}

