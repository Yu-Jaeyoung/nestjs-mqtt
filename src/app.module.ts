import { Module } from "@nestjs/common";
import { AppController } from "./app.controller";
import { AppService } from "./app.service";
import { MqttController } from "./mqtt/mqtt.controller";
import { MqttService } from "./mqtt/mqtt.service";
import { MqttModule } from './mqtt/mqtt.module';

@Module({
  controllers: [AppController, MqttController],
  providers: [AppService, MqttService],
  imports: [MqttModule]
})

export class AppModule {
}
