int dirA1 = 10; //Motor Pin PWM#11 (Custom-L298 Motor Driver)
int dirB1 = 9; //Motor Pin PWM#10 (Custom-L298 Motor Driver)
int dirA2 = 5;  //Motor Pin PWM#5  (Custom-L298 Motor Driver)
int dirB2 = 6;  //Motor Pin PWM#6  (Custom-L298 Motor Driver)
char dataIn = 'S';
char determinant;
char det;
int vel = 0;
int overdrive = 13;

void nav(int spd,int spd2) {
  analogWrite(dirA1,spd2);
  digitalWrite(dirB1,LOW);
  analogWrite(dirA2,spd);
  digitalWrite(dirB2,LOW);
}

void rev(int spd2,int spd) {
  digitalWrite(dirA1,LOW);
  analogWrite(dirB1,spd);
  digitalWrite(dirA2,LOW);
  analogWrite(dirB2,spd2);
}

char check() {
  if (Serial.available()) {
    dataIn = Serial.read();
    if (dataIn == 'F') {
      determinant = 'F';
    } else if (dataIn == 'B') {
      determinant = 'B';
    } else if (dataIn == 'L') {
      determinant = 'L';
    } else if (dataIn == 'R') {
      determinant = 'R';
    } else if (dataIn == 'I') {
      determinant = 'I';
    } else if (dataIn == 'J') {
      determinant = 'J';
    } else if (dataIn == 'G') {
      determinant = 'G';
    } else if (dataIn == 'H') {
      determinant = 'H';
    } else if (dataIn == 'S') {
      determinant = 'S';
    } else if (dataIn == '0') {
      vel = 255;
    } else if (dataIn == '1') {
      vel = 240;
    } else if (dataIn == '2') {
      vel = 230;
    } else if (dataIn == '3') {
      vel = 205;
    } else if (dataIn == '4') {
      vel = 180;
    } else if (dataIn == '5') {
      vel = 155;
    } else if (dataIn == '6') {
      vel = 130;
    } else if (dataIn == '7') {
      vel = 105;
    } else if (dataIn == '8') {
      vel = 80;
    } else if (dataIn == '9') {
      vel = 55;
    } else if (dataIn == 'q') {
      vel = 30;
    } else if (dataIn == 'U') {
      determinant = 'U';
    } else if (dataIn == 'u') {
      determinant = 'u';
    } else if (dataIn == 'W') {
      determinant = 'W';
    } else if (dataIn == 'w') {
      determinant = 'w';
    }
  }
  return determinant;
}

void setup() {
  Serial.begin(9600);
  pinMode(overdrive, OUTPUT);
  pinMode(dirA1, OUTPUT);
  pinMode(dirA2, OUTPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);
}

void loop() {
  det = check();
      
  while (det == 'F') {  // F, move forward
    nav(vel,vel);
    det = check();
  }
  while (det == 'B') {  // B, move back
    rev(vel,vel);
    det = check();
  }
  while (det == 'L') {  // L, move wheels left
    nav(vel/4,vel);
    det = check();
  }
  while (det == 'R') {  // R, move wheels right
    nav(vel,vel/4);
    det = check();
  }
  while (det == 'I') {  // I, turn right forward
    nav(vel,vel/2);
    det = check();
  }
  while (det == 'J') {  // J, turn right back
    rev(vel,vel/4);
    det = check();
  }
  while (det == 'G') {  // G, turn left forward
    nav(vel/2,vel);
    det = check();
  }
  while (det == 'H') {  // H, turn left back
    rev(vel/4,vel);
    det = check();
  }
  while (det == 'S') {  // S, stop
    nav(0,0);
    det = check();
  }
  
  //---------------------Toggle switch code------------------//
  /* while (det == 'U')   
  {digitalWrite(power, HIGH);det = check();}
  while (det == 'u')   
  {digitalWrite(power, LOW);det = check();}*/
  //---------------------Mains Power------------------//
  
  while (det == 'W') {
    digitalWrite(overdrive, HIGH);
    det = check();
  }
  while (det == 'w') {
    digitalWrite(overdrive, LOW);
    det = check();
  }
}

