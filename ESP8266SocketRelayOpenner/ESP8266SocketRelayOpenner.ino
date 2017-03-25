#include <ESP8266WiFi.h>
#include "SocketIoClient.h"

SocketIoClient socket;

void setup()
{
  Serial.begin(115200);
  pinMode(D7, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin("SFR_4242", "0671755362");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  
  socket.on("relay lamp", event);
  socket.on("connect", handler);
  socket.on("disconnected", diconnectedHandler);
  socket.begin("192.168.1.20", 3000);

  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

void loop(){
  socket.loop();
}

void event(const char * payload, size_t length) {
  Serial.print("Signal !");
  if (payload != NULL && (strcmp(payload, "1") == 0)){
    digitalWrite(D7, 1);
  } else {
    digitalWrite(D7, 0);
  }
}

void handler(const char * payload, size_t length) {
  Serial.print("Connected !");
  digitalWrite(LED_BUILTIN, LOW);
}

void diconnectedHandler(const char * payload, size_t length) {
  Serial.print("disconnected !");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);
  socket.begin("192.168.1.20", 3000);
}
