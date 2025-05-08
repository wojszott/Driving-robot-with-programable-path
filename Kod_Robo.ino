// Definiowanie pinów
const int buttonStartPin = 2; // D2
const int buttonForwardPin = 3; // D3
const int buttonRightPin = 4; // D4
const int buttonLeftPin = 5; // D5
const int leftWheelPin1 = 6; // D6
const int leftWheelPin2 = 7; // D7
const int rightWheelPin1 = 8; // D8
const int rightWheelPin2 = 9; // D9

bool recording = false;
bool running = false;
int route[100]; // Tablica do przechowywania trasy
int routeIndex = 0;

// Funkcje do sterowania kołami
void driveForward() {
  digitalWrite(leftWheelPin1, HIGH);
  digitalWrite(leftWheelPin2, LOW);
  digitalWrite(rightWheelPin1, HIGH);
  digitalWrite(rightWheelPin2, LOW);
}

void turnRight() {
  digitalWrite(leftWheelPin1, HIGH);
  digitalWrite(leftWheelPin2, LOW);
  digitalWrite(rightWheelPin1, LOW);
  digitalWrite(rightWheelPin2, LOW);
}

void turnLeft() {
  digitalWrite(leftWheelPin1, LOW);
  digitalWrite(leftWheelPin2, LOW);
  digitalWrite(rightWheelPin1, HIGH);
  digitalWrite(rightWheelPin2, LOW);
}

void stopWheels() {
  digitalWrite(leftWheelPin1, LOW);
  digitalWrite(leftWheelPin2, LOW);
  digitalWrite(rightWheelPin1, LOW);
  digitalWrite(rightWheelPin2, LOW);
}

void setup() {
  pinMode(buttonStartPin, INPUT_PULLUP);
  pinMode(buttonForwardPin, INPUT_PULLUP);
  pinMode(buttonRightPin, INPUT_PULLUP);
  pinMode(buttonLeftPin, INPUT_PULLUP);
  pinMode(leftWheelPin1, OUTPUT);
  pinMode(leftWheelPin2, OUTPUT);
  pinMode(rightWheelPin1, OUTPUT);
  pinMode(rightWheelPin2, OUTPUT);

  Serial.begin(9600);
  Serial.println("Setup complete.");
}

void loop() {
  if (digitalRead(buttonStartPin) == LOW) {
    Serial.println("Start button pressed");
    delay(200); // Debouncing
    while (digitalRead(buttonStartPin) == LOW); // Wait for button release
    
    if (!recording && !running) {
      recording = true;
      routeIndex = 0;
      Serial.println("Start recording...");
    } else if (recording) {
      recording = false;
      running = true;
      Serial.println("Stop recording. Start running...");
    } else if (running) {
      running = false;
      stopWheels();
      Serial.println("Stop running.");
    }
    delay(200); // Debouncing
  }

  if (recording) {
    if (digitalRead(buttonForwardPin) == LOW) {
      Serial.println("Forward button pressed");
      delay(200); // Debouncing
      while (digitalRead(buttonForwardPin) == LOW); // Wait for button release
      route[routeIndex++] = 11;
      Serial.println("Forward");
      delay(200); // Debouncing
    } else if (digitalRead(buttonRightPin) == LOW) {
      Serial.println("Right button pressed");
      delay(200); // Debouncing
      while (digitalRead(buttonRightPin) == LOW); // Wait for button release
      route[routeIndex++] = 10;
      Serial.println("Right");
      delay(200); // Debouncing
    } else if (digitalRead(buttonLeftPin) == LOW) {
      Serial.println("Left button pressed");
      delay(200); // Debouncing
      while (digitalRead(buttonLeftPin) == LOW); // Wait for button release
      route[routeIndex++] = 1;
      Serial.println("Left");
      delay(200); // Debouncing
    }
  }

  if (running) {
    for (int i = 0; i < routeIndex; i++) {
      switch (route[i]) {
        case 11:
          driveForward();
          break;
        case 10:
          turnRight();
          break;
        case 1:
          turnLeft();
          break;
      }
      delay(1000); // Czas trwania ruchu (możesz dostosować)
    }
    running = false;
    stopWheels();
    Serial.println("Finished running the route.");
  }
}
