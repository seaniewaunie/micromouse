#include <LED.h>

#define MODE_LED_PIN A5
#define SOUTH_LED_PIN A4
#define WEST_LED_PIN A3
#define EAST_LED_PIN A2
#define NORTH_LED_PIN A1

LED mode(MODE_LED_PIN);
LED south(SOUTH_LED_PIN);
LED west(WEST_LED_PIN);
LED east(EAST_LED_PIN);
LED north(NORTH_LED_PIN);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  mode.flashLED();
  south.flashLED();
  west.flashLED();
  east.flashLED();
  north.flashLED();
  delay(1000);
}
