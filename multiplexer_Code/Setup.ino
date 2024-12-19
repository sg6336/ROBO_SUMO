void setup() {
  // Налаштування пінів як виходи або входи
  pinMode(latchPin165, OUTPUT);
  pinMode(clockPin165, OUTPUT);
  pinMode(dataPin165, INPUT);

  pinMode(dataPin595, OUTPUT);
  pinMode(latchPin595, OUTPUT);
  pinMode(clockPin595, OUTPUT);

  // Початковий стан для сигналів
  digitalWrite(latchPin165, HIGH);
  digitalWrite(clockPin165, LOW);

  // Налаштування пінів для роботи з мультиплескором
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sig, INPUT);

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  Serial.begin(9600);  // Для виводу даних у серійний монітор

  sendToShiftRegister(motorSignals[None]);
  delay(100);
  sendToShiftRegister(motorSignals[None]);
  delay(100);
}