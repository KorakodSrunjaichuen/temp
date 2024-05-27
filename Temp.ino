#include <max6675.h>

int ledon [] = {16,5,4,0};

int ledtwo [][2] = {{16,5},{4,0}};
int size = (sizeof(ledtwo) / sizeof(ledtwo)[0]);

int thermoDO = 12;
int thermoCS = 15;
int thermoCLK = 14;



MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);

  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);

  Serial.println("MAX6675 test");
  delay(500);
}

void loop() {
  if ( thermocouple.readCelsius()>=26.00 && thermocouple.readCelsius() <=29.99 ){
    Serial.print("C >> 26 = ");

    for (int i=0;i<4;i++){
    digitalWrite(ledon[i],HIGH);
    delay(200);
    digitalWrite(ledon[i],LOW);
    delay(200);
    }

    Serial.println(thermocouple.readCelsius()); 
  }
  
  if ( thermocouple.readCelsius()>=30.00 && thermocouple.readCelsius() <=99.99 ){
    Serial.print("C WROM = ");

    for (int i=0;i<size;i++){
    digitalWrite(ledon[i],HIGH);
    delay(100);
    digitalWrite(ledon[i],LOW);
    delay(100);
    }

    Serial.println(thermocouple.readCelsius()); 
  }

  if ( thermocouple.readCelsius()>100 ){
    Serial.print("C +100 = ");

    for (int i=0;i<size;i++){
    digitalWrite(ledtwo[i][0],HIGH);
    digitalWrite(ledtwo[i][1],HIGH);
    delay(100);
    digitalWrite(ledtwo[i][0],LOW);
    digitalWrite(ledtwo[i][1],LOW);
    delay(100);
    }

    Serial.println(thermocouple.readCelsius()); 
  }
  
  if ( thermocouple.readCelsius()<=30 ){
    Serial.print("C Cool = ");

    for (int i=0;i<4;i++){
    digitalWrite(16, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(0, HIGH);
    delay(20);
    digitalWrite(16, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(0, LOW);
    delay(20);
    }
    Serial.println(thermocouple.readCelsius()); 
  }
  else{
    Serial.print("else = ");

    digitalWrite(16, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(0, LOW);
    delay(20);

    Serial.println(thermocouple.readCelsius()); 
  }
  delay(2000);
}
