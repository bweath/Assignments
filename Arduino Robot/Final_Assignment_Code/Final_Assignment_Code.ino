#define debug
#define fakeBoogieBarcodeNo //if defined correctly will set all of the bar values to that of the boogie barcode, emulating a correct reading of the boogie barcode
#include <Servo.h>
Servo rightServo;
Servo leftServo;

long aLDR; //holds the values for the average light levels
//Defining the values for the robots basic movements as global values as they will be used multiple times
float rStop = 90;
float lStop = 94;
int t90 = 2100;
float rForward;
float lForward;
int rBack;
int lBack;
//keeps track of the delay for each of the LEDs blinks in the dance
unsigned int green = 200;
unsigned int yellow = 300;
unsigned int red = 500;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); //left LDR
  pinMode(A1, INPUT); //center LDR
  pinMode(A2, INPUT); //right LDR
  pinMode(2, INPUT); //button one/IR reciver
  pinMode(3, OUTPUT); //IR transmitter
  pinMode(4, INPUT); //button two
  rightServo.attach(5); //right wheel servo
  leftServo.attach(6); //left wheel servo
  pinMode(7, OUTPUT); //green LED
  pinMode(12, OUTPUT); //yellow LED
  pinMode(13, OUTPUT); //red LED
  robotSlow();
  calibrateLDR();
#ifdef debug
  //prints the average light level
  Serial.print("Average of middle LDR");
  Serial.println(aLDR);

  //prints the current light levels when button 1 is pressed, and ends when button 2 is pressed
  while (digitalRead(2) == HIGH)
  { if (digitalRead(4) == LOW)
    { printLiLev();
    }
  }
#endif
  //loops here until button is pressed
  while (digitalRead(4) == HIGH)
  {
  }
  //calls the findBC function, and the robot starts searching for a barcode
  findBC();

}

void loop () {
  
}

/*
   Below are functions used to print or calibrate values from the LDRs



   *******************************************************************
*/

//prints the current average LDR value
void printLiLev() {
  //Reads and stores the light levels from the LDRs
  long liLvl[4];
  avgLight(liLvl, 5); //takes an average LDR reading of 5 values

  //prints the stored light levels
  Serial.print("Light level from A0 is: ");
  Serial.println(liLvl[0]);
  Serial.print("Light level from A1 is: ");
  Serial.println(liLvl[1]);
  Serial.print("Light level from A2 is: ");
  Serial.println(liLvl[2]);
  Serial.print("Average total light level is :");
  Serial.println(liLvl[3]);
  Serial.println("");
  //Small delay so only one set of light levels is sent with 1 button push
  delay(400);
}

//gets an average reading from the LDRs on a black and white surface, then calculates a cutoff point
void calibrateLDR() {
  long wLDR[4];
  long bLDR[4];
  long avLDR[3];
  avLDR[0] = 0, avLDR[1] = 0, avLDR[2] = 0;
  Serial.println("While the green light is on, place the robot on a white surface and press button 1");
  digitalWrite(7, HIGH); //green LED on
  //loops here untill button is pressed
  while (digitalRead(4) == HIGH)
  {
  }
  avgLight(wLDR, 100); //gets an average LDR value over 100 readings
  digitalWrite(7, LOW); //green LED off

  delay(500); //small delay, so that only one button press is registered

  Serial.println("While the yellow light is on place the robot on a black surface and press button 1");

  digitalWrite(12, HIGH); //Yellow LED ON
  //loops here untill button is pressed
  while (digitalRead(4) == HIGH)
  {
  }
  avgLight(bLDR, 100); //takes an average LDR value over 100 readings
  digitalWrite(12, LOW); //Yellow LED off

  //adds the average white and black LDR values together then divides by 2 to get the cutoff value
  avLDR[0] = (wLDR[0] + bLDR[0]) / 2;
  avLDR[1] = (wLDR[1] + bLDR[1]) / 2;
  avLDR[2] = (wLDR[2] + bLDR[2]) / 2;

  //currently my code only uses the center LDR, however, if the commented code is used, the cutoff would be the average value of all 3 LDRs cutoff values
  aLDR = avLDR[1];
  //(avLDR[0] + avLDR[1] + avLDR[2]) / 3;

  delay(500); //small delay so only one button press is registered
}

//Takes i reading from each LDR and sums them, then divides the sum by i, giving an average
void avgLight(long ldr[], int i) {
  int x;
  ldr[0] = 0;
  ldr[1] = 0;
  ldr[2] = 0;
  ldr[3] = 0;
  //loops here for i times, getting the sum of i readings
  for ( x = 0; x < i; x++) {
    ldr[0] = analogRead(A0) + ldr[0];
    ldr[1] = analogRead(A1) + ldr[1];
    ldr[2] = analogRead(A2) + ldr[2];
    delay(3);
  }
  //divides the sum of i readings by i to get the average
  ldr[0] = ldr[0] / i;
  ldr[1] = ldr[1] / i;
  ldr[2] = ldr[2] / i;
  //Gets one average for all the LDRs by adding each individual LDR average together, then dividing by 3
  ldr[3] = (ldr[0] + ldr[1] + ldr[2]) / 3;
}


/*
   Below are the functions that control the robots basic movement



   *******************************************************************
*/

//sets the robot to move at a faster speed
void robotFast() {
  robotStop();
  //calculates the foward and backward move speed based of the start value
  rForward = rStop - 12;
  lForward = lStop + 11;
  rBack = rStop + 12;
  lBack = lStop - 11;
}

//sets the robot to move at a slower speed
void robotSlow() {
  robotStop();
  rForward = rStop - 6;
  lForward = lStop + 5.5;
  rBack = rStop + 6;
  lBack = lStop - 5.5;
}


//function making the robot move forwards indefinatly
void robotForwards() {
  rightServo.write(rForward);
  leftServo.write(lForward);
  checkForParty();
}


//function making the robot move backwards indefinatly
void robotBackwards() {
  rightServo.write(rBack);
  leftServo.write(lBack);
}



//function making the robot turn right for a set time
void robotRight(int angle) {
  unsigned long endTime = (millis() + angle); //sets the end time to be the current time plus the angle
  while (endTime >= millis()) { //keeps looping intill the current time is the same as the end time
    rightServo.write(160);
    leftServo.write(160);
    checkForParty();
  }
}

//function making the robot turn left for a set time
void robotLeft(int angle) {
  unsigned long endTime = (millis() + angle);
  while (endTime > millis()) {
    rightServo.write(20);
    leftServo.write(20);
    checkForParty();
  }
}


//function to stop the robot
void robotStop() {
  rightServo.write(rStop);
  leftServo.write(lStop);
}


//function making the robot move forward for a set time, while flashing LEDs in a sequence
void danceForwards(unsigned int distance) {
  unsigned long endTime = (millis() + distance);
  while (endTime > millis()) {
    rightServo.write(rForward);
    leftServo.write(lForward);
    //checks to see if it is time to blink the LEDs or not
    blinkRed(red);
    blinkGreen(green);
    blinkYellow(yellow);
  }
}

//function making the robot move backwards for a set time, while flashing LEDs in a sequence
void danceBackwards(unsigned int distance) {
  unsigned long endTime = (millis() + distance);
  while (endTime > millis()) {
    rightServo.write(rBack);
    leftServo.write(lBack);
    blinkRed(red);
    blinkGreen(green);
    blinkYellow(yellow);
  }
}


//function making the robot turn right while flashing LEDs for the dance
void danceRight(int angle) {
  unsigned long endTime = (millis() + angle);
  while (endTime > millis()) {
    rightServo.write(160);
    leftServo.write(20);
    blinkRed(red);
    blinkGreen(green);
    blinkYellow(yellow);
  }
}


//function making the robot turn left while flashing LEDs for the dance
void danceLeft(int angle) {
  unsigned long endTime = (millis() + angle);
  while (endTime > millis()) {
    rightServo.write(20);
    leftServo.write(20);
    blinkRed(red);
    blinkGreen(green);
    blinkYellow(yellow);
  }
}


/*
    Below are functions which handle obstacle avoidance
   I encountered problems with the IR sensor detecting 'fake' obstacles for the first few seconds each time it was turned on,
   this was fixed by turning it on during setup, waiting 300ms for the fake readings to be detected, then turning it off


   *******************************************************************
*/

//makes the code less efficent as there is a 300ms delay, but stops the false readings. If the robot has a properley working IR transmiter/reciver, try removing this code
void setupObstacle() {
  tone(3, 38000); // Start sending IR pulses at 38kHz on pin 3
  delay(300); //this appears to be the shortest time that works
  noTone(3); //turn the IR LED off
}


//function to use the IR transmiter/reciver to look for obstacles, and take action if one is found
void obstacle() {
  tone(3, 38000); // Start sending IR pulses at 38kHz on pin 3
  delay(1);
  if (digitalRead(2) == LOW) //If an obstacle is detected, following code will be executed
  {
    noTone(3); //turn the IR LED off
    robotFast(); //makes the robot a bit faster, as it is not searching for barcodes
    //turns all the LEDs ON, turns 90 degrees right, moves forward 25cm, turns 90 degrees left and then turns all the LEDs off
    digitalWrite(7, HIGH); //green LED on
    digitalWrite(12, HIGH); //yellow LED on
    digitalWrite(13, HIGH); //red LED on
    robotRight(t90);
    robotForwards(); //tinker with this untill it equals 25cm
    delay(7000);
    robotLeft(t90);
    digitalWrite(7, LOW); //green LED off
    digitalWrite(12, LOW); //yellow LED off
    digitalWrite(13, LOW); //red LED off
    robotSlow(); //makes the robot go a bit slower, as it will start searching for barcodes again
    robotForwards();
    findBC();
  }
  else
  {
    noTone(3); //turn the IR LED off
  }
}

/*
    Below are the functions used in finding and reading barcodes


   *******************************************************************
*/

//function to find a barcode
void findBC() {
  long cLDR[4];
  robotForwards();
  avgLight(cLDR, 5); //takes an average of 5 readings from the LDRs
  while (cLDR[1] > aLDR) { //while on a white surface loop here
    setupObstacle();
    delay(25);
    obstacle();
    avgLight(cLDR, 5);
  }
  //once a black surface is detected, readBC is called
  readBC();
}

//function to read a barcode
void readBC() {
  const int arrSize = 7; //setting a constant int to keep tack of how long the bar array is
  long bar[arrSize];
  Serial.println("Started looking for barcodes");
  //loops here 7 times, alternating from detecting a black to detecting a white barcode
  for (int i = 0; i < arrSize; i++) {
    if (i % 2 == 0) {
      bar[i] = blackBarLength();
#ifdef debug //while debug is defined the length of the bar in millis is printed
      Serial.print("Bar ");
      Serial.print(i + 1);
      Serial.print(" read in ");
      Serial.println(bar[i]);
#endif
    }
    else {
      bar[i] = whiteBarLength();
#ifdef debug //while debug is defined the length of the bar in millis is printed
      Serial.print("Bar ");
      Serial.print(i + 1);
      Serial.print(" read in ");
      Serial.println(bar[i]);
#endif
    }
  }
  #ifdef fakeBoogieBarcode
   bar[0] = 496, bar[1] = 615, bar[2] = 2024, bar[3] = 318, bar[4] = 2003, bar[5] = 849, bar[6] = 415;
  robotStop();
  compareBC(bar);
  #endif
}

//function to calculate the length of a black bar in millis and return the value
long blackBarLength() {
  digitalWrite(7, HIGH); //green LED on
  long arLDR[2]; //this array will hold the 2 most recent average light readings
  arLDR[1] = 0; //set to 0 to emulate a very dark surface for the first check
  long cLDR[4];
  long barStart = millis(); //saves the start time of the bar in millis
  delay(150); //small delay to give the robot time to move away from the very edge of the bar, where readings seem to fluxuate alot
  avgLight(cLDR, 8); //calculates an average of 8 readings from the LDRs
  arLDR[0] = cLDR[1];
  while (arLDR[0] < aLDR && arLDR[1] < aLDR) { //makes sure that the last two average values were both above the cutoff, so one false reading does not stop the timer
    avgLight(cLDR, 8); //gets a new average light reading
#ifdef debug
    Serial.print(cLDR[1]);//Current light level is printed if debug is defined
    Serial.print(", ");
#endif
    //Moving the values in the array up on place, the top value is discarded and the bottom vaule is the newest average light reading
    arLDR[1] = arLDR[0];
    arLDR[0] = cLDR[1];
  }
  digitalWrite(7, LOW); //green LED off
  return (millis() - barStart); //returns the time it took to cross the barcode in millis
}

//same as the above function, except for white bars
long whiteBarLength() {
  digitalWrite(12, HIGH); //yellow LED on
  long arLDR[2]; //this array will hold the 2 most recent average light readings to compare
  arLDR[1] = 1000; //set to 1000 to emulate a very white surface for the first check
  long cLDR[3];
  long barStart = millis();
  delay(150);
  avgLight(cLDR, 8);
  arLDR[0] = cLDR[1];
  while (arLDR[0] > aLDR && arLDR[1] > aLDR) {
    avgLight(cLDR, 8);
#ifdef debug
    Serial.print(cLDR[1]);
    Serial.print(", ");
#endif
    //Moving  the values in the array up on place, the top value is discarded and the bottom vaule is the newest average light reading
    arLDR[1] = arLDR[0];
    arLDR[0] = cLDR[1];
  }
  digitalWrite(12, LOW); //yellow LED off
  return (millis() - barStart); //returns the time it took to cross the barcode in millis
}


//function to compare the scanned barcode with the stored barcode values
void compareBC(long newBC[]) {
  long threshold = 1000; //if the total difference in time for the sum of all the bars is less than the threshold, the barcodes will be considered the same
  long check;

  //all barcode comparison values are currently false, as I have not manage to get the barcode reader to work in order to gather the values

  //checks if the scanned barcode matches the turn left barcode
  long tLeft[7];
  //holds placeholder values for now until fix the barcode reading
  tLeft[0] = 200, tLeft[1] = 200, tLeft[2] = 200, tLeft[3] = 200, tLeft[4] = 200, tLeft[5] = 200, tLeft[6] = 200;
  check = calcTimeDiff(newBC, tLeft);
  if (check < threshold) {
    bcRight();
  }

  //checks if the scanned barcode matches the turn right barcode
  long tRight[7];
  //holds placeholder values for now until fix the barcode reading
  tRight[0] = 1, tRight[1] = 1, tRight[2] = 1, tRight[3] = 1, tRight[4] = 1, tRight[5] = 1, tRight[6] = 1;
  check = calcTimeDiff(newBC, tRight);
  if (check < threshold) {
    bcRight();
  }

  //checks if the scanned barcode matches the u-turn  barcode
  long uTurn[7];
  //holds placeholder values for now until fix the barcode reading
  uTurn[0] = 1, uTurn[1] = 1, uTurn[2] = 1, uTurn[3] = 1, uTurn[4] = 1, uTurn[5] = 1, uTurn[6] = 1;
  check = calcTimeDiff(newBC, uTurn);
  if (check < threshold) {
    bcUturn();
  }

  //checks if the scanned barcode matches the stop barcode
  long stopBC[7];
  //holds placeholder values for now until fix the barcode reading
  stopBC[0] = 1, stopBC[1] = 1, stopBC[2] = 1, stopBC[3] = 1, stopBC[4] = 1, stopBC[5] = 1, stopBC[6] = 1;
  check = calcTimeDiff(newBC, stopBC);
  if (check < threshold) {
    bcStop();
  }

  long boogie[7];
  //holds placeholder values for now until fix the barcode reading
  boogie[0] = 496, boogie[1] = 615, boogie[2] = 2024, boogie[3] = 318, boogie[4] = 2003, boogie[5] = 849, boogie[6] = 415;
  check = calcTimeDiff(newBC, boogie);
  if (check < threshold) {
    bcBoogie();
  }


  long partyTime[7];
  //holds placeholder values for now until fix the barcode reading
  partyTime[0] = 1, partyTime[1] = 1, partyTime[2] = 1, partyTime[3] = 1, partyTime[4] = 1, partyTime[5] = 1, partyTime[6] = 1;
  check = calcTimeDiff(newBC, partyTime);
  if (check < threshold) {
    bcPartyTime();
  }

  //if none of the barcodes match the red LED turns on, and a message is sent
  digitalWrite(13, HIGH); //red LED on
  Serial.println("No Match");
  robotStop();

}



//this function compares each bar in the new and old barcode, and returns a sum of all the differences
long calcTimeDiff(long newBC[], long oldBC[]) {
  long sum = 0;
  long negToPos;

  for (int i = 0; i < 7; i++) {
    negToPos = newBC[i] - oldBC[i]; //subtracts the bar i from each barcode
    if (negToPos < 0) { //if the resulting value is negative, it is made positive
      negToPos = -negToPos;
    }
    sum = sum + negToPos;  //sum holds the total mili diffrence in readings for each barcode
  }
  return sum;
}


/*
    Below are the functions used in making the robot dance


   *******************************************************************
*/



//function to make the Green LED blink
void blinkGreen(int interval) {
  static long prevMillis = 0; //stores the last time the LED blinked, and keeps its value between function calls, but is only initialised once, so it wont keep getting set to 0 everytime the function is called
  unsigned long currentMillis = millis();
  if ((currentMillis - prevMillis) >= interval) { //if the requested interval time has passed, blink the LED
    prevMillis = currentMillis;//sets the time of the last LED light change to be the current time
    digitalWrite(7, !digitalRead(7)); //Sets the red LED to be the oposite state of its current state
    green--; //the delay between each green blink is reduced by 1 every time it blinks
    if (green < 50) { //when the green blink delay becomes less than 50 it is set back to 200
      green = 200;
    }
  }
}

//function to make the yellow LED blink
void blinkYellow(int interval) {
  static long prevMillis = 0; //stores the last time the LED blinked, and keeps its value between function calls, but is only initialised once, so it wont keep getting set to 0 everytime the function is called
  unsigned long currentMillis = millis();
  if ((currentMillis - prevMillis) >= interval) { //if the requested interval time has passed, blink the LED
    prevMillis = currentMillis;//sets the time of the last LED light change to be the current time
    digitalWrite(12, !digitalRead(12)); //Sets the red LED to be the oposite state of its current state
    yellow--; //the delay between each yellow blink is reduced by 1 every time it blinks
    if (yellow < 100) { //when the yellow blink delay becomes less than 100 it is set back to 300
      yellow = 300;
    }
  }
}

void blinkRed(int interval) {
  static long prevMillis = 0; //stores the last time the LED blinked, and keeps its value between function calls, but is only initialised once, so it wont keep getting set to 0 everytime the function is called
  unsigned long currentMillis = millis();
  if ((currentMillis - prevMillis) >= interval) { //if the requested interval time has passed, blink the LED
    prevMillis = currentMillis;//sets the time of the last LED light change to be the current time
    digitalWrite(13, !digitalRead(13)); //Sets the red LED to be the oposite state of its current state
    red++;
    if (red > 510) {
      red = 150;
    }
  }
}



/*
    Below are the functions containing the instructions of each barcode


   *******************************************************************
*/

//function holding the instructions for when the robot reads the left barcode
void bcLeft() {
  digitalWrite(7, HIGH); //green LED on
  robotLeft(t90);
  digitalWrite(7, LOW); //green LED off
  findBC(); //looks for the next barcode
}


//function holding the instructions for when the robot reads the right barcode
void bcRight() {
  digitalWrite(12, HIGH); //yellow LED on
  robotRight(t90);
  digitalWrite(12, LOW); //yellow LED off
  findBC(); //looks for the next barcode
}

//function holding the instrucions for when the robot reads the uturn barcode
void bcUturn() {
  digitalWrite(7, HIGH); //green LED on
  digitalWrite(12, HIGH); //yellow LED on
  robotRight(t90);
  robotRight(t90);//makes the robot turn right 180 degrees
  digitalWrite(7, LOW); //green LED off
  digitalWrite(12, LOW); //yellow LED off
  findBC(); //looks for the next barcode
}

//function holding the instrucions for when the robot reads the stop barcode
void bcStop() {
  digitalWrite(13, HIGH); //red LED on
  robotStop(); //looks for the next barcode
}


//function holding the instrucions for when the robot reads the boogie barcode
void bcBoogie() {
  unsigned long endTime = millis() + 20000; //setting a timer so that the dance will stop after 20 seconds
  robotFast(); //make the robot move a bit faster as its dancing, not looking for a barcode!
  //opening dance moves, will only be used once at the start of the dance
  danceRight(600);
  danceLeft(600);
  danceForwards(400);
  danceBackwards(400);
  while (endTime >  millis())
  {
    //danceSequnce to be repeated
    danceRight(200);
    danceLeft(225);
    danceForwards(200);
    danceBackwards(200);
    danceRight(175);
    danceLeft(150);
  }
  //finishing move, only performed once at the end of the dance
  danceLeft(t90);
  danceLeft(t90);
  danceLeft(t90);
  danceLeft(t90);
  digitalWrite(7, LOW); //green LED off
  digitalWrite(12, LOW); //yellow LED off
  digitalWrite(13, LOW); //red LED off
  //after testing it appears the dance makes the robot look like its having a seizure, which is similar to my own dance moves, and is therefore perfect
  robotSlow(); //Make the robot move a bit slower again, as its back to barcode hunting
  findBC(); //looks for the next barcode
}


//function holding the instrucions for when the robot reads the party time barcode
void bcPartyTime() {
  long currentTime = millis();
  long endTime = (t90 * 4) + currentTime;
  rightServo.write(160);
  leftServo.write(160);
  while (currentTime < endTime) {
    currentTime = millis();
    tone(3, 38000); //pulses the infrared for 80ms, then stops for 80ms then repeats
    delay(80);
    noTone(3);
    delay(80);
  }
  robotStop(); //looks for the next barcode
}


/*
    Check to see if another robot is sending a IR pulse for 80ms with an 80ms delay, if so, then we dance

   *******************************************************************
*/


//a function to check if an IR signal is being transmitted for 80ms followed by a 80ms delay
void checkForParty() {
  int pause = 0;
  long startTime;
  long timePassed = 0;
  long breakOut;

  if (digitalRead(2) == LOW) {  // if digitalRead 2 == low then we begin the function, otherwise the function ends
    pause = 1;



    breakOut = millis(); // makes break out equal the current time

    while (pause == 1) { //Loop here until the IR pulse ends, we wont time it, as we dont know if we detected it midway through its pulse
      startTime = millis(); //keep updating startTime to be the current time untill the next layer of the loop
      if ((millis() - breakOut) > 100) { //if the program spends more than 100ms in this loop it will break out
      break;}
    if (digitalRead(2) == HIGH) {
        breakOut = millis(); //update breakOut with the current time of the new loop
        while (digitalRead(2) == HIGH) { //will loop here untill another IR signal is detected, or until break out - millis() is greater than 100 seconds
          if ((millis() - breakOut) > 100) { //if the program spends more than 100ms in this loop it will break out
          break;
        }
      }
      timePassed = (millis() - startTime); //calulate the time for which there was no IR pulse
        pause = 2;
      }
    }

    if (timePassed > 74 && timePassed < 86) { //if the delay between IR pulses was between 75 and 85ms, then we continue, otherwise we break out of the function as it is not a 80ms delay
      pause = 3;
    }

    if (pause == 3) {
      startTime = millis();
      while (digitalRead(2) == LOW) { //loops here while there is an IR signal
        if ((millis() - startTime) > 100) { //if the program spends more than 100ms it breaks as we know the IR does not pulse for 80ms
        break;
      }
    }
    timePassed = startTime - millis(); //sets time passed to equal the amount of ms the IR signal was pulsed for
    }


    if (timePassed > 74 && timePassed < 86) { //if the  IR pulse was between 75 and 85ms, then we dance, as it has both a pulse length of 80ms, and a delay of 80ms, if not we break out of the function
      bcBoogie(); //robot begins to dance
    }
  }
}
