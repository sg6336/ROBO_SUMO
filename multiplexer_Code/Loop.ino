void loop() {
  if (Serial.available()) {
    inChar = (byte)Serial.read();
    Serial.print("Bin: ");
    printBinaryWithLeadingZeros(inChar);
    //sendToShiftRegister(inChar);  // Надсилаємо дані до 74hc595
    inChar = 0;
    Serial.write(g_sensorData[4]);
    Serial.write(g_sensorData[5]);
    Serial.write(g_sensorData[6]);
    Serial.write(g_sensorData[7]);
  }
  // Зчитування даних із мікросхеми 74hc165
  inputData = readShiftRegister();

  if (inputData != inputDataOld) {
    inputDataOld = inputData;

    //sendToShiftRegister(inputData);  // Надсилаємо дані до 74hc595

    // Виведення даних у серійний монітор у двійковому вигляді
    Serial.print("Data: ");
    //Serial.println(inputData, BIN);
    //printBinaryWithLeadingZeros(inputData);

    //delay(500); // Затримка для зручності перегляду
  } else {
    //delay(2000);
    //sendToShiftRegister(motorSignals[Forward]);
  }
  readMultiplexer(g_sensorData);
  move(g_sensorData);
}

// Функція для виводу 8-бітного числа у форматі з провідними нулями
void printBinaryWithLeadingZeros(byte data) {
  for (int i = 7; i >= 0; i--) {
    Serial.print((data >> i) & 1);  // Зміщуємо і виводимо кожен біт
  }
  Serial.println();  // Перехід на новий рядок
}