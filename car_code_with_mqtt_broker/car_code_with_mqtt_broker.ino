#include <WiFi.h>
#include <WiFiClient.h>
#include <analogWrite.h>
#include <PubSubClient.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "********"; //WIFI ID goes here
char pwd[] = "***********"; //WFIF password goes here

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 
char mqttServer [] = "***************"; //mqtt broker address goes here
int mqttPort = ****; //mqtt port number goes here

//Enabling the MCU pins for the motors that feed to the motor controller
// Motor A connections
int enA = 21;
int lw1 = 22;
int lw2 = 19;
// Motor B connections
int enB = 23;
int rw1 = 16;
int rw2 = 4;

//connect the arduino to the internet
void connectToWiFi() {
  Serial.print("Connecting to ");
 
  WiFi.begin(ssid, pwd);
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected.");
}

//create a connection to the MQTT server
void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}
//if loss of connection to the mqtt server, reestablise the connection
void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("cartestthing1243/command");
      }
  }
}

// function to set the rc car to drive in directions for 1s intervals
void forward()
{
    digitalWrite(lw1, HIGH);
    digitalWrite(rw1, HIGH);
    delay(1000);
    digitalWrite(lw1, LOW);
    digitalWrite(rw1, LOW);
}

void backward()
{
    digitalWrite(lw2, HIGH);
    digitalWrite(rw2, HIGH);
    delay(1000);
    digitalWrite(lw2, LOW);
    digitalWrite(rw2, LOW);
}

void left()
{
    digitalWrite(lw2, HIGH);
    digitalWrite(rw1, HIGH);
    delay(1000);
    digitalWrite(lw2, LOW);
    digitalWrite(rw1, LOW);
}

void right()
{
    digitalWrite(lw1, HIGH);
    digitalWrite(rw2, HIGH);
    delay(1000);
    digitalWrite(lw1, LOW);
    digitalWrite(rw2, LOW);
}

//string handler for posted messages to the MQTT server, 
//will complete a task per instuction it identifies
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    switch((char)payload[i]){
      case '1': 
        forward();
        break;
      case '2':
        backward();
        break;
      case '3':
        left();
        break;
      case '4':
        right();
        break;
      default:
        break;
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  connectToWiFi();
  setupMQTT();

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(lw1, OUTPUT);
  pinMode(lw2, OUTPUT);
  pinMode(rw1, OUTPUT);
  pinMode(rw2, OUTPUT);
  
  analogWrite(enA, 255);
  analogWrite(enB, 255);

}
//Loop to continue listening to the mqtt broker
void loop()
{ 
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
}
