from dataclasses import dataclass
import uuid

@dataclass
class WeatherEntity:
    event_id: str
    devide_id: str
    
    temperature: float
    humidity: float
    pressure: float

    @staticmethod
    def create(device_id, temperature, humidity, pressure):

        return WeatherEntity(
            event_id=str(uuid.uuid4()),
            devide_id=device_id,
            
            temperature=temperature,
            humidity=humidity,
            pressure=pressure
        )