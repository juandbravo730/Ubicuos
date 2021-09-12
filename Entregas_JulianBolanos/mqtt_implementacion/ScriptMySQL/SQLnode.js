//variables de mqtt

var mqtt = require('mqtt');// obtener el paquete mqtt
var hostMqtt = "localhost";
var port = 1883;
var clientMqtt;

//Variables SQL

var mysql = require('mysql');   
var conexion = mysql.createConnection({  //Creamos un objeto de conexión hacia la base de datos SQL
    host : 'localhost',
    database : 'ubicuos1',
    user : 'root',
    password : '',
});

var topicSubscribe = "casa/cocina/+";

function conectionCreate(error, cliente) {
    
    if (error) throw error;
    console.log('Conectado con el identificador ' + conexion.threadId);

    //var database = cliente.db("iotDbTest");
    //var collection = database.collection("casa");

    clientMqtt = mqtt.connect({ host: hostMqtt, port: port });
    clientMqtt.subscribe(topicSubscribe);
    clientMqtt.on("message", function (topic, message) {
       var messageDecrypt = message.toString('utf8'); 

        try {
            console.log(messageDecrypt);
            messageDecrypt = JSON.parse(messageDecrypt);
            console.log(message, messageDecrypt);


            conexion.query("INSERT INTO iotDbTest SET ?", messageDecrypt, function (error, results) {
                if (error) throw error;
            
                console.log("1 record inserted");
            });

        } catch (e) {
            console.log("existe un error en los datos");
        }
    });
}

conexion.connect(conectionCreate);