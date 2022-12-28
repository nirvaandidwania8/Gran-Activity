#include <ESP8266WiFi.h>
#include <Arduino_JSON.h>

const char* ssid = "ONEPLUS_co_apbpgv";
const char* password = "hotspot123";


const char* host = "nodemcu-server.hkhday.repl.co"; // only google.com not https://google.com

int ledpin = 5; // D1(gpio5)
int ledpin2 = 14;
int button = 4; //D2(gpio4)
int buttonState=0;
bool isOn = false;
String payload;

void setup() {
 pinMode(ledpin, OUTPUT);
 pinMode(button, INPUT);
 pinMode(ledpin2, OUTPUT);
 Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
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
}
void loop() {
 buttonState=digitalRead(button); // put your main code here, to run repeatedly:
 Serial.println(buttonState);
 if (buttonState == 1)
 {
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS!
  
  client.setInsecure(); // this is the magical line that makes everything work
  
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/finished/person1";
  //url += "?data=";
  //url += "aaaa";


  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  Serial.println();
  Serial.println("closing connection");
  if (isOn) {
   digitalWrite(ledpin, LOW);
   isOn=false;
   Serial.println('pressed');
  } else {
   digitalWrite(ledpin, HIGH);
   isOn = true;
  }
  delay(500);
 }
 Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS!
  
  client.setInsecure(); // this is the magical line that makes everything work
  
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/status";
  //url += "?data=";
  //url += "aaaa";


  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  payload = client.readStringUntil('\n');
  Serial.println(payload);
  
  JSONVar json = JSON.parse(payload);
  Serial.println(json["person2"]);

  Serial.println();
  Serial.println("closing connection");
}
