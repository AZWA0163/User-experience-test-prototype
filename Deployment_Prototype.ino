#include <OOCSI.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const char* ssid = "lab-id";
const char* password = "ID-LAB-PSK";
const char* OOCSIName = "ESP_OOCSI_event_Alan";
//const char* OOCSIName = "ESP_OOCSI_event_Bram";
const char* hostserver = "oocsi.id.tue.nl";

int Brightness, Fade;
int i, j;
int Chore1, Chore2;
int Member1, Member2;
int Check1 = -1, Check2 = -1;

#define RING_PIN 2
#define RING_NUMBER 3

OOCSI oocsi = OOCSI();

Adafruit_NeoPixel RING = Adafruit_NeoPixel(RING_NUMBER, RING_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  oocsi.setActivityLEDPin(LED_BUILTIN);

  oocsi.connect(OOCSIName, hostserver, ssid, password, processOOCSI);
  
  RING.begin();
  RING.show();
}

void loop() {
  oocsi.check();
  for(i = 0; i < (RING_NUMBER); i++){
    RING.setPixelColor(i, 0, 0, 0);
    RING.show();
  }
  Chore1 = oocsi.getInt("Chore1", -1);
  Member1 = oocsi.getInt("Member1", -1);
  Brightness = oocsi.getInt("Brightness", 0);
  RING.setPixelColor(Chore1, 0, 0, 255);
  RING.setPixelColor(Member1, 255, 130, 0);
  RING.show();
}

void processOOCSI(){
  Serial.print("Brightness: ");
  Serial.print(oocsi.getInt("Brightness", 0));
  Serial.print("Chore1: ");
  Serial.print(oocsi.getInt("Chore1", -1));
  Serial.print("Member1: ");
  Serial.print(oocsi.getInt("Member1", -1));
}

void off(){
  
}


