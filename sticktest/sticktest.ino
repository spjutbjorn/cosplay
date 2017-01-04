#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define ADASTICK 6
#define ADARING 2
#define ADASTICKPIXELS 8 
#define ADARINGPIXELS 16


Adafruit_NeoPixel stick = Adafruit_NeoPixel(ADASTICKPIXELS, ADASTICK, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(ADARINGPIXELS, ADARING, NEO_GRB + NEO_KHZ800);

int delayval = 200; // delay for half a second

void setup() {
  stick.begin(); 
  ring.begin();
  startup();
}

void loop() {
  delay(50000);
  pulse();
}

void startup(){
  int stickCount = 0;
  for(int i=0;i<ADARINGPIXELS;i++){


  if(i % 2 == 0){
    stick.setPixelColor(stickCount, stick.Color(150,0,0)); 
    stickCount++;
  }
  
    ring.setPixelColor(i, ring.Color(150,0,0)); 
    setBrightness(254/(16 - i));
    
    delay(delayval); 

  }
  setBrightness(254);
}

void pulse(){
    int count = 16;
    int delayms = 20;
    for(int i=count;i>0;i--){
      setBrightness(254/(count - i));
      delay(delayms); 
    }

    for(int i=0;i<count;i++){
      setBrightness(254/(count - i));
      delay(delayms); 
    }

}

void setBrightness(int brightness){
    if(brightness > 254)
      brightness = 254;
    stick.setBrightness(brightness);
    ring.setBrightness(brightness);
    
    stick.show(); 
    ring.show(); 
}
