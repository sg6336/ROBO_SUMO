// Функція для надсилання даних у 74HC595
void sendToShiftRegister(byte data) {
  digitalWrite(latchPin595, LOW);  // Вимикаємо защіпку
  //delayMicroseconds(5);                         // Невелика затримка
  delay(1);
  shiftOut(dataPin595, clockPin595, MSBFIRST, data);  // Надсилаємо байт
  delay(1);
  digitalWrite(latchPin595, HIGH);  // Увімкнемо защіпку для оновлення виходів
}