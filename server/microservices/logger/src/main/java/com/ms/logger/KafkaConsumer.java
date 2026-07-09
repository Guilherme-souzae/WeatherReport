package com.ms.logger;

import java.util.UUID;

import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Component;

@Component
public class KafkaConsumer {

    private final String instanceId = UUID.randomUUID().toString().substring(0, 8);

    @KafkaListener(topics = "weather-readings")
    public void receive(String message) {

        System.out.println(
                "[" + instanceId + "] " + message
        );
    }
}