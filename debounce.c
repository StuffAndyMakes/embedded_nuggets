#include <Arduino.h>

#define PIN_TEST_LED 13
#define PIN_TEST_BUTTON 12
#define BUTTON_DEBOUNCE_INTERVAL 20

typedef enum {
  BUTTON_IDLE, BUTTON_DOWN, BUTTON_PRESSED, BUTTON_UP
} button_state_t;
button_state_t buttonState = BUTTON_IDLE;
unsigned long debounceTimeout = 0;

bool isLEDOn = false;

void handleButton(button_state_t bs);

void setup() {
  pinMode(PIN_TEST_LED, OUTPUT);
  digitalWrite(PIN_TEST_LED, LOW);
  pinMode(PIN_TEST_BUTTON, INPUT_PULLUP);
}

void loop(void) {
  if (digitalRead(PIN_TEST_BUTTON) == LOW) {
    if (buttonState == BUTTON_IDLE) {
        buttonState = BUTTON_DOWN;
        debounceTimeout = millis() + BUTTON_DEBOUNCE_INTERVAL;
        handleButton(buttonState);
    } else if (buttonState == BUTTON_DOWN && millis() > debounceTimeout) {
        buttonState = BUTTON_PRESSED;
        handleButton(buttonState);
    }
  } else {  // button pin is HIGH
    if (buttonState == BUTTON_DOWN || buttonState == BUTTON_PRESSED) {
        buttonState = BUTTON_UP;
        handleButton(buttonState);
    } else if (buttonState == BUTTON_UP) {
        buttonState = BUTTON_IDLE;
        handleButton(buttonState);
    }
  }
}

void handleButton(button_state_t bs) {
  switch (bs) {
    case BUTTON_IDLE:
      break;
    case BUTTON_DOWN:
      break;
    case BUTTON_PRESSED:
      isLEDOn = (isLEDOn == LOW ? HIGH : LOW);
      digitalWrite(PIN_TEST_LED, isLEDOn);
      break;
    case BUTTON_UP:
      break;
  }
}
