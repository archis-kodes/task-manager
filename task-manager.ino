//Project: Task Manager
//Members: Archisman Das

//Library Import:
//For RFID
#include <SPI.h>
#include <MFRC522.h>

//For I2C Display
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//LCD Alias
LiquidCrystal_I2C lcd(0x27, 16, 2);

//RFID Alias
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define the pins for the touch buttons
const int INButtonPin = 5;
const int OUTButtonPin = 6;
const int prevButtonPin = 7;
const int nextButtonPin = 8;

//Define CARD IDs
String Home = "13 75 CF FD";
String School = "62 47 D1 4E";

//Define the list of items
String HomeIN[] = {"Homework", "Pump ON", "Math Homework", "Wash Clothes"};
String HomeOUT[] = {"Tiffin", "Water Bottle", "Project", "Homework"};
String SchoolIN[] = {"Chart Paper", "English Homework", "Math Notes", "Project Discuss", "Fees"};
String SchoolOUT[] = {"Water Refill", "Phone", "All Books"};

// Variable to keep track of the current item to display
int currentItem = 0;

// Variable to keep track of the button state
int nextButtonState;
int prevButtonState;
int INButtonState;
int OUTButtonState;

// Variable to store the previous button state
int lastNextButtonState;
int lastPrevButtonState;

//Setup of LCD and RFID
void setup() {

  //For LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  //For RFID
  SPI.begin();
  lcd.print("Place RFID Tag:");

  //Declare PIN Modes
  pinMode(INButtonPin, INPUT);
  pinMode(OUTButtonPin, INPUT);
  pinMode(nextButtonPin, INPUT);
  pinMode(prevButtonPin, INPUT);
}

void loop() {

  //Initialize RFID Reader
  mfrc522.PCD_Init(); 
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
  
    lcd.clear();
    content.toUpperCase();

//*******************************************************************************************************************************************************************
    //For HOME
    if (content.substring(1) == Home) {  //HOME detected
      lcd.print("HOME Detected");
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print("IN or OUT?");
      delay(500);

      //Reads any Press in Button IN or OUT
      INButtonState = digitalRead(INButtonPin);
	    OUTButtonState = digitalRead(OUTButtonPin);

      //IN button is Pressed
      if (digitalRead(INButtonPin == HIGH) {
        lcd.clear();
        lcd.print("Loading Tasks");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
         // Read the current state of the next and previous buttons
        nextButtonState = digitalRead(nextButtonPin);
        prevButtonState = digitalRead(prevButtonPin);

        // Check if the next button is pressed
        if (nextButtonState == 1)   {  
        // Move to the next item in the list
        currentItem++;

        // If we've reached the end of the list, reset the currentItem to 0
        if (currentItem >= sizeof(HomeIN) / sizeof(HomeIN[0])) {
          currentItem = 0;
        }
        // Clear the display and print the current item
        lcd.clear();
        lcd.print("TASK ");
        lcd.print(currentItem+1);
        lcd.setCursor(0,1);
        lcd.print(HomeIN[currentItem]);
        delay(1000);
      }
      

      // Check if the previous button is pressed
      if (prevButtonState == 1) {
        // Move to the previous item in the list
        currentItem--;
        // If we've reached the beginning of the list, set currentItem to the last index
        if (currentItem < 0) {
        currentItem = sizeof(HomeIN) / sizeof(HomeIN[0]) - 1;
      }

      // Clear the display and print the current item
      lcd.clear();
      lcd.print("TASK ");
      lcd.print(currentItem+1);
      lcd.setCursor(0,1);
      lcd.print(HomeIN[currentItem]);
      delay(1000);
      }
    }

      //If OUT button is pressed
      if (OUTButtonState == 1) {
        lcd.clear();
        lcd.print("Loading Tasks");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
         // Read the current state of the next and previous buttons
        nextButtonState = digitalRead(nextButtonPin);
        prevButtonState = digitalRead(prevButtonPin);

        // Check if the next button is pressed
        if (nextButtonState == HIGH )  { 
        // Move to the next item in the list
        currentItem++;

        // If we've reached the end of the list, reset the currentItem to 0
        if (currentItem >= sizeof(HomeOUT) / sizeof(HomeOUT[0])) {
          currentItem = 0;
        }
        // Clear the display and print the current item
        lcd.clear();
        lcd.print("TASK ");
        lcd.print(currentItem+1);
        lcd.setCursor(0,1);
        lcd.print(HomeOUT[currentItem]);
        delay(1000);
      }
      // Check if the previous button is pressed
      if (prevButtonState == 1) {
        // Move to the previous item in the list
        currentItem--;
        // If we've reached the beginning of the list, set currentItem to the last index
        if (currentItem < 0) {
        currentItem = sizeof(HomeOUT) / sizeof(HomeOUT[0]) - 1;
      }

      // Clear the display and print the current item
      lcd.clear();
      lcd.print("TASK ");
      lcd.print(currentItem+1);
      lcd.setCursor(0,1);
      lcd.print(HomeOUT[currentItem]);
      delay(1000);
      }
    }
  }
//*******************************************************************************************************************************************************************
    //For SCHOOL
    if (content.substring(1) == School) {  //SCHOOL detected
      lcd.print("SCHOOL Detected");
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print("IN or OUT?");
      delay(500);

      //Reads any Press in Button IN or OUT
      INButtonState = digitalRead(INButtonPin);
	    OUTButtonState = digitalRead(OUTButtonPin);

      //IN button is Pressed
      if (INButtonState == 1) {
        lcd.clear();
        lcd.print("Loading Tasks");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
         // Read the current state of the next and previous buttons
        nextButtonState = digitalRead(nextButtonPin);
        prevButtonState = digitalRead(prevButtonPin);

        // Check if the next button is pressed
        if (nextButtonState == 1) {
        // Move to the next item in the list
        currentItem++;

        // If we've reached the end of the list, reset the currentItem to 0
        if (currentItem >= sizeof(SchoolIN) / sizeof(SchoolIN[0])) {
          currentItem = 0;
        }
        // Clear the display and print the current item
        lcd.clear();
        lcd.print("TASK ");
        lcd.print(currentItem+1);
        lcd.setCursor(0,1);
        lcd.print(SchoolIN[currentItem]);
        delay(1000);
      }

      // Check if the previous button is pressed
      if (prevButtonState == 1) {
        // Move to the previous item in the list
        currentItem--;
        // If we've reached the beginning of the list, set currentItem to the last index
        if (currentItem < 0) {
        currentItem = sizeof(SchoolIN) / sizeof(SchoolIN[0]) - 1;
      }

      // Clear the display and print the current item
      lcd.clear();
      lcd.print("TASK ");
      lcd.print(currentItem+1);
      lcd.setCursor(0,1);
      lcd.print(SchoolIN[currentItem]);
      delay(1000);
      }
    }

      //If OUT button is pressed
      if (OUTButtonState == 1) {
        lcd.clear();
        lcd.print("Loading Tasks");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
        lcd.print(".");
        delay(50);
         // Read the current state of the next and previous buttons
        nextButtonState = digitalRead(nextButtonPin);
        prevButtonState = digitalRead(prevButtonPin);

        // Check if the next button is pressed
        if (nextButtonState == 1)     {
        // Move to the next item in the list
        currentItem++;

        // If we've reached the end of the list, reset the currentItem to 0
        if (currentItem >= sizeof(SchoolOUT) / sizeof(SchoolOUT[0])) {
          currentItem = 0;
        }
        // Clear the display and print the current item
        lcd.clear();
        lcd.print("TASK ");
        lcd.print(currentItem+1);
        lcd.setCursor(0,1);
        lcd.print(SchoolOUT[currentItem]);
        delay(1000);
      }
      // Check if the previous button is pressed
      if (prevButtonState == 1) {
        // Move to the previous item in the list
        currentItem--;
        // If we've reached the beginning of the list, set currentItem to the last index
        if (currentItem < 0) {
        currentItem = sizeof(SchoolOUT) / sizeof(SchoolOUT[0]) - 1;
      }

      // Clear the display and print the current item
      lcd.clear();
      lcd.print("TASK ");
      lcd.print(currentItem+1);
      lcd.setCursor(0,1);
      lcd.print(SchoolOUT[currentItem]);
      delay(1000);
      }
    }
  }
    


  }
}
