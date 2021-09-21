/*
 * Project yapowermon
 * Description:
 * Author:
 * Date:
 */

#include "Particle.h"
#include "Adafruit_INA260.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

SerialLogHandler dbg(LOG_LEVEL_ALL);
Adafruit_INA260 ina260 = Adafruit_INA260();


static void park() {
  Log.warn("PARKING ON ERROR");
  while (1) {
    delay(250);
  }
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  delay(4000); //wait for Serial USB to connect
  Log.info("setup begin");

  if (!ina260.begin()) {
    Log.error("Couldn't find INA260 chip");
    park();
  }

  Log.info("setup done");
}

void loop() {
  delay(250);
  float current = ina260.readCurrent();
  if (current < 0) { current = 0; }
  Log.info("%lu,%0.2f", millis(), current);
}