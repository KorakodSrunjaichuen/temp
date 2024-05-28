#include <max6675.h>
#include <ESP8266WiFi.h>

const char* ssid = "WeiseTechWifi_5G";
const char* password = "123456789ab";

int ledon [] = {16,5,4,0};

int ledtwo [][2] = {{16,5},{4,0}};
int size = (sizeof(ledtwo) / sizeof(ledtwo)[0]);

int thermoDO = 12;
int thermoCS = 15;
int thermoCLK = 14;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {

  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("connecting to");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");
  }
  Serial.println(""); 
  Serial.println("WiFi connected");
  Serial.println("IP address: ");   
  Serial.println(WiFi.localIP());

  
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);


  Serial.println("MAX6675 test");
  delay(500);
}

void loop() {

  if ( thermocouple.readCelsius()<25.99){
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

    Serial.print("Cool = ");
    Serial.println(thermocouple.readCelsius());
  }

  if ( thermocouple.readCelsius()>=26.00 && thermocouple.readCelsius() <=29.99 ){

    for (int i=0;i<4;i++){
      digitalWrite(ledon[i],HIGH);
      delay(100);
  
    } Serial.print("Nomal = ");
    Serial.println(thermocouple.readCelsius()); 
  }
  
  if ( thermocouple.readCelsius()>=30.00 && thermocouple.readCelsius() <=99.99 ){
    
    for (int i=0;i<size;i++){
      digitalWrite(ledtwo[i][0],HIGH);
      digitalWrite(ledtwo[i][1],HIGH);
      delay(400);
      digitalWrite(ledtwo[i][0],LOW);
      digitalWrite(ledtwo[i][1],LOW);
      delay(400);
    }

    Serial.print("C WROM = ");
    Serial.println(thermocouple.readCelsius()); 
  }

  if ( thermocouple.readCelsius()>100 ){

    for (int i=0;i<size;i++){
      digitalWrite(ledtwo[i][0],HIGH);
      digitalWrite(ledtwo[i][1],HIGH);
      delay(50);
      digitalWrite(ledtwo[i][0],LOW);
      digitalWrite(ledtwo[i][1],LOW);
      delay(50);
      digitalWrite(ledtwo[i][0],HIGH);
      digitalWrite(ledtwo[i][1],HIGH);
      delay(50);
      digitalWrite(ledtwo[i][0],LOW);
      digitalWrite(ledtwo[i][1],LOW);
      delay(50);
    }

    Serial.print("HOT = ");
    Serial.println(thermocouple.readCelsius()); 
  } else{

    digitalWrite(16, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(0, LOW);
    delay(1000);

    Serial.print("else = ");
    Serial.println(thermocouple.readCelsius()); 
  }
  delay(2000);
}
