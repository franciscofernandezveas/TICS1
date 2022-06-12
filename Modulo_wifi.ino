//librerias

#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//conexion wifi
String ssid     = "Francisco";
String password = "12345678";
const char* host = "  192.168.1.119  ";  // IP serveur - Server IP
const int   port = 80;            // Port serveur - Server Port
const int   watchdog = 5000;
unsigned long previousMillis = millis();
ESP8266WebServer server(80);

//sensor de temperatura
const int pinDatosDQ = 9;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

void handleRoot(){
  digitalWrite(2,1);
  server.send(200,"text/plano ","hello world" );
  digitalWrite(2,0);
}
  

byte cont = 0;
byte max_intentos = 50;

void setup() {
  // Inicia Serial
  Serial.begin(115200);
  Serial.println("\n");

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) { //Cuenta hasta 50 si no se puede conectar lo cancela
    cont++;
    delay(500);
    Serial.print(".");
  }

Serial.println("");

  if (cont < max_intentos) {  //Si se conectó      
      Serial.println("********************************************");
      Serial.print("Conectado a la red WiFi: ");
      Serial.println(WiFi.SSID());
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("macAdress: ");
      Serial.println(WiFi.macAddress());
      Serial.println("*********************************************");

      server.on("/",handleRoot);
      server.begin();
      Serial.println("Server HTTP started");
  }
  else { //No se conectó
      Serial.println("------------------------------------");
      Serial.println("Error de conexion");
      Serial.println("------------------------------------");
  }//fin de conexion wifi esp8266

  //sensor de temperatura

    Serial.begin(9600);// Iniciamos la comunicación serie
    sensorDS18B20.begin();  // Iniciamos el bus 1-Wire
    Serial.println(" Temperatura\n\n");


  
}

void loop() {
//temperatura
// Mandamos comandos para toma de temperatura a los sensores
    sensorDS18B20.requestTemperatures();
 
    // Leemos y mostramos los datos de los sensores DS18B20
    Serial.print("Temperatura sensor: ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.println(" °C");

    
    sensorDS18B20.requestTemperatures();
    Serial.print("Temperatura sensor: ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.println(" °C");

delay(1000); 
  
 server.handleClient();
 
       unsigned long currentMillis = millis();
    
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      //Serial.println("Fallo al conectar");
      return;
    }
    String url = "/TutorialESP8266/index.php?temp=";
//    url += sensorDS18B20;

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
