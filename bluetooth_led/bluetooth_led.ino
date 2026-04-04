#include <SoftwareSerial.h>
#include <FastLED.h>

const uint8_t NumLeds=40;
const uint8_t ledPin=8;

CRGB LED[NumLeds];
SoftwareSerial BT(2, 3);  // RX, TX

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

      uint8_t brightness = 255 - (k * (255 / groupSize));

      LED[idx % NumLeds] = CHSV(hue, 180, brightness);
    }

    FastLED.show();
    hue++;
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

static bool     switchLeds    = true;
static uint8_t  phase         = 0;     // 0..255
static uint32_t lastFrameChristmas      = 0;

static constexpr uint8_t  step          = 4;
static constexpr uint16_t transitionChristmas    = 40;
static constexpr uint8_t  holdOnFrames  = 10;
static constexpr uint8_t  holdOffFrames = 6;
static constexpr uint8_t  cutoff        = 6;

enum class ChristmasMode : uint8_t { FADE, HOLD_ON, HOLD_OFF };
static ChristmasMode xmasMode = ChristmasMode::FADE;
static uint8_t hold = 0;

void christmas() {
  const uint32_t now = millis();
  if (now - lastFrameChristmas < transitionChristmas) return;
  lastFrameChristmas = now;

  switch (xmasMode) {
    case ChristmasMode::FADE:
      phase = (phase + step >= 255) ? 255 : (uint8_t)(phase + step);
      if (phase == 255) { xmasMode = ChristmasMode::HOLD_ON; hold = 0; }
      break;

    case ChristmasMode::HOLD_ON:
      if (++hold >= holdOnFrames) {
        switchLeds = !switchLeds;
        phase = 0;
        xmasMode = ChristmasMode::HOLD_OFF;
        hold = 0;
      }
      break;

case ChristmasMode::HOLD_OFF:
      if (++hold >= holdOffFrames) {
        xmasMode = ChristmasMode::FADE;
        hold = 0;
      }
      break;

    
  }

  uint8_t b = phase;
  uint8_t a = 255 - phase;
  if (a < cutoff) a = 0;
  if (b < cutoff) b = 0;

  for (int i = 0; i < NumLeds; ++i) {
    const bool odd = (i & 1);
    const bool isA = switchLeds ? odd : !odd;
    LED[i] = CHSV(hue, 255, isA ? a : b);
  }

  FastLED.show();
  ++hue;
}

// SET SOLID COLOR
String input = "";
void setColorFromString(const String& msg) {
  FastLED.clear();

  int c1 = msg.indexOf(',');
  int c2 = msg.indexOf(',', c1 + 1);
  if (c1 <= 0 || c2 <= c1) return;

  int r = msg.substring(0, c1).toInt();
  int g = msg.substring(c1 + 1, c2).toInt();
  int b = msg.substring(c2 + 1).toInt();

  fill_solid(LED, NumLeds, CRGB(r, g, b));

  FastLED.show();
}

void getCurrentMode(char v){
   if (v == 'r') {
      FastLED.clear(true);
      input = "";
      currentMode = Mode::RUNCOMET;
      lastFrame = 0;
    }
    else if (v == 't') {
      FastLED.clear(true);
      input = "";
      currentMode = Mode::TRANSITION;
      lastFrame = 0;
    }
    else if (v == 'x') {
      FastLED.clear(true);
      input = "";
      currentMode = Mode::CHRISTMAS;
      lastFrame = 0;
    }
    else if (v == 'o') {
      input = "";
      FastLED.clear(true);
      currentMode = Mode::OFF;
    }
    else if (v == '\n') {
      currentMode = Mode::COLORPICK;
    }
    else {
      input += v;
      if (input.length() > 40) input = "";
    }
}

void setup() {
  FastLED.addLeds<WS2812B, ledPin, GRB>(LED, NumLeds);
  FastLED.clear(true);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
  FastLED.setBrightness(100);

  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Arduino starts!");
}

void loop() {
  while (BT.available()) {
    char v = (char)BT.read();
    getCurrentMode(v);
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