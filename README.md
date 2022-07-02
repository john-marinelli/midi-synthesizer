# Teensy 3.2 MIDI Synthesizer

This project is an exploration into DSP and synthesis from scratch. 

The only Teensy library classes used are for audio routing and MIDI. Any waveform generation, envelopes, filters or other audio (and some MIDI) functionality is created from scratch.

## AudioPlayQueue usage

This program sends sound to the Teeny 3.2's audio shield using an AudioPlayQueue object, which takes in an int16_t (Arduino 16-bit integer) as a sample.

The default buffer size is 128 samples, and the sample rate is around 44,100 Hz. 

## MIDI library usage

Callbacks for CC, velocity and note messages are implemented to interact with filters, envelopes and waveforms.

## platformIO 

Instead of using the Arduino IDE, for increased modularity, intellisense and better compatibility with non-microcontroller projects, this program is being built with platformIO.

To get started with platformIO and try out this project on your own microcontroller, visit https://platformio.org/ for instructions. 
