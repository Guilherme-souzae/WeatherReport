#include <esp_system.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define READING_INTERVAL 1000

const char* SSID = "ADMIN";
const char* PASSWORD = "ADMIN";

const char* mqttServer = "000.000.000.000";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

struct Datagram
{
    float pressure;
    float temperature;
    float humidity;
};

void connectMQTT()
{
    while (!mqtt.connected())
    {
        Serial.println("Conectando ao MQTT...");
        Serial.println(WiFi.localIP());

        if (mqtt.connect("station001"))
        {
            Serial.println("MQTT conectado!");
        }
        else
        {
            Serial.print("Falha. Código: ");
            Serial.println(mqtt.state());

            delay(2000);
        }
    }
}

float random_mock()
{
    return (esp_random() % 5000) / 10.0;
}

void publishReading(const Datagram& data)
{
    char payload[128];

    snprintf(
        payload,
        sizeof(payload),
        "{\"temperature\":%.1f,\"humidity\":%.1f,\"pressure\":%.1f}",
        data.temperature,
        data.humidity,
        data.pressure
    );

    mqtt.publish("weather/station001/readings", payload);

    Serial.println("Publicado no MQTT:");
    Serial.println(payload);
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Conectando ao WiFi...");

    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi conectado!");
    Serial.print("IP do ESP32: ");
    Serial.println(WiFi.localIP());

    mqtt.setServer(mqttServer, 1883);

    connectMQTT();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi desconectado!");

        WiFi.begin(SSID, PASSWORD);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println("\nWiFi reconectado!");
    }

    if (!mqtt.connected())
    {
        connectMQTT();
    }

    mqtt.loop();

    Datagram reading;

    reading.pressure = random_mock();
    reading.temperature = random_mock();
    reading.humidity = random_mock();

    Serial.println();

    Serial.print("Pressure: ");
    Serial.println(reading.pressure);

    Serial.print("Temperature: ");
    Serial.println(reading.temperature);

    Serial.print("Humidity: ");
    Serial.println(reading.humidity);

    publishReading(reading);

    delay(READING_INTERVAL);
}