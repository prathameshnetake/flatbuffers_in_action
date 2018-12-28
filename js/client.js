var net = require('net');
var flatbuffers = require('./flatbuffers').flatbuffers;
var MyGame = require('../schema/monster_generated').MyGame;

var client = new net.Socket();
client.connect(5010, '127.0.0.1', function() {
	console.log('Connected');
});

client.on('data', function(data) {
  console.log("Recieved some data");
  var arrayBuffer = new Uint8Array(data);
  var buf = new flatbuffers.ByteBuffer(arrayBuffer);
  var monster = MyGame.Sample.Monster.getRootAsMonster(buf);
  console.log("Monster name is : " + monster.name());
  console.log("Hitting points this monster has : " + monster.hp());
  console.log("Mana power this monster has is : " + monster.mana());
});

client.on('close', function() {
	console.log('Connection closed');
});
