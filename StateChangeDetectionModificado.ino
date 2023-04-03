/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  This example shows how to detect when a button or button changes from off to on
  and on to off.

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10 kilohm resistor attached to pin 2 from ground
  - LED attached from pin 13 to ground (or use the built-in LED on most
    Arduino boards)

  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

 https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection
*/

// this constant won't change:
#define INTERRUPTOR 2    // the pin that the pushbutton is attached to

// Variables will change:
int contadorInterruptor = 0;   // counter for the number of button presses
int estadoInterruptor = 0;         // current state of the button
int estadoAntreriorInterruptor = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(INTERRUPTOR, INPUT);
  // initialize the LED as an output:
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  estadoInterruptor = digitalRead(INTERRUPTOR);

  // compare the estadoInterruptor to its previous state
  if (estadoInterruptor != estadoAntreriorInterruptor) {
    // if the state has changed, increment the counter
    if (estadoInterruptor == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      contadorInterruptor++;
      Serial.println("Encendido (LED IR bloqueado)");
      Serial.print("número de veces: ");
      Serial.println(contadorInterruptor);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("Apagado (LED IR desbloqueado)");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }       
  
  // save the current state as the last state, for next time through the loop
  estadoAntreriorInterruptor = estadoInterruptor;


  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  if (contadorInterruptor % 4 == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

}
