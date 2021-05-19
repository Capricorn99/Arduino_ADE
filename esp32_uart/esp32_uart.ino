//#include <WiFi.h>
//#include <PubSubClient.h>
//#include <string.h>
//
//const char* ssid = "ASUS1999";
//const char* password = "12101999";
//const char* mqtt_server = "192.168.137.1";
//const int   mqtt_port = 1883;
//
//const char* sub_topic = "meo/2";
//const char* pub_topic = "meo/1";
//
//WiFiClient espClient;
//PubSubClient client(espClient);
//
//#define RXD2 16
//#define TXD2 17

void setup() {
  Serial.begin(115200);
//  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
//  Serial.println("Serial Txd is on pin: "+String(TX));
//  Serial.println("Serial Rxd is on pin: "+String(RX));
//  
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  client.setServer(mqtt_server, mqtt_port);
//  client.setCallback(callback);
//
//  xTaskCreate(
//    WifiTask,
//    "wifi_reconnect",
//    2048,
//    NULL,
//    2,
//    NULL);
}

void loop() {
//  if (Serial2.available()) client.publish(pub_topic, (char*) Serial2.readString().c_str(), false);
//  client.loop();
}

//void callback(char* topic, byte* message, unsigned int length) {
//  Serial.print("Topic: ");
//  Serial.println(topic);
//  Serial.print("Message: ");
//  String _mess = "";
//  String _topic = (String) topic;
//  
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)message[i]);
//    _mess += (char)message[i];
//  }
//  Serial.println("");
//}
//
//void WifiTask (void *pvParameters) {
//  (void) pvParameters;
//
//  for(;;) {
//    if (WiFi.status() != WL_CONNECTED) {
//      WiFi.reconnect();
//      while(WiFi.status() != WL_CONNECTED) vTaskDelay(100);
//    }
//    if (!client.connected() && (WiFi.status() == WL_CONNECTED)) {
//      Serial.println("Attempting MQTT connection...");
//      if (client.connect("ESP_ac_ctrl")) {
//        Serial.println("MQTT connected");
//        client.subscribe(sub_topic);
//      } else {
//        Serial.print("failed, rc=");
//        Serial.print(client.state());
//        Serial.println("");
//      }
//    }
//    vTaskDelay(10);
//  }
//}
