#include "pitches.h"

const unsigned int TRIG_PIN = 13;
const unsigned int ECHO_PIN = 12;
const unsigned int BAUD_RATE = 9600;

int melody[] = {NOTE_D4, NOTE_C5, NOTE_FS4, NOTE_A4};
int noteDurations[] = {8, 8, 4, 4};
int speed = 90;
void (*resetFunc)(void) = 0; // Declare reset function pointer

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}

void notePlay() {
  for (int thisNote = 0; melody[thisNote] != -1; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(3, melody[thisNote], noteDuration);
    delay(noteDuration * 0.9); // Add a slight delay after playing the note
    noTone(3);
  }
}
void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  digitalWrite(ECHO_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(ECHO_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ECHO_PIN, LOW);

  pinMode(ECHO_PIN, INPUT);
  long duration = pulseIn(ECHO_PIN, HIGH);
  long cm = (duration / 2) / 29.1;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (cm > 100) {
    notePlay();
    delay(100);
    Serial.print("Reet");
    resetFunc(); 
  }
}
