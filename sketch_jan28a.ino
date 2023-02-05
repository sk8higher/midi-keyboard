#include <Bounce2.h>
#include <USB-MIDI.h>

// номера midi-нот. стандартом принят отсчет от ноты c3 (60), в некоторых контроллерах yamaha - c4
int default_notes[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71 };

// Номер октавы для ограничения переключений
int octave = 3;

// Номера пинов клавиш (c c# d d# e f f# g g# a a# b)
const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

// Пин потенциометра (ручки громкости)
#define POT_PIN A0

// Пины кнопок для переключения октав
#define PLUS_OCT_BTN_PIN A1
#define MINUS_OCT_BTN_PIN A2

// Создаем объекты кнопок для прослушивания ивентов на них
Bounce2::Button plusOctButton = Bounce2::Button();
Bounce2::Button minusOctButton = Bounce2::Button();

const int buttonCount = 12;

Bounce2::Button buttons[buttonCount];

// чета там инициализируем шоб миди работало
USBMIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // Потенциометр будет вводить значения
  pinMode(POT_PIN, INPUT);
  // прилепляем обработчик событий на каждую кнопку
  // interval - debounce interval
  // pressedState - низкий т. к. не используется внешний резистор
  plusOctButton.attach(PLUS_OCT_BTN_PIN, INPUT_PULLUP);
  plusOctButton.interval(25);
  plusOctButton.setPressedState(LOW);

  minusOctButton.attach(MINUS_OCT_BTN_PIN, INPUT_PULLUP);
  minusOctButton.interval(25);
  minusOctButton.setPressedState(LOW);

  for (int i = 0; i < buttonCount; i++) {
    buttons[i].attach(buttonPins[i], INPUT_PULLUP);
    buttons[i].interval(25);
    buttons[i].setPressedState(LOW);
  }

  MIDI.begin(1);
  Serial.begin(9600);
}


void loop() {
  int rotat, velo;
  // обновляем состояние кнопок
  for(int i = 0; i < buttonCount; i++) buttons[i].update();

  plusOctButton.update();
  minusOctButton.update();

  rotat = analogRead(POT_PIN);
  // velocity - громкость/сила нажатия ноты.
  // 1023 / 8 = 127 - максимальное значение
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

  if (buttons[0].pressed()) {
    MIDI.sendNoteOn(default_notes[0], velo, 1);
  } else if(buttons[0].released()) {
    MIDI.sendNoteOff(default_notes[0], 0, 1);
  }

  if (buttons[1].pressed()) {
    MIDI.sendNoteOn(default_notes[1], velo, 1);
  } else if(buttons[1].released()) {
    MIDI.sendNoteOff(default_notes[1], 0, 1);
  }

  if (buttons[2].pressed()) {
    MIDI.sendNoteOn(default_notes[2], velo, 1);
  } else if(buttons[2].released()) {
    MIDI.sendNoteOff(default_notes[2], 0, 1);
  }

  if (buttons[3].pressed()) {
    MIDI.sendNoteOn(default_notes[3], velo, 1);
  } else if(buttons[3].released()) {
    MIDI.sendNoteOff(default_notes[3], 0, 1);
  }

  if (buttons[4].pressed()) {
    MIDI.sendNoteOn(default_notes[4], velo, 1);
  } else if(buttons[4].released()) {
    MIDI.sendNoteOff(default_notes[4], 0, 1);
  }

  if (buttons[5].pressed()) {
    MIDI.sendNoteOn(default_notes[5], velo, 1);
  } else if(buttons[5].released()) {
    MIDI.sendNoteOff(default_notes[5], 0, 1);
  }

  if (buttons[6].pressed()) {
    MIDI.sendNoteOn(default_notes[6], velo, 1);
  } else if(buttons[6].released()) {
    MIDI.sendNoteOff(default_notes[6], 0, 1);
  }

  if (buttons[7].pressed()) {
    MIDI.sendNoteOn(default_notes[7], velo, 1);
  } else if(buttons[7].released()) {
    MIDI.sendNoteOff(default_notes[7], 0, 1);
  }

  if (buttons[8].pressed()) {
    MIDI.sendNoteOn(default_notes[8], velo, 1);
  } else if(buttons[8].released()) {
    MIDI.sendNoteOff(default_notes[8], 0, 1);
  }

  if (buttons[9].pressed()) {
    MIDI.sendNoteOn(default_notes[9], velo, 1);
  } else if(buttons[9].released()) {
    MIDI.sendNoteOff(default_notes[9], 0, 1);
  }

  if (buttons[10].pressed()) {
    MIDI.sendNoteOn(default_notes[10], velo, 1);
  } else if(buttons[10].released()) {
    MIDI.sendNoteOff(default_notes[10], 0, 1);
  }

  if (buttons[11].pressed()) {
    MIDI.sendNoteOn(default_notes[11], velo, 1);
  } else if(buttons[11].released()) {
    MIDI.sendNoteOff(default_notes[11], 0, 1);
  }
}
