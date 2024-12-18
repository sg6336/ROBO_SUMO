byte readShiftRegister() {
  byte data = 0;

  // Активуємо завантаження паралельних даних (SH/LD = LOW)
  digitalWrite(latchPin165, LOW);
  delayMicroseconds(5);  // Невелика затримка для стабільності
  digitalWrite(latchPin165, HIGH);

  // Зчитуємо серійні дані
  for (int i = 0; i < 8; i++) {
    // Зсув біта, зчитаного з dataPin165, у змінну data
    data <<= 1;  // Зміщуємо дані вліво
    if (digitalRead(dataPin165)) {
      data |= 1;  // Встановлюємо молодший біт, якщо на QH логічна 1
    }

    // Генеруємо тактовий імпульс (rising edge)
    digitalWrite(clockPin165, HIGH);
    delayMicroseconds(5);  // Невелика затримка
    digitalWrite(clockPin165, LOW);
  }

  return data;
}