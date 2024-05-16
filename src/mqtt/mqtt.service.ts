import { Injectable } from "@nestjs/common";
import { connect, MqttClient } from "mqtt";

@Injectable()
export class MqttService {
  public readonly mqtt: MqttClient;

  constructor() {
    this.mqtt = connect("mqtt://broker.emqx.io:1883", {
      clientId: "steviaClient",
      clean: true,
      connectTimeout: 4000,
      reconnectPeriod: 1000
    });
  }

  async publish(topic: string, payload: string): Promise<string> {
    this.mqtt.publish(topic, payload);
    return "Message Published !";
  }
}
