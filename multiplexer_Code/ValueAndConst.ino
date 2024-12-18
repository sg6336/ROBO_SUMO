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

int *g_sensorData = calloc(multiplexerSensorsAmount, sizeof(int));

byte inputData = 0;
byte inputDataOld = 0;

byte inChar = 0;

int motorSignals[] = { 85, 170, 105, 150, 0};

int oldTimeForMovingCenter = 0;
int timeToCenter = 350;
bool isMovingToCenter = false;
bool isNearLine = false;

enum Direction
{
  Forward, Backward, Right, Left, None
};

Direction currDirection = None;

enum Sensor {
  C7, C6, C5, C4, C3, C2, C1, C0
};