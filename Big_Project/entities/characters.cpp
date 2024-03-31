#include"./entities/characters.hpp"
#include"./company_tools/manager.hpp"
using namespace std;

void Characters::init(string Position, string avatar_directory) {
    position = Position;
    avatar = avatar_directory;
}

void Characters::chatMessage(ChatBox* box, string message) {
    bool CAN_MESSAGE = (*box).canMessage(this);
    if (CAN_MESSAGE) {
        (*box).appendMessage(this, message);
    }
}