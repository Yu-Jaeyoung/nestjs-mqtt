import { Body, Controller, Post } from "@nestjs/common";
import { MqttService } from "./mqtt.service";

@Controller("mqtt")
export class MqttController {
  constructor(private readonly mqttService: MqttService) {
  }

  @Post("publish")
  async publishMessage(@Body() body: { topic: string; message: string }): Promise<string> {
    return await this.mqttService.publish(body.topic, body.message);
  }
}
