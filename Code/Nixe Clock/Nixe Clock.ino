#include <RTClib.h>

RTC_DS1307 rtc;

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
    digitalWrite(tubes[address][0], HIGH);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 3:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], HIGH);
    break;

    case 4:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 5:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], HIGH);
    break;

    case 6:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], HIGH);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 7:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], HIGH);
    break;

    case 8:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], HIGH);
    digitalWrite(tubes[address][3], LOW);
    break;

    case 9:
    digitalWrite(tubes[address][0], LOW);
    digitalWrite(tubes[address][1], LOW);
    digitalWrite(tubes[address][2], LOW);
    digitalWrite(tubes[address][3], HIGH);
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

  bool RTC_Flag = false;
  if (!rtc.begin()) 
    RTC_Flag = true;

  if (!rtc.isrunning() && RTC_Flag == false) 
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (rtc.isrunning() && rtc.begin()){}
}

void loop() {
  //TEST
  for(int i = 0; i <= 9; i++){
    for(int id = 0; id <= 4; id++){
      write_nixie(id, i);
      Serial.println("Writing " + String(i) + " To Nixie Number " + String(id) + "!");

      delay(10);
    }
    delay(500);
  }

  //CLOCK
  /*DateTime now = rtc.now();
  int hrs = now.hour();

  if (hrs == 0 && hrs != 12) {
    hrs = 12;
  } else if (hrs == 12 && hrs != 0) {
    hrs = 12;
  } else if (hrs < 12 && hrs != 0) {
    hrs = hrs;
  } else if (hrs > 12 && hrs != 0) {
    hrs = hrs - 12;
  }

  int one = (hour / 10) % 10;
  int two = hour % 10;
  int three =  (minute / 10) % 10;
  int four = minute % 10;

  write_nixie(1, one);
  write_nixie(2, two);
  write_nixie(3, three);
  write_nixie(4, four);*/

  delay(1000);
}
