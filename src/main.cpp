#include <Arduino.h>
#include <WiFi.h>

const char * ssid = "lsgo";
const char * password = "1234abcd";
const char * host = "www.google.com";
const int * puerto = 80;

 
void setup() {
  Serial.begin(115200); //Inicializamos el puerto Serial a 115200 bits / segundo
  pinMode(2,OUTPUT); //Colocar un pin como entrada o como salida
  Serial.println("Inicializando dispositivo");
  WiFi.begin(ssid,password);

  Serial.println("Estableciendo vinculo con el AP.");

    while (WiFi.status() != WL_CONNECTED);
    {
      Serial.print(".");
      delay(1000); 
    }
  Serial.println("\r\nConexion establecida");
  Serial.print("Numero IP asignado: ");
  Serial.println (WiFi.localIP());

}
 
void loop() { // creamos cliente TCP por wifi
  WiFiClient cliente;
   // conexion al servidor
   if(!cliente.connect(host, puerto)){
     Serial.println("Error conexion al host fallida");
     delay(2000);
     return;
   }
  //peticion GET al servidor HTTP (request)
   cliente.print("GET /index.html HTTP/1.1\r\nHost: "+host+"\r\n"+"Connection: close\r\n\r\n");

  //debemos darle tiempo al servidor para que responda la peticion (response)
   unsigned long milisegundos = millis(); //hora de inicio
    while (cliente.available()==0) //pregunta si hay datos disponibles
    {
      if (millis()-milisegundos > 5000){
      Serial.println("Se expiro el tiempo de la conexion");
      cliente.stop();
    }
    }
    
   while (cliente.available())
   {
    String linea = cliente.readStringUntil('\r');
    Serial.println(linea);
   }
   
   Serial.println("Fin de la conexion");
   cliente.stop();

   delay(2000);
   


  delay(500);  //Realizar retardos de tiempo en milisegundos
  digitalWrite(2,HIGH);  //Escribir en un pin, ya sea un alto (HIGH) o bajo (LOW)

  Serial.println("Led encendido");

  delay(500);
  digitalWrite(2,LOW);

  Serial.println("Led apagado");
} 