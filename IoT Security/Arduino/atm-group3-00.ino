#include <MQTT.h>
#include <Microphone.h>
#include <Brightness.h>
#include <Temperature.h>
#include <Gyroscope.h>
#include <LinearHall.h>
#include <GPS.h>
#include <Display.h>
#include <Motion.h>
#include <RGBLed.h>
#include <Buzzer.h>

//Environment vars
const char *SERVER_ADDRESS = "paologas91.chickenkiller.com";
const int SERVER_PORT = 1883;
const char *clientName = "atm-group3-00";
const char *username = "atm";
const char *password = "atm";

const char *gyroTopic = "atm/gyroscope/value";
const char *temperatureTopic = "atm/temperature/value";
const char *brightnessTopic = "atm/brightness/value";
const char *microphoneTopic = "atm/microphone/value";
const char *linearHallTopic = "atm/linearhall/value";
const char *gpsTopic = "atm/gps/value";
const char *motionTopic = "atm/motion/value";

void(* Reset)(void) = 0;
MQTT mqtt((char *)SERVER_ADDRESS, (int)SERVER_PORT, Serial);

bool gps_mode = false;
//int n_alarms = 0;
unsigned long current_millis = 0;
unsigned long interval = 0;

//Sensors instances
Brightness brightness(PHOTO_RES_PIN);
Temperature temperature(DHT11_PIN);
Microphone microphone(BIG_SOUND_AO_PIN);
LinearHall linearHall(LH_MAGNETIC_AO_PIN);
Motion motion(MOTION_PIN);
Gyroscope gyroscope;
GPS gpsModule;
Display display;
RGBLed rgbled;
Buzzer buzzer;

void initConnection()
{
  if (mqtt.initialize())
  {
    mqtt.connect(clientName, username, password);
    mqtt.subscribe((char *)clientName);
    mqtt.OUT->println(F("Connected & Subscribed..."));
  }
  else
  {
    mqtt.OUT->println(F("Unable to connect to the network...retrying"));
    initConnection();
  }
}

void publish(const char *topic, char* sensorValue, int QoS = 0)
{
  mqtt.publish(topic, sensorValue, QoS);
}

void publishSensors(char* sensorValue)
{
  gpsModule.measureValue(sensorValue);
  publish(gpsTopic, sensorValue);
  delay(200);
  microphone.measureValue(sensorValue);
  publish(microphoneTopic, sensorValue);
  delay(200);
  brightness.measureValue(sensorValue);
  publish(brightnessTopic, sensorValue);
  delay(200);
  temperature.measureValue(sensorValue);
  publish(temperatureTopic, sensorValue);
  delay(200);
  gyroscope.measureValue(sensorValue);
  publish(gyroTopic, sensorValue);
  delay(200);
  linearHall.measureValue(sensorValue);
  publish(linearHallTopic, sensorValue);
  delay(200);
  motion.measureValue(sensorValue);
  publish(motionTopic, sensorValue);
}

void checkStatus()
{
  if (strcmp(mqtt.receivedMessage, "rule1") == 0)
  {
    if (current_millis != 0)
    {
      interval += millis() - current_millis;
    }
    else
    {
      current_millis = millis();
    }
    activateAlarm("Rule 1");
    //n_alarms++;
  }
  else if (strcmp(mqtt.receivedMessage, "rule2") == 0) 
  {
    if (current_millis != 0)
    {
      interval += millis() - current_millis;
    }
    else
    {
      current_millis = millis();
    }
    activateAlarm("Rule 2");
    //n_alarms++;
  }
  else if (strcmp(mqtt.receivedMessage, "rule3") == 0) 
  {
    if (current_millis != 0)
    {
      interval += millis() - current_millis;
    }
    else
    {
      current_millis = millis();
    }
    activateAlarm("Rule 3");
    //n_alarms++;
  }
  else if (strcmp(mqtt.receivedMessage, "rule4") == 0) 
  {
    if (current_millis != 0)
    {
      interval += millis() - current_millis;
    }
    else
    {
      current_millis = millis();
    }
    activateAlarm("Rule 4");
    //n_alarms++;
  }
  else if (strcmp(mqtt.receivedMessage, "rule5") == 0) 
  {
    if (current_millis != 0)
    {
      interval += millis() - current_millis;
    }
    else
    {
      current_millis = millis();
    }
    activateAlarm("Rule 5");
    //n_alarms++;
  }
  else if (strcmp(mqtt.receivedMessage, "rule6") == 0) 
  {
    if (current_millis != 0)
    {
      interval += millis() - current_millis;
    }
    else
    {
      current_millis = millis();
    }
    gps_mode = true;
    activateAlarm("Rule 6");
    //n_alarms++;
  }
  else if (strcmp(mqtt.receivedMessage, "rule7") == 0) 
  {
    if (current_millis != 0)
    {
      interval += millis() - current_millis;
      Serial.print("millis value inside if: ");
      Serial.println(millis());
      Serial.print("current_millis value inside if: ");
      Serial.println(current_millis);
    }
    else
    {
      current_millis = millis();
      Serial.print("millis value inside else: ");
      Serial.println(millis());
      Serial.print("current_millis value inside else: ");
      Serial.println(current_millis);
    }
    gps_mode = true;
    activateAlarm("Rule 7");
    //n_alarms++;
  }
  else if (strcmp(mqtt.receivedMessage, "reset") == 0)
  {
    deactivateAlarm();
    //n_alarms = 0;
    gps_mode = false;
    current_millis = 0;
    interval = 0;
  }
  else if (strcmp(mqtt.receivedMessage, "debug") == 0)
  {
    debugMode = !debugMode;
    mqtt.receivedMessage[0] = '\0';
  }
  else if (strcmp(mqtt.receivedMessage, "reboot") == 0)
  {
    Reset();
  }
  else
  {
    Serial.println("No message or invalid message from NodeRED");
    mqtt.receivedMessage[0] = '\0';
  }
}

void activateAlarm(char * message)
{
    display.printAlarm(message);
    buzzer.activate(660, 3000);
    rgbled.color(255, 0, 0);
}

void deactivateAlarm()
{
    display.printLogo();
    buzzer.activate(660, 1);
    buzzer.deactivate();
    rgbled.color(0, 255 ,0);
    mqtt.receivedMessage[0] = '\0';
}

void setup()
{
  srand(static_cast<unsigned>(time(0)));
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  rgbled.setup();
  buzzer.setup();
  gpsModule.setup();
  gyroscope.setup();
  display.printLogo();
  rgbled.color(0, 255, 0);
  initConnection();
}

void loop()
{
  char sensorValue[90];
  if (mqtt.isConnected())
  {
    if (gps_mode)
    {
      gpsModule.measureValue(sensorValue);
      publish(gpsTopic, sensorValue);
    }
    else
    {
      publishSensors(sensorValue);
    }
  }
  if (gps_mode)
  {
    delay(1000);
  }
  else
  {
    delay(5000);
  }
  Serial.print("Battery voltage read: ");
  Serial.println(analogRead(A13));
  display.printBatteryStatus();
  delay(3000);
  display.printLogo();
  mqtt.loop();
  checkStatus();
  
  if (!mqtt.isConnected()){
    Reset();
  }
  if (current_millis != 0) // simulates ink-stained banknotes
  {
    Serial.print("interval: ");
    Serial.println(interval);
    if (interval >= 60000)
    digitalWrite(RELAY_PIN, HIGH);
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
  }
}
