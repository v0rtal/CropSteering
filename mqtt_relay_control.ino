/**
   @file mqtt_relay_control.ino
   @author sixteenounces@gmail.com
   @brief conncet mqtt broker, subscribe Irrigation/Relay from mqtt broker server to control relay on board,
          and publish messages to mqtt broker server. Based on mqtt_sub_pub.ino by taylor.lee@rakwireless.com
   @version 0.1
   @date 2023-05-11
**/

#include <WiFi.h>
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient/archive/master.zip
#include <Wire.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "ssid";
const char* password = "password";

// Replace it with your MQTT Broker IP address or domain
const char* mqtt_server = "mqtt.msgbroker.net";

// Define an ID to indicate the device, If it is the same as other devices which connect the same mqtt server,
// it will lead to the failure to connect to the mqtt server
const char* mqttClientId = "esprelay";

// if need username and password to connect mqtt server, they cannot be NULL.
const char* mqttUsername = "user";
const char* mqttPassword = "password";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

long lastMsg = 0;

// Relay Pins
int relayPin1 = 1;
int relayPin2 = 2;
int relayPin3 = 3;
int relayPin4 = 4;
int relayPin5 = 5;
int relayPin6 = 6;
int relayPin7 = 7;
int relayPin8 = 8;

void setup()
{
  Serial.begin(115200);

  // conncet WiFi AP
  setup_wifi();

  // connect mqtt broker
  mqttClient.setServer(mqtt_server, 1883);
  // set callback of receiving message
  mqttClient.setCallback(callback);

  // set relay pin mode
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);
  pinMode(relayPin6, OUTPUT);
  pinMode(relayPin7, OUTPUT);
  pinMode(relayPin8, OUTPUT);
}

/* conncet WiFi AP
   wait until wifi is connected.
*/
void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* callback of receiving subscribed message
   it can only deal with topics that he has already subscribed.
*/
void callback(char* topic, byte* message, unsigned int length) {
  String messageTemp = "";
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  // get and print message recieved
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic Irrigation/Relay1, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "Irrigation/Relay1")
  {
    Serial.print("Changing Relay1 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin1, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin1, LOW);
    }
  }

  if (String(topic) == "Irrigation/Relay2")
  {
    Serial.print("Changing Relay2 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin2, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin2, LOW);
    }
  }

  if (String(topic) == "Irrigation/Relay3")
  {
    Serial.print("Changing Relay3 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin3, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin3, LOW);
    }
  }

  if (String(topic) == "Irrigation/Relay4")
  {
    Serial.print("Changing Relay4 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin4, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin4, LOW);
    }
  }

  if (String(topic) == "Irrigation/Relay5")
  {
    Serial.print("Changing Relay5 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin5, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin5, LOW);
    }
  }

  if (String(topic) == "Irrigation/Relay6")
  {
    Serial.print("Changing Relay6 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin6, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin6, LOW);
    }
  }

  if (String(topic) == "Irrigation/Relay7")
  {
    Serial.print("Changing Relay7 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin7, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin7, LOW);
    }
  }

  if (String(topic) == "Irrigation/Relay8")
  {
    Serial.print("Changing Relay8 status to ");
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(relayPin8, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(relayPin8, LOW);
    }
  }

  // Feel free to add more to handle more topics
}

/*
    reconnect to mqtt broker if disconnected
    when connected to mqtt broker, subscribe topic here.
*/
void reconnect() {
  // Loop until reconnected
  while (!mqttClient.connected())
  {
    Serial.print("Connecting to  MQTT broker...");
    if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword))
    {
      Serial.println("connected");

      // Subscribe topics which you want to receive.
      mqttClient.subscribe("Irrigation/Relay1");
      mqttClient.subscribe("Irrigation/Relay2");
      mqttClient.subscribe("Irrigation/Relay3");
      mqttClient.subscribe("Irrigation/Relay4");
      mqttClient.subscribe("Irrigation/Relay5");
      mqttClient.subscribe("Irrigation/Relay6");
      mqttClient.subscribe("Irrigation/Relay7");
      mqttClient.subscribe("Irrigation/Relay8");
      // you can add other Subscribe here
    }
    else
    {
      Serial.print("failed, code=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop()
{
  if (!mqttClient.connected())
  {
    reconnect();
  }
  mqttClient.loop();

  long now = millis();
  if (now - lastMsg > 20000) // publish every 20s
  {
    lastMsg = now;

    // publish or keep-alive

  }
}
