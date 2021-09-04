/*
 * To update scketch:
 * Disconect Trinamic Power supply
 * Plug Arduino USB cable
 * Switch RS485 to OFF with switch on shield
 * Upload arduino sketch
 * Unplug Arduino USB cable
 * Switch RS485 to ON with switch on shield
 * Reconect Trinamic Power supply
 */

int delayBetweenRS = 20;
// - Different time needed for the different animations
// 1000 * 60 = 60000 = 1 minute
unsigned long timeNeeded_calibration = 50000;
unsigned long timeNeeded_toe = 20000;
unsigned long timeNeeded_heel = 17000;
unsigned long timeNeeded_step = 26000; // - 6 s
// - Where M1 is the LEFT shoe and M2 the RIGHT shoe
// - Calibration address
byte calib_M1[] = {0x01, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83};
byte calib_M2[] = {0x02, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84};
// - Toe in front address
byte toe_M1[] = {0x01, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x84};
byte toe_M2[] = {0x02, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x85};
// - Hell back address
byte heel_M1[] = {0x01, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x85};
byte heel_M2[] = {0x02, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x86};
// - Full step address
byte step_M1[] = {0x01, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x86};
byte step_M2[] = {0x02, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x87};

void setup() {
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  
  // - Calibrate the two motors
  Serial.write(calib_M1, sizeof calib_M1);
  delay(delayBetweenRS);
  Serial.write(calib_M2, sizeof calib_M2);
  delay(timeNeeded_calibration);

  delay(8000);

  // - Toe animation
  Serial.write(toe_M1, sizeof toe_M1);
  delay(delayBetweenRS);
  Serial.write(heel_M2, sizeof heel_M2);
  delay(timeNeeded_toe);
  delay(6000);
  Serial.write(heel_M1, sizeof heel_M1);
  delay(delayBetweenRS);
  Serial.write(toe_M2, sizeof toe_M2);
  delay(timeNeeded_toe);

  delay(8000);

  // - Step animation 
  Serial.write(step_M1, sizeof step_M1);
  delay(timeNeeded_step);
  Serial.write(step_M2, sizeof step_M2);
  delay(timeNeeded_step);
  Serial.write(step_M1, sizeof step_M1);
  delay(timeNeeded_step);
  Serial.write(step_M2, sizeof step_M2);
  delay(timeNeeded_step);
  delay(9000);
}
