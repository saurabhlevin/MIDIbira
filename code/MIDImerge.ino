#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int piezoPin = 0;

int8_t transpose = 0;
int8_t piezoValue = 0;

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Send a Note (pitch 42, velo 127 on channel 1)
  MIDI.sendNoteOn(pitch,velocity+transpose,channel);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  MIDI.sendNoteOff(pitch,velocity,channel);
}
void setup() {
  MIDI.turnThruOff();
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
}

void loop() {

  if(MIDI.read()) {
    int type = MIDI.getType();
    if(type != 0x80 && type != 0x90) {
      MIDI.send(MIDI.getType(),MIDI.getData1(),MIDI.getData2(),MIDI.getChannel()); 
    }  
  } 
        piezoValue = analogRead(piezoPin);
        transpose = constrain(piezoValue, 0, 127);
      //  transpose = map(piezoValue, 0, 180, 20, 127);  

}




