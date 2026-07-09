import json
import paho.mqtt.client as mqtt
from kafka_client import KafkaClient


class MqttClient:

    def __init__(self):
        self.BROKER = "localhost"
        self.PORT = 1883
        self.TOPIC = "weather/+/readings"

        self.kafka_client = KafkaClient(self.TOPIC)

        self.client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message

    def on_connect(self, client, userdata, flags, reason_code, properties=None):
        print("Conectado!")
        client.subscribe(self.TOPIC)

    def on_message(self, client, userdata, msg):
        print("MENSAGEM RECEBIDA")
        payload = json.loads(msg.payload.decode())

        print(payload)

        self.kafka_client.produce_msg(payload)

    def start(self):
        self.client.connect(self.BROKER, self.PORT)
        self.client.loop_forever()