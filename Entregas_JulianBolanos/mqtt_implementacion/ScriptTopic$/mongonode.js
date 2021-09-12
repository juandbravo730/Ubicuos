//variables de mqtt

var mqtt = require('mqtt');// obtener el paquete mqtt
var hostMqtt = "localhost";
var port = 1883;
//variables de mongo db
var mongodb = require('mongodb');
var mongodbClient = mongodb.MongoClient;
var mongodbURI = 'mongodb://localhost:27017/house';
var topicSubscribe = "casa/cocina/+";   //Con el signo + le decimos que vamos a escuchar todo lo de la cocina
var topicSubscribe1 = "$SYS/broker/uptime";

var clientMqtt;


function conectionCreate(error, cliente) {
    if (error) throw error;

    var database = cliente.db("iotDbTest");
    var collection = database.collection("casa");

    clientMqtt = mqtt.connect({ host: hostMqtt, port: port });
    clientMqtt.subscribe(topicSubscribe);   //me suscribo al topic
    clientMqtt.on("message", function (topic, message) {    //creamos un evento para poder escuchar
        var messageDecrypt = message.toString('utf8');
        try {
            console.log(messageDecrypt);
            var objToInsert = { topic: topic, data: messageDecrypt };
            collection.insertOne(objToInsert, function (err, res) {
                if (err) throw err;
                console.log("El valor :" + messageDecrypt + " está en la db");
            });
        } catch (e) {
            console.log("existe un error en los datos");
        }
    });
}

mongodb.connect(mongodbURI, conectionCreate);