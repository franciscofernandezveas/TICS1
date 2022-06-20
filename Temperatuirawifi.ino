#include <ESP8266WiFi.h>
const char* ssid     = "Francisco";      // SSID
const char* password = "12345678";      // Password
const char* host = "localhost";  // IP serveur - Server IP
const int   port = 80;            // Port serveur - Server Port
const int   watchdog = 5000;        // Fréquence du watchdog - Watchdog frequency
unsigned long previousMillis = millis(); 
//wifi====================================================================================================


#include <OneWire.h>
#include <DallasTemperature.h>

const int pinDatosDQ = 9;
void setup(void){ 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //termino conexion wifi ===========================================================================
  
  dht.begin();
  Serial.begin(9600);
  Serial.println("Temperatura\n\n");
  delay(700);

  //opcion
  sensorDS18B20.begin();
  Serial.begin(9600);

}
void loop() {
    

    float t = sensorDS18B20.requestTemperatures();      
    Serial.print("Temperatura = ");
    Serial.print(t); 
    Serial.println("°C  ");

    unsigned long currentMillis = millis();
    
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
    }

    String url = "/tics/enviadatos.php?temperatura=";
    url += t;
    
    
    // Enviamos petición al servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  
    // Leemos la respuesta del servidor
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
}
