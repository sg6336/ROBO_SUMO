// Функція для читання сенсорів з мультиплексора
void readMultiplexer(int *sensorData)
{
  for (int i = 0; i < multiplexerSensorsAmount; i++)
  {
      int data = digitalRead(sig);
      setPins(i);
      sensorData[i] = data;
      Serial.print(sensorData[i]);
      Serial.print(" ");
  }
    Serial.println();
}

// Функція для налаштування мультиплексора для читання сигналу бажаного датчика
void setPins(int number) 
{
    digitalWrite(s0, (number >> 0) & 1); // отримуємо найменшзначущий біт (найправіший)
    digitalWrite(s1, (number >> 1) & 1); 
    digitalWrite(s2, (number >> 2) & 1);
    digitalWrite(s3, (number >> 3) & 1); 
}