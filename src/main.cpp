#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
WiFiClient client;

ESP8266WebServer server(80);

const char *ssid = "AndroidAP00DF";
const char *password = "extfs2048";

String data = " ";

#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

void handlerequest()
{
  if (server.hasArg("Key"))
  {
    Serial.println(server.arg("Key"));
  }
}

void connectingToWiFi()
{
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi Please Wait... ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Waiting to Connect");
  }
  Serial.println("Connected to WiFi");
  Serial.print(WiFi.localIP().toString());
  delay(5000);
}

void move_forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void move_backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turn_left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turn_right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void turn_sharp_left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turn_sharp_right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop_bot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("GPIO TEST !");

  pinMode(IN1, OUTPUT); // orange
  pinMode(IN2, OUTPUT); // yellow
  pinMode(IN3, OUTPUT); // green
  pinMode(IN4, OUTPUT); // blue

  connectingToWiFi();

  server.on("/", handlerequest);
  server.onNotFound(handlerequest);

  server.begin();
  Serial.println("Server Started");
}

void loop()
{
  server.handleClient();
  String data = server.arg("Key");
  Serial.println(data);

  if (data == "F")
  {
    move_forward();
  }
  else if (data == "B")
  {
    move_backward();
  }
  else if (data == "R")
  {
    turn_right();
  }
  else if (data == "L")
  {
    turn_left();
  }
  else if (data == "SR")
  {
    turn_sharp_right();
  }
  else if (data == "SL")
  {
    turn_sharp_left();
  }
  else if (data == "S")
  {
    stop_bot();
  }
}