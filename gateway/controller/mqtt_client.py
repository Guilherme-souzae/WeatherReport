import json
import paho.mqtt.client as mqtt


BROKER = "localhost"
PORT = 1883
TOPIC = "weather/+/readings"


def on_connect(client, userdata, flags, reason_code, properties=None):
    print("Conectado ao broker MQTT!")

    # Inscreve-se em todas as estações
    client.subscribe(TOPIC)


def on_message(client, userdata, msg):

    print("=" * 40)
    print(f"Tópico: {msg.topic}")

    # Converte bytes -> string -> dict
    payload = json.loads(msg.payload.decode())

    print("Dados recebidos:")
    print(payload)

    # Descobre qual estação enviou
    device_id = msg.topic.split("/")[1]

    print(f"Dispositivo: {device_id}")

    temperatura = payload["temperature"]
    umidade = payload["humidity"]
    pressao = payload["pressure"]

    print(f"Temperatura: {temperatura}")
    print(f"Umidade: {umidade}")
    print(f"Pressão: {pressao}")

    # Aqui futuramente você faria:
    #
    # evento = WeatherReading(...)
    # kafka.publish("weather.readings", evento)
    #
    # Por enquanto apenas exibimos.


client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)

client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER, PORT)

client.loop_forever()