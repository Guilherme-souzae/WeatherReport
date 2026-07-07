#include <esp_system.h>
#include <WiFi.h>

#define DEVICE_ID 1
#define READING_INTERVAL 100

const char* SSID = "ADMIN";
const char* PASSWORD = "ADMIN";

struct Datagram
{
    float pressure;
    float temperature;
    float humidity;
};

float random_mock()
{
    uint32_t numero = esp_random();

    return (numero % 5000) / 10.0;
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
    
    Serial.println("Conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    Datagram payload;

    payload.pressure = random_mock();
    payload.temperature = random_mock();
    payload.humidity = random_mock();

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi conectado!");
    }
    else
    {
      Serial.println("Sem conexão.");
    }

    Serial.print("Pressure: ");
    Serial.println(payload.pressure);

    Serial.print("Temperature: ");
    Serial.println(payload.temperature);

    Serial.print("Humidity: ");
    Serial.println(payload.humidity);

    delay(READING_INTERVAL);
}