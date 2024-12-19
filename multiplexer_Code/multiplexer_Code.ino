// Піни Arduino для підключення 74HC165
const int latchPin165 = 2;  // SH/LD (завантаження даних)
const int clockPin165 = 3;  // CLK (тактовий сигнал)
const int dataPin165 = 4;   // QH (серійний вихід)

// Піни Arduino для підключення 74HC595
const int dataPin595 = 9;   // Пін DS (Data Serial)
const int latchPin595 = 12;  // Пін ST_CP (Latch)
const int clockPin595 = 11;  // Пін SH_CP (Clock)

//Піни Arduino для підключення мультиплексора
const int s0 = 5;
const int s1 = 6;
const int s2 = 7;
const int s3 = 8;
const int sig = 10;

const int multiplexerSensorsAmount = 8;

//int *g_sensorData = calloc(multiplexerSensorsAmount, sizeof(int));
int g_sensorData[] = {0, 0, 0, 0, 0, 0, 0, 0};

byte inputData = 0;
byte inputDataOld = 0;

byte inChar = 0;

int motorSignals[] = { 85, 170, 105, 150, 0};

enum Direction
{
  Forward, Backward, Right, Left, None
};

Direction currDirection = None;

int oldTimeForMovingCenter = 0;
int timeToCenter = 700;
bool isMovingToCenter = false;
bool isNearLine = false;

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
  } 
  //delay(2000);
  //sendToShiftRegister(motorSignals[Forward]);
  
  readMultiplexer(g_sensorData);
  move(g_sensorData);
}

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

// Функція для виводу 8-бітного числа у форматі з провідними нулями
void printBinaryWithLeadingZeros(byte data) {
  for (int i = 7; i >= 0; i--) {
    Serial.print((data >> i) & 1);  // Зміщуємо і виводимо кожен біт
  }
  Serial.println();  // Перехід на новий рядок
}

// Функція для надсилання даних у 74HC595
void sendToShiftRegister(byte data) {
  digitalWrite(latchPin595, LOW);  // Вимикаємо защіпку
  //delayMicroseconds(5);          // Невелика затримка
  delay(1);
  shiftOut(dataPin595, clockPin595, MSBFIRST, data);  // Надсилаємо байт
  delay(1);
  digitalWrite(latchPin595, HIGH);  // Увімкнемо защіпку для оновлення виходів
}

// Функція для читання сенсорів з мультиплексора
void readMultiplexer(int *sensorData)
{
  for (int i = 0; i < 8; ++i)
  {
      setPins(i);
      int data = digitalRead(sig);
      sensorData[i] = data;
      //Serial.print(sensorData[i]);
      //Serial.print(" ");
  }
    //Serial.println();
}

// Функція для налаштування мультиплексора для читання сигналу бажаного датчика
void setPins(int number) 
{
    digitalWrite(s0, (number >> 0) & 1); // отримуємо найменшзначущий біт (найправіший)
    digitalWrite(s1, (number >> 1) & 1); 
    digitalWrite(s2, (number >> 2) & 1);
    digitalWrite(s3, (number >> 3) & 1); 
}

void move(int *sensorData)
{
  proccessBottomSensors(sensorData);

  if(!isNearLine) // Якщо нижні датчики спрацьовували, то на верхні не реагуємо
  {
    proccessUpperSensors(sensorData);
  }
  delay(400);
}

void updateStateNearLine()
{
  isNearLine = true;
  isMovingToCenter = false;
}

void proccessBottomSensors(int *sensorData)
{
  if(sensorData[0])
  {
    updateStateNearLine();

    Serial.println("Backward From Bottom");
    sendToShiftRegister(motorSignals[Backward]);
  } 
  if (sensorData[1])
  {
    updateStateNearLine();

    Serial.println("Forward From Bottom");
    sendToShiftRegister(motorSignals[Forward]);
  }
  if (sensorData[2])
  {
    updateStateNearLine();

    Serial.println("Left From Bottom");
    sendToShiftRegister(motorSignals[Left]);
  }
  if (sensorData[3])
  {
    updateStateNearLine();

    Serial.println("Right From Bottom");
    sendToShiftRegister(motorSignals[Right]);
  }
  if (!sensorData[0] && !sensorData[1] && !sensorData[2] && !sensorData[3])
  {
    if(!isMovingToCenter)
    {
      oldTimeForMovingCenter = millis();
      isMovingToCenter = true;
    } else {
      Serial.println("Moving to center");
      int currTime = millis();
      if( (currTime - oldTimeForMovingCenter) > timeToCenter)
      {
        Serial.println("We are near to center");
        sendToShiftRegister(motorSignals[None]);
        isMovingToCenter = false;
        isNearLine = false;
      }
    }
    Serial.println("None From Bottom");
    sendToShiftRegister(motorSignals[None]);
  }
}

void proccessUpperSensors(int *sensorData)
{
  if (!sensorData[4])
  {
    Serial.println("Forward From Upper");
    sendToShiftRegister(motorSignals[Forward]);
  }
  if (!sensorData[5])
  {
    Serial.println("Backward From Upper");
    sendToShiftRegister(motorSignals[Backward]);
  }
  if (!sensorData[6])
  {
    Serial.println("Right From Upper");
    sendToShiftRegister(motorSignals[Right]);
  }
  if (!sensorData[7])
  {
    Serial.println("Left From Upper");
    sendToShiftRegister(motorSignals[Left]);
  }
  if(sensorData[4] && sensorData[5] && sensorData[6] && sensorData[7])
  {
    Serial.println("None From Upper");
    sendToShiftRegister(motorSignals[None]);
  }
}