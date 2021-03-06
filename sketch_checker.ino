int sensorValue = 0;
//int volt = 0;
int x = 0;
int c = 0;
int pol = 0;
float voltage = 4.5;
float vol = 0;
float cap = 0;
float capplus = 0;
float minute = 0;
bool start = true;

int switcher = 2; // 1-универсальный, 2-для батареи
float resist;

int reading;
int counter = 0;
int current_state = LOW;


void setup() {
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT); //кнопка
  pinMode(2, OUTPUT); //реле
  Serial.begin(9600);
}

void loop() {
  if (switcher == 1) {
    resist = 7.4; // универсальный    
  } else {
    resist = 3; // вариант для батареи
  }
  
  if (voltage == 4.5) { // запускаем реле
    digitalWrite (2, LOW);
  }

  // кнопка напряжения
  for (int i=0; i <2000; i++) {
    reading = digitalRead(3);
    
    if(reading == LOW && counter > 0) {
      counter--;
    }

    if(reading == HIGH) {
       counter++; 
    }  

    if(counter >= 5) {
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      ClearDigit();

      if (voltage >= 4) {
        digitalWrite(6, HIGH);
      } else {
        int voltageDigit = round((voltage - 3)*10);
        Serial.print(voltageDigit);
        DrawDigit(voltageDigit);
      }
      
      cap = cap + 0.4;
      delay(3000);
      ClearDigit();
      counter = 0;
      continue; 
    }
    delay(3);
  }

  // проверяем напряжение
  if (voltage < 3.05) {
    digitalWrite (2, HIGH);
    capplus = 0;
  } else {
    if(switcher == 1) { // универсальный
      capplus = (voltage*10) / (resist*6); // * 1000 / * 60 минут в часе * 10 раз по 6 секунд 
    } else {
      capplus = voltage / 18; // вариант для батареи, максимум 20950 мА/час
    }
  }
  //capplus = 40;
  
  int sensorValue = analogRead(A1);
  Serial.print(sensorValue);
  Serial.print(" : ");
  
  voltage = sensorValue*0.00485;
  //voltage = voltage - 0.01;
  Serial.print("voltage V: ");
  Serial.print(voltage);

  cap = cap + capplus;
  Serial.print("  capacity mA: ");
  Serial.print(cap);
  
  minute = minute + 0.1;
  Serial.print("  minutes: ");
  Serial.print(minute);
  
  c = cap;
  if (cap > 999 && cap < 1999 ) {
    c = cap - 1000;
    digitalWrite(4, HIGH);
    if (cap < 1001) {
      ClearDigit();
    }
  }
  if (cap > 1999) {
    c = cap - 2000;
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    if (cap < 2001) {
      ClearDigit();
    }
  }
  Serial.print("  hundreds: ");
  Serial.print(c);

  x = floor (c/100);
  Serial.print("  digit: ");
  Serial.print(x);
  DrawDigit(x);
  
  pol = c - x*100;
  Serial.print("  pol: ");
  Serial.print(pol); 
  
  if ( pol > 49 ) {
    digitalWrite (10, HIGH);
  } else {
    digitalWrite (10, LOW);
  }

  //delay (6000);
  //ClearDigit();
  Serial.println("");
}

void DrawDigit(int x) {

  if (x == 1) {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);  
  }

  if (x == 2) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }
  if (x == 3) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  
  if (x == 4) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  
 if (x == 4) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  
 if (x == 5) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  
  if (x == 6) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }
  
  if (x == 7) {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  
  if (x == 8) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }
  
  if (x == 9) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  
}

void ClearDigit() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW); 
}
