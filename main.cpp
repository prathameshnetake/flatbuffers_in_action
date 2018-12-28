#include <stdio.h>
#include <boost/lambda/lambda.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/beast/core.hpp>
#include <signal.h>

#include "flatbuffers/flatbuffers.h"
#include "communication/server.h"

#include "monster_generated.h"

using namespace MyGame::Sample; // get namespace from schema file

void session(socket_ptr sock) {
    boost::system::error_code error;
    boost::asio::streambuf streamBuffer;
    std::cout << "New client is connected!" << std::endl;
    flatbuffers::FlatBufferBuilder builder(1024);
    auto weapon_one_name = builder.CreateString("Sword");
    short weapon_one_damage = 3;
    auto weapon_two_name = builder.CreateString("Axe");
    short weapon_two_damage = 5;
    // Use the `CreateWeapon` shortcut to create Weapons with all the fields set.
    auto sword = CreateWeapon(builder, weapon_one_name, weapon_one_damage);
    auto axe = CreateWeapon(builder, weapon_two_name, weapon_two_damage);

    auto name = builder.CreateString("Viper");
    // Create a `vector` representing the inventory of the Orc. Each number
    // could correspond to an item that can be claimed after he is slain.
    unsigned char treasure[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto inventory = builder.CreateVector(treasure, 10);

    // Place the weapons into a `std::vector`, then convert that into a FlatBuffer `vector`.
    std::vector<flatbuffers::Offset<Weapon>> weapons_vector;
    weapons_vector.push_back(sword);
    weapons_vector.push_back(axe);
    auto weapons = builder.CreateVector(weapons_vector);

    Vec3 points[] = { Vec3(1.0f, 2.0f, 3.0f), Vec3(4.0f, 5.0f, 6.0f) };
    auto path = builder.CreateVectorOfStructs(points, 2);

    // Create the position struct
    auto position = Vec3(1.0f, 2.0f, 3.0f);
    // Set his hit points to 300 and his mana to 150.
    int hp = 1000;
    int mana = 500;
    // Finally, create the monster using the `CreateMonster` helper function
    // to set all fields.
    auto orc = CreateMonster(builder, &position, mana, hp, name, inventory,
                            Color_Red, weapons, Equipment_Weapon, axe.Union(),
                            path);
    builder.Finish(orc); // You could also call `FinishMonsterBuffer(builder,
                        //
    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize();
    std::cout << "Buffer is ready to transfer" << std::endl;
    boost::asio::write(*sock, boost::asio::buffer(buf, size));
}

int main(int argc, char** argv )
{
    boost::asio::io_service io_service;
    std::cout << "Starting boost server" << std::endl;
    Server::startBoost(session, io_service, 5010);
    return 0;
}