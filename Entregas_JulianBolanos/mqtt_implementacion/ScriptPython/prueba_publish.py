import paho.mqtt.client as mqtt
from random import randrange
import time

mqttBroker = "localhost"
client = mqtt.Client("P1")
client.connect(mqttBroker)

while True:
    randNumber = randrange(10)
    client.publish("demo/device/client", randNumber)
    print("Just published " + str(randNumber) + " to Topic demo/device/client")
    time.sleep(1)