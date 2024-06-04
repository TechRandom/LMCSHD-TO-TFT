#include <TFT_eSPI.h> // Hardware-specific library
#include <HardwareSerial.h>

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

HardwareSerial Cereal(1);

const uint8_t HEIGHT = 128;
const uint16_t WIDTH = 182;

const int NUM_PIX = WIDTH * HEIGHT;

uint16_t data[NUM_PIX];

void setup() {
  Cereal.begin(1500000); // initialize the Cereal communication
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  if (Cereal.available()){
    byte header = Cereal.read();
    if (header == 0x05){
      Cereal.println(WIDTH);
      Cereal.println(HEIGHT);
    }
    else if (header == 0x42){
      Cereal.readBytes((uint8_t *)data, NUM_PIX * 2);
      tft.pushImage(0, 0, (int32_t) WIDTH, (int32_t) HEIGHT, data);
      Cereal.write(0x06); //acknowledge
    }
  }
}
