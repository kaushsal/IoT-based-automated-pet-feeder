

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Define servo motor pin
const int servoPin = 8;

// Create a servo object
Servo servoMotor;
#define SS_PIN 10
#define RST_PIN 9
byte readCard[4];
String MasterTag = "328E824";
String tagID = "";
// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);



/**********************************************************************************************
 * setup() function
**********************************************************************************************/
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  //Show details of PCD - MFRC522 Card Reader
  mfrc522.PCD_DumpVersionToSerial();
  servoMotor.attach(servoPin);

  servoMotor.write(0);
}


/**********************************************************************************************
 * loop() function
**********************************************************************************************/
void loop() 
{
  //----------------------------------------------------------------------
  //Wait until new tag is available
  while (getID()) {
    if (tagID == MasterTag){
      unsigned long currentMillis = millis();
      Serial.println(currentMillis);
      servoMotor.write(90);
      delay(1000); // Wait for 1 second

      // Rotate the servo back to 0 degrees
      servoMotor.write(0);
      delay(1000);
    }
    else{

    }
    delay(100);

  }
  //----------------------------------------------------------------------
}




/**********************************************************************************************
 * getID() function
 * Read new tag if available
**********************************************************************************************/
boolean getID() 
{
  // Getting ready for Reading PICCs
  //If a new PICC placed to RFID reader continue
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  //Since a PICC placed get Serial and continue
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return false;
  }
  tagID = "";
  // The MIFARE PICCs that we use have 4 byte UID
  for ( uint8_t i = 0; i < 4; i++) {
  //readCard[i] = mfrc522.uid.uidByte[i];
  // Adds the 4 bytes in a single String variable
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
