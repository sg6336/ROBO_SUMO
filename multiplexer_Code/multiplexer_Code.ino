void move(int *sensorData) {
  //proccessBottomSensors(sensorData);

  proccessUpperSensors(sensorData);
}

void proccessBottomSensors(int *sensorData) {
  if (sensorData[C2]) {
    currDirection = Backward;
    sendToShiftRegister(motorSignals[Backward]);
    isNearLine = true;
  }
  if (sensorData[C1]) {
    currDirection = Forward;
    sendToShiftRegister(motorSignals[Forward]);
    isNearLine = true;
  }
  if (sensorData[C0]) {
    currDirection = Left;
    sendToShiftRegister(motorSignals[Left]);
    isNearLine = true;
  }
  if (sensorData[C3]) {
    currDirection = Right;
    sendToShiftRegister(motorSignals[Right]);
    isNearLine = true;
  }
  if (!sensorData[0] && !sensorData[1] && !sensorData[2] && !sensorData[3]) {
    // if(!isMovingToCenter)
    // {
    //   oldTimeForMovingCenter = millis();
    //   isMovingToCenter = true;
    // } else {
    //   int currTime = millis();
    //   if( (currTime - oldTimeForMovingCenter) > timeToCenter)
    //   {
    //     sendToShiftRegister(motorSignals[None]);
    //     isMovingToCenter = false;
    //   }
    // }
    currDirection = None;
    sendToShiftRegister(motorSignals[None]);
  }
}

void proccessUpperSensors(int *sensorData) {
  // if (sensorData[C4] && !isNearLine)
  // {
  //   currDirection = Right;
  //   sendToShiftRegister(motorSignals[Right]);
  //   isNearLine = true;
  // }
  // if (sensorData[C5] && !isNearLine)
  // {
  //   currDirection = Right;
  //   sendToShiftRegister(motorSignals[Right]);
  //   isNearLine = true;
  // }
  // if (sensorData[C6] && !isNearLine)
  // {
  //   currDirection = Right;
  //   sendToShiftRegister(motorSignals[Right]);
  //   isNearLine = true;
  // }
  // if (sensorData[C7] && !isNearLine)
  // {
  //   currDirection = Right;
  //   sendToShiftRegister(motorSignals[Right]);
  //   isNearLine = true;
  // }
  if (!sensorData[C4]) {
    currDirection = Forward;
    sendToShiftRegister(motorSignals[Forward]);
  }
  if (!sensorData[C5]) {
    currDirection = Left;
    sendToShiftRegister(motorSignals[Left]);
  }
  if (!sensorData[C6]) {
    currDirection = Backward;
    sendToShiftRegister(motorSignals[Backward]);
  }
  if (!sensorData[C7]) {
    currDirection = Right;
    sendToShiftRegister(motorSignals[Right]);
  }
  if (sensorData[C4] && sensorData[C5] && sensorData[C6] && sensorData[C7]) {
    sendToShiftRegister(motorSignals[None]);
  }
}