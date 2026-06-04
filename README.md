# Estação Meteorológica IoT - Monitoramento de Temperatura e Umidade

## Disciplina: Microprocessadores e Microcontroladores
## Professor doutor: Fábio Cardoso
## Universidade do Estado do Amazonas
## Projeto implementado pelos acadêmicos: 
Annyele Barbosa de Castro; Apolo da Silva Valente; Luiz C. V. dos Santos

## Descrição do Projeto
Este projeto consiste em uma estação meteorológica automatizada baseada em IoT (Internet das Coisas). O sistema realiza a leitura em tempo real da temperatura e umidade do ambiente utilizando uma placa ESP32 e um sensor DHT22. 

Os dados capturados são enviados via protocolo MQTT para um broker público na nuvem. Um script em Python atua como cliente, consumindo esses dados e salvando-os de forma incremental em uma planilha de dados local. Por fim, os dados são integrados ao Excel/Power BI para gerar dashboards visuais e analíticos (como monitoramento por segundos, minutos e semanas).

## Componentes e Ferramentas Utilizadas
### Hardware / Simulação
*   **Microcontrolador:** ESP32 (Dev Module)
*   **Sensor:** DHT22 (Sensor de Temperatura e Umidade Relativa do Ar)
*   **Simulador Online:** Wokwi (para validação do circuito virtual)

### Software, Protocolos e Bibliotecas
*   **Firmware:** Linguagem C++ (Arduino IDE 2.3.9)
*   **Biblioteca MQTT:** PubSubClient (v2.8)
*   **Protocolo de Comunicação:** MQTT (Broker público: `broker.hivemq.com`)
*   **Tópico MQTT Utilizado:** `uea/annyele/datalogger`
*   **Data Ingestion:** Python 3 (com bibliotecas `paho-mqtt` e `os`)
*   **Visualização de Dados:** Microsoft Power BI / Google Sheets / Excel

## Instruções de Execução
### 1. Configuração e Upload do Firmware (ESP32)
1. Abra o arquivo do código-fonte (geralmente `.ino`) na **Arduino IDE**.
2. Certifique-se de ter a placa ESP32 instalada e as bibliotecas **PubSubClient** e **DHT sensor library** adicionadas.
3. No código, ajuste as variáveis de Wi-Fi (`ssid` e `password`) para as credenciais da sua rede real (caso use a placa física). Se for rodar no Wokwi, mantenha `"Wokwi-GUEST"`.
4. Conecte a ESP32 ao computador via USB e clique no botão **Upload** (Seta para a direita) para gravar o código.

### 2. Execução do Coletor de Dados (Python)
1. Certifique-se de ter o Python instalado na sua máquina.
2. Instale a biblioteca do MQTT executando o comando no terminal:
```bash
   pip install paho-mq
