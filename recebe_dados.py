import paho.mqtt.client as mqtt
import openpyxl
from datetime import datetime
import os

# Configurações
BROKER = "broker.hivemq.com"
PORT = 1883
TOPICO = "uea/annyele/datalogger"
ARQUIVO_EXCEL = "dados_estacao.xlsx" # Agora é .xlsx!

# Cria a planilha Excel se ela não existir
if not os.path.exists(ARQUIVO_EXCEL):
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.title = "Dados Sensor"
    ws.append(["Data e Hora", "Temperatura (C)", "Umidade (%)"])
    wb.save(ARQUIVO_EXCEL)

def ao_conectar(client, userdata, flags, rc, properties=None):
    print(f"Conectado! Escutando o tópico: {TOPICO}")
    client.subscribe(TOPICO)

def ao_receber_mensagem(client, userdata, msg):
    dados_recebidos = msg.payload.decode("utf-8")
    agora = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
    
    try:
        temp, umid = dados_recebidos.split(",")
        print(f"[{agora}] Temp: {temp}°C | Umid: {umid}%")
        
        # Abre o Excel, adiciona a linha e salva
        wb = openpyxl.load_workbook(ARQUIVO_EXCEL)
        ws = wb.active
        # Converte para número (float) para o Excel entender como gráfico depois
        ws.append([agora, float(temp), float(umid)]) 
        wb.save(ARQUIVO_EXCEL)
            
    except Exception as e:
        print(f"Erro ao salvar: {e}")

cliente = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
cliente.on_connect = ao_conectar
cliente.on_message = ao_receber_mensagem

print("Iniciando receptor de dados em XLSX...")
cliente.connect(BROKER, PORT, 60)
cliente.loop_forever()