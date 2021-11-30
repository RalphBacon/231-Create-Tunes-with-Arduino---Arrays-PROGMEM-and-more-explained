/*
    Simple Christmas (or other) tune player for the Arduino Uno, Nano & Mini
*/

// Uncomment next line if using Arduino IDE 2.0
// #include <Arduino.h>
#include "notes.h"
#include "tunes.h"

// Output must be PWM capable
#define buzzerPin 9

// One second declaration milliseconds
#define ONE_SECOND 1000

// ======================================
// SETUP      SETUP      SETUP      SETUP
// ======================================
void setup() {
    Serial.begin(115200);
    delay(2000);
}

// ======================================
// LOOP     LOOP     LOOP     LOOP
// ======================================
void loop() {
    Serial.println("\nEnter tune #");
    while (!Serial.available())
        ;

    // Need to validate this - see https://bit.ly/3rk9daC 
    unsigned int tuneNo = Serial.parseInt();
    if (tuneNo > (sizeof(tunes) / sizeof(*tunes)) -1){
        Serial.println("\nNo such tune! Try again");
        return;
    }

    // Tunes start from ZERO
    Serial.print("Playing tune #");
    Serial.println(tuneNo);

    for (uint8_t cnt = 0; cnt < sizeof(tunes[tuneNo]); cnt = cnt + 2) {
        // Get the two-byte integer ("word") for the melody
        int note = pgm_read_word_near(tunes[tuneNo] + cnt);
        if (note == _END) break;

        // Get the duration of the note (one byte integer, so a "byte" not a "word")
        uint16_t durationMs = ONE_SECOND / pgm_read_byte_near(tunes[tuneNo] + cnt + 1);

        // Play the note for the duration
        tone(buzzerPin, note, durationMs);

        // Delay between notes about 1.4 x note duration (adjust to suit your ears)
        delay(durationMs * 1.4);
    }

    // All done
    Serial.println("Done!");
}
