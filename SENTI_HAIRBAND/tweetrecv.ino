/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
IPAddress ip(192,168,133,254);
IPAddress gateway(192,168,133,111);
IPAddress subnet(255,255,0,0);


const char* ssid     = "<>";
const char* password = "<>";

const char* host = "192.168.133.18";
const char* streamId   = "....................";
const char* privateKey = "....................";

void setup() {

  
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(0, LOW);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 50000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request

  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    if ((char)line[0] == 'R'){
      Serial.print(line);
      digitalWrite(2, LOW);
      digitalWrite(0, HIGH);
      digitalWrite(3, LOW);
      
    }
    if ((char)line[0] == 'G'){
      Serial.print(line);
      digitalWrite(0, LOW);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
    }

    if ((char)line[0] == 'B'){
      Serial.print(line);
      digitalWrite(0, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
    }
  }
  
  Serial.println();
  Serial.println("closing connection");
}

