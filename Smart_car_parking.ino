#define BLYNK_TEMPLATE_ID        ""
#define BLYNK_TEMPLATE_NAME      ""
#define BLYNK_AUTH_TOKEN         ""
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>


char ssid[] = "Wifi Name";
char pass[] = "WiFi Password";

// I2C LCD
#define SDA_PIN 21
#define SCL_PIN 22
LiquidCrystal_I2C lcd(0x27,16,2);

Servo gateServo;

// IR sensors
int IR1=33, IR2=26, IR3=25;
int IR4=34, IR5=35, IR6=32;

// LEDs
#define LED1 13
#define LED2 14
#define LED3 12
#define LED4 23
#define LED5 4
#define LED6 27

// Ultrasonic
int trigOpen=2, echoOpen=15;
int trigClose=5, echoClose=19;
enum State {IDLE, OPENING, WAIT_PASS, CLOSING, WAIT_CLEAR};
State gateState = IDLE;

enum Direction {NONE, ENTRY, EXIT};
Direction carDirection = NONE;

long duration;
int distanceOpen, distanceClose;

int evOccupied, fuelOccupied;
int evVacant, fuelVacant;

// 🔥 NEW FEATURES VARIABLES
bool reserveEV = false;
bool reserveFuel = false;

bool alertActive = false;
unsigned long alertTimer = 0;

bool carInside = false;
static bool wasFull = false;

// timing
unsigned long lastLCD = 0;
bool showVacant = true;
bool gateOpen = false;

//📱 BLYNK BUTTONS
BLYNK_WRITE(V4) // Reserve EV
{
  reserveEV = param.asInt();
}

BLYNK_WRITE(V5) // Reserve Fuel
{
  reserveFuel = param.asInt();
}

void setup()
{
Serial.begin(115200);

// Blynk start
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Wire.begin(SDA_PIN, SCL_PIN);

  lcd.init();
  lcd.backlight();

  pinMode(IR1,INPUT); pinMode(IR2,INPUT); pinMode(IR3,INPUT);
  pinMode(IR4,INPUT); pinMode(IR5,INPUT); pinMode(IR6,INPUT);

  pinMode(LED1,OUTPUT); pinMode(LED2,OUTPUT); pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT); pinMode(LED5,OUTPUT); pinMode(LED6,OUTPUT);

  pinMode(trigOpen,OUTPUT); pinMode(echoOpen,INPUT);
  pinMode(trigClose,OUTPUT); pinMode(echoClose,INPUT);

  gateServo.attach(18);
  gateServo.write(90);
}

// FAST ultrasonic with timeout
int getDistance(int trig,int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 20000); // timeout 20ms

  if(duration == 0) return 999; // no reading
  return duration * 0.034 / 2;
}

void loop()
{
  Blynk.run();

// Read sensors instantly
  int s1=digitalRead(IR1);
  int s2=digitalRead(IR2);
  int s3=digitalRead(IR3);
  int s4=digitalRead(IR4);
  int s5=digitalRead(IR5);
  int s6=digitalRead(IR6);

  evOccupied = 0;
  fuelOccupied = 0;

  // EV slots
  if(s1==LOW){evOccupied++; digitalWrite(LED1,HIGH);} else digitalWrite(LED1,LOW);
  if(s2==LOW){evOccupied++; digitalWrite(LED2,HIGH);} else digitalWrite(LED2,LOW);
  if(s3==LOW){evOccupied++; digitalWrite(LED3,HIGH);} else digitalWrite(LED3,LOW);

  // Fuel slots
  if(s4==LOW){fuelOccupied++; digitalWrite(LED4,HIGH);} else digitalWrite(LED4,LOW);
  if(s5==LOW){fuelOccupied++; digitalWrite(LED5,HIGH);} else digitalWrite(LED5,LOW);
  if(s6==LOW){fuelOccupied++; digitalWrite(LED6,HIGH);} else digitalWrite(LED6,LOW);

  evVacant = 3 - evOccupied;
  fuelVacant = 3 - fuelOccupied;

  // 🔁 Non-blocking LCD update every 1 sec
  if(millis() - lastLCD > 1000)
  {
    lastLCD = millis();
    lcd.clear();

    if(showVacant)
    {
      lcd.setCursor(0,0);
      lcd.print("EV Vacant: "); lcd.print(evVacant);

      lcd.setCursor(0,1);
      lcd.print("Fuel Vacant: "); lcd.print(fuelVacant);
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print("EV Occupied: "); lcd.print(evOccupied);

      lcd.setCursor(0,1);
      lcd.print("Fuel Occupied: "); lcd.print(fuelOccupied);
    }

    showVacant = !showVacant;
  }

  // 🚀 FAST gate control
  // OPEN GATE (only once)
// Read sensors
distanceOpen  = getDistance(trigOpen, echoOpen);
distanceClose = getDistance(trigClose, echoClose);

bool carAtEntry = (distanceOpen > 0 && distanceOpen < 6);
bool carAtExit  = (distanceClose > 0 && distanceClose < 6);

switch(gateState)
{
  case IDLE:
    // Detect new car
    if(carAtEntry && !(evVacant == 0 && fuelVacant == 0))
    {
      carDirection = ENTRY;
      gateServo.write(0); // OPEN
      gateOpen = true;
      gateState = WAIT_PASS;
    }
    else if(carAtExit)
    {
      carDirection = EXIT;
      gateServo.write(0); // OPEN
      gateOpen = true;
      gateState = WAIT_PASS;
    }
    break;

  case WAIT_PASS:
    // Wait until car reaches opposite sensor
    if(carDirection == ENTRY && carAtExit)
    {
      gateState = CLOSING;
    }
    else if(carDirection == EXIT && carAtEntry)
    {
      gateState = CLOSING;
    }
    break;

  case CLOSING:
    delay(500); // let car pass fully
    gateServo.write(90); // CLOSE
    gateOpen = false;
    gateState = WAIT_CLEAR;
    break;

  case WAIT_CLEAR:
    // 🔑 IMPORTANT: wait until BOTH sensors are clear
    if(!carAtEntry && !carAtExit)
    {
      carDirection = NONE;
      gateState = IDLE; // ready for next car
    }
    break;
}

// Reservation apply
if(reserveEV && evVacant > 0)
{
  evVacant--;
}

if(reserveFuel && fuelVacant > 0)
{
  fuelVacant--;
}

//🔔 ALERT SYSTEM
// 🚨 ALERT SYSTEM (Priority Display)

if(evVacant == 0 && fuelVacant == 0)
{
  // FULL PARKING → always show
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Parking Full");

  if(!wasFull)
  {
    Blynk.logEvent("parking_full", "Parking Full");
    wasFull = true;
  }

  alertActive = true; // block normal LCD
}
else
{
  // When space becomes available
  if(wasFull)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Slots Available");

    Blynk.logEvent("slot_available", "Slots Available");

    alertActive = true;
    alertTimer = millis();
    wasFull = false;
  }

  // Show "Slots Available" ONLY for 3 seconds
  if(alertActive && millis() - alertTimer > 3000)
  {
    alertActive = false;
  }
}
if(evVacant == 0 && fuelVacant == 0)
{
  Blynk.virtualWrite(V7, "FULL");
}
else
{
  Blynk.virtualWrite(V7, "AVAILABLE");
}

// 📡 SEND DATA TO APP
Blynk.virtualWrite(V0, evVacant);
Blynk.virtualWrite(V1, fuelVacant);
Blynk.virtualWrite(V2, evOccupied);
Blynk.virtualWrite(V3, fuelOccupied);

}