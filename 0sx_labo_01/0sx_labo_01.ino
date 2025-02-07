//définir la broche de la DEL
const int ledPin = 13;

//définir l'état de l'application


enum AppState {FIRST, SECOND, THIRD};
AppState currentState = FIRST;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  switch(currentState) {
    case FIRST:
      Serial.print("Allumé : ");
      Serial.println("2206160");
      ON();
    break;
    case SECOND:
      Serial.print("Clignotement :");
     Serial.println("220610");
      blinkFast();
    break;
    case THIRD:
      delay(1000);
      Serial.print("Variation :");
      Serial.println("2206160");
      fade();
      delay(1000);
      Off();
    break;
  }
}

void ON() {
  // Variables statiques pour conserver
  // l'état de la DEL à chaque appel
  static bool ledState = HIGH;

  // Compteur d'appels
  static int counter = 0;

  //inverser l'état de la DEL
  
  digitalWrite(ledPin, HIGH);
  
  counter++;
  if (counter == 1) {
    counter = 0;
    currentState = SECOND;
  }
  delay(1000);
}

void blinkFast() {
  // Variables statiques pour conserver
  // l'état de la DEL à chaque appel
  static bool ledState = LOW;

  // Compteur d'appels
  static int counter = 0;
  
  //inverser l'état de la DEL
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  delay(250);
  counter++;
  if (counter == 4) {
    counter = 0;
    currentState = THIRD;
  }
}

void fade() {
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  
  currentState = FIRST;
}

void Off() {
  static bool ledState = LOW;

  // Compteur d'appels
  static int counter = 0;

  //inverser l'état de la DEL
  
  digitalWrite(ledPin, LOW);
  
  counter++;
  if (counter == 1) {
    counter = 0;
    currentState = FIRST;
  }
}


