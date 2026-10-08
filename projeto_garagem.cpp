#include <Servo.h>

const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 9;
const int ledPin = 10;
const int pinBuzzer = A5;

Servo cancelaServo;

bool barreiraAberta = false;

// ======================================================
// FUNÇÕES AUXILIARES
// ======================================================

void abreCancela() {
  cancelaServo.write(90);
  digitalWrite(ledPin, HIGH);
  barreiraAberta = true;
}

void fechaCancela() {
  cancelaServo.write(0);
  digitalWrite(ledPin, LOW);
  barreiraAberta = false;
}

void buzzerOn() {
  tone(pinBuzzer, 1294);  // Ré (D4)
  delay(1000);             // PIIII
  noTone(pinBuzzer);
  delay(1000);   
}

void buzzerOff() {
  noTone(pinBuzzer);
}

// ======================================================
// SETUP
// ======================================================

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  cancelaServo.attach(servoPin);
  cancelaServo.write(0);

  buzzerOff();
}

// ======================================================
// LOOP
// ======================================================

void loop() {
  long duration, distance;

  // Dispara o sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Mede o tempo do retorno
  duration = pulseIn(echoPin, HIGH);

  // Converte para centímetros
  distance = (duration / 2) / 29.1;

  // ====================================================
  // VEÍCULO DETECTADO
  // ====================================================

  if (distance <= 15) {
    abreCancela();
    buzzerOn();
  }

  // ====================================================
  // VEÍCULO NÃO DETECTADO
  // ====================================================

  else {
    buzzerOff();

    if (barreiraAberta) {
      delay(1500);
      fechaCancela();
    }
  }

  delay(100);
}