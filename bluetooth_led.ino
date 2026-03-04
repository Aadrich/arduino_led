#include <SoftwareSerial.h>
#include <FastLED.h>

SoftwareSerial BT(2, 3);  // RX, TX

#define NumLeds 40
#define ledPin 8
CRGB LED[NumLeds];

enum class Mode {
  OFF,
  RUNCOMET,
  TRANSITION,
  CHRISTMAS,
  COLORPICK,
  NONE
};

Mode currentMode = Mode::OFF;

uint8_t hue = 0;
uint32_t lastFrame = 0;

// COMET függvényhez használt változók
uint16_t stepIdx = 0;
int transitionComet = 60;
int groupSize = 10;

void comet() {
  uint32_t now = millis();
  if (now - lastFrame >= transitionComet) {
    lastFrame = now;

    FastLED.clear();

    for (uint8_t k = 0; k < groupSize; k++) {
      int idx = stepIdx - k;
      while (idx < 0) idx += NumLeds;

      // Halványodás számítása
      uint8_t brightness = 255 - (k * (255 / groupSize));

      LED[idx % NumLeds] = CHSV(hue, 180, brightness);
    }

    FastLED.setBrightness(100);
    FastLED.show();
    hue++;  // szín változik
    stepIdx++;
  }
}

// COLOR TRANSITION
uint16_t transitionColor = 100;
void colorTransition() {
  uint32_t now = millis();
  if (now - lastFrame >= transitionColor) {
    lastFrame = now;

    fill_solid(LED, NumLeds, CHSV(hue, 255, 255));

    FastLED.show();

    hue++;
  }
}

// CHRISTMAS
bool switchLeds = true;
uint8_t xmasPhase = 0;          
uint8_t xmasStep = 4;
uint32_t lastXmas = 0;
uint16_t xmasInterval = 40;

// új: mennyi ideig tartson a csúcson és a mélyponton
uint8_t holdOnFrames  = 10;   // ~10 * 40ms = 400ms
uint8_t holdOffFrames = 6;    // ~6  * 40ms = 240ms
uint8_t holdCnt = 0;

// új: állapot a “tartáshoz”
enum class XmasHoldState { NONE, HOLD_ON, HOLD_OFF };
XmasHoldState holdState = XmasHoldState::NONE;

void christmas() {
  uint32_t now = millis();
  if (now - lastXmas < xmasInterval) return;
  lastXmas = now;

  // --- HOLD logika: ha tartunk, nem léptetjük a fázist ---
  if (holdState == XmasHoldState::HOLD_ON) {
    if (holdCnt++ >= holdOnFrames) {
      holdCnt = 0;
      // csúcs után: jöhet OFF szünet (még mindig 255-ön vagyunk most),
      // de mivel crossfade-nél a másik oldal ekkor 0,
      // itt közvetlenül átváltunk OFF hold-ra úgy, hogy phase=0-ra resetelünk.
      xmasPhase = 0;
      switchLeds = !switchLeds;
      holdState = XmasHoldState::HOLD_OFF;
    }
  }
  else if (holdState == XmasHoldState::HOLD_OFF) {
    if (holdCnt++ >= holdOffFrames) {
      holdCnt = 0;
      holdState = XmasHoldState::NONE; // indulhat újra a fade
    }
  }
  else {
    // normál fade: garantáltan elérjük a 255-öt
    if (xmasPhase + xmasStep >= 255) xmasPhase = 255;
    else xmasPhase += xmasStep;

    // ha elértük a csúcsot, onnantól HOLD_ON
    if (xmasPhase == 255) {
      holdState = XmasHoldState::HOLD_ON;
      holdCnt = 0;
    }
  }

  // --- fényerő számítás ---
  uint8_t p = (xmasPhase);
  uint8_t bLevel = p;
  uint8_t aLevel = 255 - p;

  // teljes fekete küszöb
  if (aLevel < 6) aLevel = 0;
  if (bLevel < 6) bLevel = 0;

  for (int i = 0; i < NumLeds; i++) {
    bool odd = (i & 1);
    bool isA = switchLeds ? odd : !odd;
    uint8_t v = isA ? aLevel : bLevel;
    LED[i] = CHSV(hue, 255, v);
  }

  FastLED.show();

  // színek pörgetése (lassítható)
  hue++;
}
// SET SOLID COLOR
String input = "";
void setColorFromString(const String& msg) {
  FastLED.clear();
  FastLED.setBrightness(100);

  int c1 = msg.indexOf(',');
  int c2 = msg.indexOf(',', c1 + 1);
  if (c1 <= 0 || c2 <= c1) return;

  int r = msg.substring(0, c1).toInt();
  int g = msg.substring(c1 + 1, c2).toInt();
  int b = msg.substring(c2 + 1).toInt();

  fill_solid(LED, NumLeds, CRGB(r, g, b));

  FastLED.show();
}

void setup() {
  FastLED.addLeds<WS2812B, ledPin, GRB>(LED, NumLeds);
  FastLED.clear(true);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);  // pl. 1.5A limit

  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Arduino starts!");
}

void loop() {
  // 1) BT mindig olvasva legyen
  while (BT.available()) {
    char v = (char)BT.read();
    if (v == 'r') {
      FastLED.clear(true);
      input = "";
      currentMode = Mode::RUNCOMET;
      lastFrame = 0;
      continue;
    }

    if(v == 't'){
      FastLED.clear(true);
      input = "";
      currentMode = Mode::TRANSITION;
      lastFrame = 0;
      continue;
    }

    if(v == 'x'){
      FastLED.clear(true);
      input = "";
      currentMode = Mode::CHRISTMAS;
      lastFrame = 0;
      continue;
    }

    if (v == 'o') {
      input = "";
      FastLED.clear(true);
      currentMode = Mode::OFF;
      continue;
    }

    Serial.write(v);
    if (v == '\n') {
      currentMode = Mode::COLORPICK;
    } else if (v != '\n') {
      input += v;
      if (input.length() > 40) input = "";
    }
  }
 
  switch (currentMode) {
    case Mode::RUNCOMET:
      {
        comet();
        break;
      }
    case Mode::TRANSITION:
      {
        colorTransition();
        break;
      }
    case Mode::CHRISTMAS:
      {
        christmas();
        break;
      }
    case Mode::COLORPICK:
      {
        setColorFromString(input);
        currentMode = Mode::NONE;
        input="";
        break;
      }
    case Mode::OFF:
      {
        break;
      }
  }
}






