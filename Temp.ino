#include <max6675.h>
#include <ESP8266WiFi.h>

const char* ssid = "WeiseTechWifi";
const char* password = "123456789ab";

int ledon [] = {16,5,4,0};

int ledtwo [][2] = {{16,5},{4,0}};
int size = (sizeof(ledtwo) / sizeof(ledtwo)[0]);

int thermoDO = 12;
int thermoCS = 15;
int thermoCLK = 14;

int ledPin1 = 3;

int ch1 = 0;
////
WiFiServer server(80);

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {

  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");
  }
  Serial.println(""); 
  Serial.println("WiFi connected");
  Serial.println("IP address: ");   

  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("/");

  pinMode(ledPin1, OUTPUT);
  
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);


  Serial.println("MAX6675 test");
  delay(1000);
}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    return;
  }

  Serial.println("new client");
  while (!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


  


  if(request.indexOf("LED=ON") !=-1){
    digitalWrite(ledPin1, LOW);
    ch1 = 1;
  }
  if(request.indexOf("LED=OFF") != -1){
    digitalWrite(ledPin1, HIGH);
    ch1 = 0;
  }


  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("");
  client.println("");


  client.print("led pin 3 : ");
  if (ch1 == 1){
    client.print("on<br>");
  } else{
    client.print('Off<br>');
  }

  client.println("");
  client.println("CH1 <a href=\"/LED1=ON\"\"><button> On </button></a><a href=\"/LED1=OFF\"\"><button> OFF </button></a><br>");

  client.println("");

  Serial.println("Client disonnected");
  Serial.println("");





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

  if ( thermocouple.readCelsius()>26.00 && thermocouple.readCelsius() <=29.99 ){

    for (int i=0;i<4;i++){
      digitalWrite(ledon[i],HIGH);
      delay(100);
      digitalWrite(ledon[i],LOW);
      delay(100);
  
    } Serial.print("Nomal = ");
    Serial.println(thermocouple.readCelsius()); 
  }
  
  if ( thermocouple.readCelsius()>30.00 && thermocouple.readCelsius() <=99.99 ){
    
    for (int i=0;i<size;i++){
      digitalWrite(ledtwo[i][0],HIGH);
      digitalWrite(ledtwo[i][1],HIGH);
      delay(100);
      digitalWrite(ledtwo[i][0],LOW);
      digitalWrite(ledtwo[i][1],LOW);
      delay(100);
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

  }
  delay(500);
}
