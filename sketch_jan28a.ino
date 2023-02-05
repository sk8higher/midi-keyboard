#include <Bounce2.h>
#include <USB-MIDI.h>

// номера midi-нот. стандартом принят отсчет от ноты c3 (60), в некоторых контроллерах yamaha - c4
// 48 - c2, 60 - c3, 72 - c4?
int default_notes[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71 };
int octave = 3;

// Номера пинов клавиш (c c# d d# e f f# g g# a a# b)
#define C_BTN_PIN 2
#define CD_BTN_PIN 3
#define D_BTN_PIN 4
#define DD_BTN_PIN 5
#define E_BTN_PIN 6
#define F_BTN_PIN 7
#define FD_BTN_PIN 8
#define G_BTN_PIN 9
#define GD_BTN_PIN 10
#define A_BTN_PIN 11
#define AD_BTN_PIN 12
#define B_BTN_PIN 13

// Пин потенциометра (ручки громкости)
#define POT_PIN A0

// Пины кнопок для переключения октав
#define PLUS_OCT_BTN_PIN A1
#define MINUS_OCT_BTN_PIN A2

// Создаем объекты кнопок для прослушивания ивентов на них
Bounce2::Button cButton = Bounce2::Button();
Bounce2::Button cdButton = Bounce2::Button();
Bounce2::Button dButton = Bounce2::Button();
Bounce2::Button ddButton = Bounce2::Button();
Bounce2::Button eButton = Bounce2::Button();
Bounce2::Button fButton = Bounce2::Button();
Bounce2::Button fdButton = Bounce2::Button();
Bounce2::Button gButton = Bounce2::Button();
Bounce2::Button gdButton = Bounce2::Button();
Bounce2::Button aButton = Bounce2::Button();
Bounce2::Button adButton = Bounce2::Button();
Bounce2::Button bButton = Bounce2::Button();

Bounce2::Button plusOctButton = Bounce2::Button();
Bounce2::Button minusOctButton = Bounce2::Button();

// const byte buttonPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
// const byte buttonCount = sizeof(buttonPins);
// Bounce2::Button buttons[buttonCount];

// нужна для отсылки ивента noteoff
byte last_played_note;

// чета там инициализируем шоб миди работало
USBMIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  // прилепляем обработчик событий на каждую кнопку
  // interval - debounce interval
  // pressedState - низкий т. к. не используется внешний резистор
  cButton.attach(C_BTN_PIN, INPUT_PULLUP);
  cButton.interval(25);
  cButton.setPressedState(LOW);

  cdButton.attach(CD_BTN_PIN, INPUT_PULLUP);
  cdButton.interval(25);
  cdButton.setPressedState(LOW);

  dButton.attach(D_BTN_PIN, INPUT_PULLUP);
  dButton.interval(25);
  dButton.setPressedState(LOW);

  ddButton.attach(DD_BTN_PIN, INPUT_PULLUP);
  ddButton.interval(25);
  ddButton.setPressedState(LOW);

  eButton.attach(E_BTN_PIN, INPUT_PULLUP);
  eButton.interval(25);
  eButton.setPressedState(LOW);

  fButton.attach(F_BTN_PIN, INPUT_PULLUP);
  fButton.interval(25);
  fButton.setPressedState(LOW);

  fdButton.attach(FD_BTN_PIN, INPUT_PULLUP);
  fdButton.interval(25);
  fdButton.setPressedState(LOW);

  gButton.attach(G_BTN_PIN, INPUT_PULLUP);
  gButton.interval(25);
  gButton.setPressedState(LOW);

  gdButton.attach(GD_BTN_PIN, INPUT_PULLUP);
  gdButton.interval(25);
  gdButton.setPressedState(LOW);

  aButton.attach(A_BTN_PIN, INPUT_PULLUP);
  aButton.interval(25);
  aButton.setPressedState(LOW);

  adButton.attach(AD_BTN_PIN, INPUT_PULLUP);
  adButton.interval(25);
  adButton.setPressedState(LOW);

  bButton.attach(B_BTN_PIN, INPUT_PULLUP);
  bButton.interval(25);
  bButton.setPressedState(LOW);


  plusOctButton.attach(PLUS_OCT_BTN_PIN, INPUT_PULLUP);
  plusOctButton.interval(25);
  plusOctButton.setPressedState(LOW);

  minusOctButton.attach(MINUS_OCT_BTN_PIN, INPUT_PULLUP);
  minusOctButton.interval(25);
  minusOctButton.setPressedState(LOW);

  // for (int i = 0; i < buttonCount; i++) {
  //   buttons[i].attach(buttonPins[i], INPUT_PULLUP);
  //   buttons[i].interval(25);
  //   buttons[i].setPressedState(LOW);
  // }

  MIDI.begin(1);
  Serial.begin(9600);
}


void loop() {
  int rotat, velo;
  // обновляем состояние кнопки
  // for(int i = 0; i < buttonCount; i++) buttons[i].update();
  cButton.update();
  cdButton.update();
  dButton.update();
  ddButton.update();
  eButton.update();
  fButton.update();
  fdButton.update();
  gButton.update();
  gdButton.update();
  aButton.update();
  adButton.update();
  bButton.update();

  plusOctButton.update();
  minusOctButton.update();

  rotat = analogRead(POT_PIN);
  velo = rotat / 8;

  if(plusOctButton.pressed()) {
    if(octave == 7) return;

    octave++;

    for(int i = 0; i < 12; i++) {
      default_notes[i] += 12;
    }
  }

  if(minusOctButton.pressed()) {
    if(octave == 1) return;

    octave--;

    for(int i = 0; i < 12; i++) {
      default_notes[i] -= 12;
    }
  }

  if (cButton.pressed()) {
    last_played_note = default_notes[0];

    MIDI.sendNoteOn(default_notes[0], velo, 1);
  } else if(cButton.released()) {
    MIDI.sendNoteOff(default_notes[0], 0, 1);
  }

  if (cdButton.pressed()) {
    last_played_note = default_notes[1];

    MIDI.sendNoteOn(default_notes[1], velo, 1);
  } else if(cdButton.released()) {
    MIDI.sendNoteOff(default_notes[1], 0, 1);
  }

  if (dButton.pressed()) {
    last_played_note = default_notes[2];

    MIDI.sendNoteOn(default_notes[2], velo, 1);
  } else if(dButton.released()) {
    MIDI.sendNoteOff(default_notes[2], 0, 1);
  }

  if (ddButton.pressed()) {
    last_played_note = default_notes[3];

    MIDI.sendNoteOn(default_notes[3], velo, 1);
  } else if(ddButton.released()) {
    MIDI.sendNoteOff(default_notes[3], 0, 1);
  }

  if (eButton.pressed()) {
    last_played_note = default_notes[4];

    MIDI.sendNoteOn(default_notes[4], velo, 1);
  } else if(eButton.released()) {
    MIDI.sendNoteOff(default_notes[4], 0, 1);
  }

  if (fButton.pressed()) {
    last_played_note = default_notes[5];

    MIDI.sendNoteOn(default_notes[5], velo, 1);
  }

  if (fdButton.pressed()) {
    last_played_note = default_notes[6];

    MIDI.sendNoteOn(default_notes[6], velo, 1);
  }

  if (gButton.pressed()) {
    last_played_note = default_notes[7];

    MIDI.sendNoteOn(default_notes[7], velo, 1);
  }

  if (gdButton.pressed()) {
    last_played_note = default_notes[8];

    MIDI.sendNoteOn(default_notes[8], velo, 1);
  }

  if (aButton.pressed()) {
    last_played_note = default_notes[9];

    MIDI.sendNoteOn(default_notes[9], velo, 1);
  }

  if (adButton.pressed()) {
    last_played_note = default_notes[10];

    MIDI.sendNoteOn(default_notes[10], velo, 1);
  }

  if (bButton.pressed()) {
    last_played_note = default_notes[11];

    MIDI.sendNoteOn(default_notes[11], velo, 1);
  }

  //MIDI.sendNoteOff(last_played_note, 0, 1);
}
