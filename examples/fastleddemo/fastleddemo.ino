#include <FastLED.h>

#define NUM_LEDS 78

#define DATA_PIN 4

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(84);

}

void expanding()
{
    for (int stepsize = 1 ; stepsize < 1000 ; stepsize++)
    {
        memset(leds, 0, sizeof(leds));
        for (int i = 0 ; i < NUM_LEDS*100 ; i += stepsize)
            leds[i/100] = CHSV(stepsize, 255, 255);
        FastLED.show();
        delay(10);
    }
}

int posmod(int a, int b)
{
    int res = a % b;
    if (res < 0)
        res += b;
    return res;
}
void bounce(int n) {
    int loops = 0;
    int pos[8];
    int size[8];
    int speed[8];
    int color[8];

    // init with random values.
    for (int i = 0 ; i < n ; i++)
    {
        pos[i] = ((i+1)*NUM_LEDS)/(n+1);
        size[i] = random(5, 20);
        speed[i] = random(-5, 5);
        if (speed[i]>=0)  // avoid speed 0
            speed[i]++;
        color[i] = i+2; // random(16);
    }
    while(loops < NUM_LEDS) {
        // draw balls
        memset(leds, 0, sizeof(leds));
        for (int i=0 ; i<n ; i++)
        {
            int x0 = posmod(pos[i] - size[i], NUM_LEDS);
            int x1 = posmod(pos[i] + size[i], NUM_LEDS);
            if (x0 < x1) {
                for (int x = x0 ; x < x1 ; x++)
                    leds[x] = CHSV(color[i]*16, 255, 255);
            }
            else { // x0 > x1
                for (int x = x0 ; x < NUM_LEDS ; x++)
                    leds[x] = CHSV(color[i]*16, 255, 255);
                for (int x = 0 ; x < x1 ; x++)
                    leds[x] = CHSV(color[i]*16, 255, 255);
            }
        }
        FastLED.show();
        delay(20);

        // update positions
        for (int i=0 ; i<n ; i++) {
            pos[i] += speed[i];
            //color[i] = posmod(color[i] + 1, 16);
            // bounce off walls
            if (((pos[i]-size[i])<0) || ((pos[i]+size[i])>=NUM_LEDS)) {
                speed[i] = -speed[i];
                pos[i] += speed[i];
            }
        }
//      print("dots: ");
//      for (int i=0 ; i<n ; i++)
//          print(" %2d:%2d", pos[i], speed[i]);
//      print(".\n");

        // detect collisions
        for (int i=0 ; i<n ; i++) {
            for (int j=i+1 ; j<n ; j++) {
                if ( (abs(pos[i]+size[i]-(pos[j]-size[j])) < 2) || (abs(pos[i]-size[i]-(pos[j]+size[j])) < 2)) {
                    speed[i] = -speed[i];
                    speed[j] = -speed[j];
//                  int impuls = size[i] * speed[i] + size[j] * speed[j];
//                  speed[i] = -impuls / size[i];
//                  speed[j] = -impuls / size[j];
//                  if (speed[i]==0)
//                      speed[i]++;
//                  if (speed[j]==0)
//                      speed[j]--;
                }
            }
        }

        loops++;
    }
}

void loop() {
for (int i=0 ; i<2 ; i++) 
    switch(i) {
        case 0: expanding(); break;
        case 1: bounce(4); break;
      //case 2: bounce(3); break;
      //case 3: bounce(4); break;
      //case 4: bounce(5); break;
    }
}
