from kafka import KafkaProducer
import json

class KafkaClient:
    def __init__(self, topic):
        self.producer = KafkaProducer(
            bootstrap_servers="localhost:9092",
            value_serializer=lambda v: json.dumps(v).encode("utf-8")
        )
        self.topic = topic

    def produce_msg(self, data):
        self.producer.send("weather-readings", key=b"station-01", value=data)
        self.producer.flush()