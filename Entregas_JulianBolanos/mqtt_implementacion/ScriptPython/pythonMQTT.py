import paho.mqtt.client as mqtt #import the client1
import time
############

import pymongo

myclient = pymongo.MongoClient("mongodb://localhost:27017/")
mydb = myclient["pythonbase"]
mycol = mydb["home"]

def on_message(client, userdata, message):

    mydict = { "data": message.payload.decode("utf-8"), "topic": message.topic }

    x = mycol.insert_one(mydict)
    print("message received " ,str(message.payload.decode("utf-8")))
    print("message topic=",message.topic)
    print("message qos=",message.qos)
    print("message retain flag=",message.retain)


########################################
broker_address="localhost"
#broker_address="iot.eclipse.org"
print("creating new instance")
client = mqtt.Client("P1") #create new instance
client.on_message=on_message #attach function to callback
print("connecting to broker")
client.connect(broker_address) #connect to broker
client.loop_start() #start the loop
print("Subscribing to topic","demo/device/client")
client.subscribe("demo/device/client")
time.sleep(40) # wait
client.loop_stop() #stop the loop