#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// COLOCAR AQUI O WIFI QUE VAI SER UTILIZADO)
const char* ssid = "NOME_DO_WIFI";
const char* password = "SENHA_DO_WIFI";

// Servidor (Broker) MQTT Público e Gratuito
const char* mqtt_server = "broker.hivemq.com"; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.begin(115200);
  Serial.print("Conectando-se ao Wi-Fi virtual... ");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado com sucesso!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão com o Servidor MQTT...");
    // Cria um ID único para o ESP32 
    String clientId = "UEA_Annyele_Client_";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println(" Conectado ao Broker!");
    } else {
      Serial.print(" Falhou, erro: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Realiza a leitura real do DHT22
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro na leitura do sensor DHT22!");
    return;
  }

  // Mostra os valores no terminal do Wokwi
  Serial.print("Temp: "); Serial.print(temperatura);
  Serial.print("°C | Umid: "); Serial.print(umidade); Serial.println("%");

  // Transforma os dados em um texto simples separado por vírgula (CSV)
  // Exemplo resultante: "25.4,60.2"
  String dados = String(temperatura, 1) + "," + String(umidade, 1);
  
  // PUBLICA os dados no tópico exclusivo do seu grupo na internet!
  client.publish("uea/annyele/datalogger", dados.c_str());

  delay(3000); // Envia novos dados a cada 3 segundos
}