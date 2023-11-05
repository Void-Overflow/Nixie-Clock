#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>

RTC_DS1307 rtc;

static const String daysOfTheWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool firstSundayPassed = false;
int DSTCorrection = 0;
int firstSundayDate = 0;

int tubes[4][4] = {
  {A3, A2, A1, A0},
  {13, 12, 11, 10},
  {9, 8, 7,6 },
  {5,4,3,2}
};

void write_nixie(short address, short number){
  switch (number){
    case 0:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 1:
    digitalWrite(tubes[address][0], HIGH);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], HIGH);
    break;

    case 2:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], HIGH);
    break;

    case 3:
    digitalWrite(tubes[address][0], HIGH);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 4:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 5:
    digitalWrite(tubes[address][0], HIGH);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 6:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 7:
    digitalWrite(tubes[address][0], HIGH);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 8:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 9:
    digitalWrite(tubes[address][0], HIGH);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], LOW);
    break;

    default:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], LOW);
    break;
  }
}

void setup() {
  Serial.begin(9600);

  for(int i = 0; i <= 4; i++){
    for(int ie = 0; ie < 4; ie++){
      pinMode(tubes[i][ie], OUTPUT);
      digitalWrite(tubes[i][ie], LOW);

      Serial.println("Pin " + String(tubes[i][ie]) + " Initialized!");
      delay(10);
    }
  }

  Serial.println("\n");

 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  DSTCorrection = EEPROM.read(0);
  firstSundayPassed = EEPROM.read(1);
  firstSundayDate = EEPROM.read(2);
}

void loop() {
  //TEST
  /*for(int i = 0; i <= 9; i++){
    for(int id = 0; id <= 4; id++){
      write_nixie(id, i);
      Serial.println("Writing " + String(i) + " To Nixie Number " + String(id) + "!");

      delay(10);
    }
    delay(500);
  }*/

  //CLOCK
  DateTime now = rtc.now();
  int hrs = now.hour();
  int minute = now.minute();
  
  String day = daysOfTheWeek[now.dayOfTheWeek()];
  int month = now.month();
  hrs -= DSTCorrection; 
  Serial.println(hrs);
  //November DST correction
  if(month == 11 && day == "Sunday" && hrs == 2 && firstSundayPassed == false){
    DSTCorrection = 1;
    firstSundayPassed = true;
  }
  else if (month == 12){
    DSTCorrection = 1;
    firstSundayPassed = false;
  }

  //March DST correction
  if(month == 3 && day == "Sunday" && firstSundayPassed == false){
    firstSundayPassed = true;
    firstSundayDate = now.day();
  }
  else if(month == 3 && day == "Sunday" && hrs == 2 && firstSundayPassed == true && now.day() != firstSundayDate){
    DSTCorrection = 0;
  }
  else if (month == 4){
    firstSundayPassed = false;
    firstSundayDate = 0;
    DSTCorrection = 0;
  }
  EEPROM.write(0, DSTCorrection);
  EEPROM.write(1, firstSundayPassed);
  EEPROM.write(2, firstSundayDate);
  
  if(hrs < 0)
    hrs = 23;
  if (hrs == 0 && hrs != 12) {
    hrs = 12;
  } else if (hrs == 12 && hrs != 0) {
    hrs = 12;
  } else if (hrs < 12 && hrs != 0) {
    hrs = hrs;
  } else if (hrs > 12 && hrs != 0) {
    hrs = hrs - 12;
  }
  
  int one = (hrs / 10) % 10;
  int two = hrs % 10;
  int three =  (minute / 10) % 10;
  int four = minute % 10;

  if(one > 1){}
  
  else{
    write_nixie(0, one);
    write_nixie(1, two);
    write_nixie(2, three);
    write_nixie(3, four);
  }
  
  Serial.print(String(one) + String(two));
  Serial.print(":");
  Serial.print(String(three) +  String(four));
  Serial.print(":");
  Serial.println(day + "/" + String(month));

  delay(1000 - 10);
}
