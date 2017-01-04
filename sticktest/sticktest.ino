#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define ADASTICK 2
#define ADARING 6
#define ADASTICKPIXELS 8 
#define ADARINGPIXELS 16


Adafruit_NeoPixel stick = Adafruit_NeoPixel(ADASTICKPIXELS, ADASTICK, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(ADARINGPIXELS, ADARING, NEO_GRB + NEO_KHZ800);

int delayval = 400; // delay for half a second
long randNumber;
long randDelay;

void setup() {
  stick.begin(); 
  ring.begin();
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  startup();
}

void loop() {
  randNumber = random(100);
  randDelay = random(60000);
  delay(randDelay);

  if(randNumber < 70)
    pulse();
  else
    scan();
}

void startup(){
  int stickCount = 0;
  for(int i=0;i<ADARINGPIXELS;i++){


  if(i % 2 == 0){
    stick.setPixelColor(stickCount, stick.Color(0,150,0)); 
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
    int delayms = delayval / 10;
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

void scan(){
  colorWipe(ring.Color(255, 0, 0), 50); // Red
  
  theaterChase(ring.Color(127, 0, 0), 50); // Red 

  colorWipe(ring.Color(255, 0, 0), 50); // Red
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<ring.numPixels(); i++) {
    ring.setPixelColor(i, c);
    ring.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, c);    //turn every third pixel on
      }
      ring.show();

      delay(wait);

      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
