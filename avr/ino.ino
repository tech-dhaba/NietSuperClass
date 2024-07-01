#include <TM1637Display.h>
#include <Adafruit_SSD1306.h>
#include <LedControl.h>
char receivedChar1='0';
// Define the connections pins for the MAX7219
#define DATA_IN 12
#define CLK 11
#define CS 10
LedControl lc = LedControl(DATA_IN, CLK, CS, 1);

// Character bitmap for 'A'
byte A[8] = {
  B00000000,
  B00011000,
  B00100100,
  B00100100,
  B00111100,
  B00100100,
  B00100100,
  B00000000
};

int currVal = 0;

// Define connections pins
#define CLK 2
#define DIO 3

// Create TM1637Display object
TM1637Display displayy(CLK, DIO);

// Define the OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Define the I2C address of the display (0x3C is common for SSD1306 displays)
#define OLED_ADDRESS 0x3C

// Create an instance of the SSD1306 display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  displayy.setBrightness(5);
  // Clear the display
  displayy.clear();
  // Initialize the Serial for debugging purposes
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(8, INPUT);

  // Initialize the display
  if (!display.begin(SSD1306_PAGEADDR, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the display buffer
  display.clearDisplay();

  // Display initial message
  display.setTextSize(3);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(50, 0);     // Start at top-left corner
  display.display();
}

void loop() {
  // displayy.clear();
  unsigned long elapsedSeconds = (millis() / 1000) - currVal;
  // uint16_t displayValue = elapsedSeconds % 10000;
  uint16_t displayValue = 0;
  display.clearDisplay();
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
  if (Serial.available() > 0) {

    receivedChar1 = Serial.read();
    receivedChar1 +=1;
  }
    display.clearDisplay();
    display.setCursor(60, 0);
    char a= 'Q';
    display.println(a);
    display.setCursor(80, 0);
    display.println(receivedChar);
      // displayValue=receivedChar;
    display.display();
          // displayy.showNumberDec(displayValue-'0', true);
          if(receivedChar!=13 && receivedChar!=10 && receivedChar!=65){
          // if(receivedChar1!=13 && receivedChar1!=10 && receivedChar1!=65){
            if(receivedChar1>'0')
            displayValue=10*(receivedChar-'0')+(receivedChar1-'0'-1);
            else displayValue=receivedChar-'0';
          displayy.showNumberDec(displayValue, true);
          // }
          }
    Serial.println(receivedChar);
    Serial.println(receivedChar1);
    delay(200);
    if (receivedChar == 'A') {
      lc.shutdown(0, false);       // Wake up display
      lc.setIntensity(0, 8);       // Set brightness level (0 is min, 15 is max)
      lc.clearDisplay(0);          // Clear display register
      for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, A[i]);
      }
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
      
      currVal = millis() / 1000;  // Reset the elapsed time
    }
  }

  lc.shutdown(0, false);       // Wake up display
  lc.setIntensity(0, 8);       // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);          // Clear display register

  // Display character 'A' on the matrix
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, A[i]-A[i]);
  }
}

