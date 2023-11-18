#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
Servo Servo1;
Servo Servo2;
int servoPin1 = 9;
int servoPin2 = 10;

void setup() {
  Serial.begin(9600);
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  pinMode(8, INPUT);
}

void loop() {
  static int timeRemaining = 30; // Variable to hold the countdown value
  
  display.clearDisplay(); // Clear the display buffer
  display.setTextSize(4); // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.setCursor(0, 0); // Set cursor position

if(digitalRead(8) == HIGH) {
    timeRemaining += 15;
  }

  display.print(timeRemaining); // Display the current countdown value
  display.display(); // Show the updated display buffer
  
  delay(1000); // Wait for 1 second
  timeRemaining--; // Decrement the countdown value
  
  if (timeRemaining < 0) {
    Servo1.write(0);
    Servo2.write(0);
    delay(1000); // Wait for 1 second
    // Reset the countdown to 30 seconds after reaching 0
    Servo1.write(180);
    Servo2.write(180);
    timeRemaining = 30;
  }
}




